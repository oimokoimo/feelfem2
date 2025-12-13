      subroutine mkielemex(feel,myrank,nprocs,nparams,
     $                     enptr,con,matno,nelem,
     $                     ibuf,icount,idispl,
     $                     dbuf,dcount,ddispl,
     $                     nelem_ex,np_enptr_ex,np_con_ex,np_matno_ex)
*----------------------------------------------------------
* FEELFEM/P2DRAMA subroutine
* 
* Make Outer element information 
*      
* INPUT:  feel     REAL*4(*)       Memory allocation buffer
*         myrank   INTEGER*4       MPI my rank
*         nprocs   INTEGER*4       Number of processors
*         nparams  INTEGER*4       Number of parameters in ibuf area
*         enptr    INTEGER*4(2,*)  DRAMA double index format indicator
*         con      INTEGER*4(2,*)  DRAMA double index format
*         matno    INTEGER*4(*)    Material number
*         nelem    INTEGER*4       Number of elements (of my PE)
*         ibuf     INTEGER*4(*)    Gather/Bcast data buffer(INTEGER DATA)
*         icount   INTEGER*4(*)    Number of data
*         idispl   INTEGER*4(*)    Starting Pointer
*         dbuf     REAL*8(*)       Gather/Bcast data buffer(DOUBLE PRECISION)
*         dcount   INTEGER*4(*)    Number of data
*         ddispl   INTEGER*4(*)    Starting Pointer
*
* OUTPUT: nelem_ex        INTEGER*4 Number of elements for relating outer elem
*         np_enptr_ex     INTEGER*4 (allocated pointer in feel array)
*         np_con_ex       INTEGER*4 (allocated pointer in feel array)
*         np_matno_ex     INTEGER*4 (allocated pointer in feel array)
*
*----------------------------------------------------------
      parameter (MAX_PROCS = 256)
      parameter (NCTRL_ITEMS_HERE = 4)
*
      real*4    feel(*)
      integer*4 enptr(2,*),con(2,*),matno(*)

      integer*4 ibuf(*)
      real   *8 dbuf(*)
      integer*4 icount(*),idispl(*)
      integer*4 dcount(*),ddispl(*)
*
      integer*4 procbuf(MAX_PROCS)
*----------------------------------------------------------
* check the number of parameters stored in ibuf area
*-----
      if(MAX_PROCS .LT. nprocs) then
         call abortexit(myrank,'Too many procs (mkielemex)')
      endif
*
      if(NCTRL_ITEMS_HERE .NE. nparams) then
         call abortexit(myrank,'Mismatch NCTRL_ITEMS(mkielemex)')
      endif
*
      mypeid = myrank
      mypeidx= myrank+1
*------------------------------------------------
* STEP 1 Count the necessary elements in other PE
*------------------------------------------------
      nelem_ex    = 0
      nconsiz_ex  = 0
*
      do 100 i=1,nprocs
         procbuf(i) = 0
         if(mypeidx .eq. i) goto 100

*---
*information pointer for PE(i-1)
*---
         ne2send  =   ibuf(idispl(i) + 1)
         nconsiz  =   ibuf(idispl(i) + 2)
         iptr_enptr_send = idispl(i) + NCTRL_ITEMS_HERE + 1
         iptr_con_send   = idispl(i) + NCTRL_ITEMS_HERE + 
     $                     2*(ne2send+1) + 1
         iptr_matno_send = iptr_con_send + nconsiz * 2

         if(ne2send .eq. 0) goto 100
         
         call mkielemex_count_elem(mypeid, ne2send,
     $                            ibuf(iptr_enptr_send),
     $                            ibuf(iptr_con_send  ),
     $                            myconcern,myebufsiz)
         procbuf(i) = myconcern
         nelem_ex   = nelem_ex   + myconcern
         nconsiz_ex = nconsiz_ex + myebufsiz
 100  continue
*
      if(nelem_ex .NE. 0) then
      call f_alloc(np_enptr_ex,'enptr_ex',(nelem_ex+1)*2,0,0)
      call f_alloc(np_con_ex  ,'con_ex'  , nconsiz_ex *2,0,0)
      call f_alloc(np_matno_ex,'matno_ex', nelem_ex     ,0,0)
      call feelset_npi(feel,np_enptr_ex,1,1)
*-----
* MAKE con_ex,exptr_ex
*-----
      iptr = 0
      do 150 i=1,nprocs
         if(procbuf(i) .eq. 0) goto 150
         if(mypeidx    .eq. i) goto 150
*---
*information pointer for PE(i-1)
*---
         ne2send  =   ibuf(idispl(i) + 1)
         nconsiz  =   ibuf(idispl(i) + 2)
         iptr_enptr_send = idispl(i) + NCTRL_ITEMS_HERE + 1
         iptr_con_send   = idispl(i) + NCTRL_ITEMS_HERE + 
     $                                 2*(ne2send+1)    + 1
         iptr_matno_send = iptr_con_send + nconsiz * 2
*
         if(ne2send .eq. 0) goto 150
*
         call mkielemex_mk_ex(mypeid, ne2send, iptr,
     $                       ibuf(iptr_enptr_send),
     $                       ibuf(iptr_con_send  ),
     $                       ibuf(iptr_matno_send),
     $                       feel(np_enptr_ex),feel(np_con_ex),
     $                       feel(np_matno_ex))
 150  continue      
      endif
*---
      return
      end
      subroutine mkielemex_count_elem(mypeid,
     $                               ne2send,enptr,con,
     $                               myconcern,myebufsiz)
*----------------------------------------------------------------
* Count the element in other PE's element
*
* INPUT : mypeid     PE id of mine
*         ne2send    This processor's sended number of elements
*         enptr      Sended element pointer
*         con        Sended element-node pointer
*         myconcern  Number of elements relating my PE
*         myebufsiz  The size of buffer for eptr(must be *2 )
*----------------------------------------------------------------      
      integer*4 enptr(2,*),con(2,*)
*----------------------------------
      myconcern = 0
      myebufsiz = 0
*-
      do 100 i=1,ne2send
         ipos_from = enptr(1,i  )
         ipos_to   = enptr(1,i+1)-1
         ilen      = ipos_to - ipos_from +1
*         
         do 101 j=ipos_from,ipos_to
            if(con(2,j) .EQ. mypeid) then
               myconcern = myconcern +1 
               myebufsiz = myebufsiz + ilen
               goto 100
            endif
 101     continue
*
 100  continue
*
      return
      end
      subroutine mkielemex_mk_ex(mypeid,ne2send,iptr,
     $                           enptr  ,con  ,matno   ,
     $                           enptrex,conex,matnoex  )
*----------------------------------------------------------------
* Count the element in other PE's element
*
* INPUT : mypeid     PE id of mine
*         ne2send    This processor's sended number of elements
*      
*         enptr      Sended element pointer
*         con        Sended element-node pointer
*
* INPUT/OUTPUT
*         iptr       pointer for enptrex,conex
*         enptrex
*         conex
*----------------------------------------------------------------      
      integer*4 enptr  (2,*), con  (2,*),matno  (*)
      integer*4 enptrex(2,*), conex(2,*),matnoex(*)
*----------------------------------
      do 100 i=1,ne2send
         ipos_from = enptr(1,i  )
         ipos_to   = enptr(1,i+1)-1
         ilen      = ipos_to - ipos_from +1
*         
         do 101 j=ipos_from,ipos_to
            if(con(2,j) .EQ. mypeid) then
               iptr = iptr + 1
*
*  enptrex(1,1) is set to 1 at the allocation
*
               enptrex(2,iptr  )= enptr  (2,i)
               enptrex(1,iptr+1)= enptrex(1,iptr)+ilen
               matnoex(iptr    )= matno(i)

               do 102 k=1,ilen
                  conex(1,enptrex(1,iptr)+k-1)=con(1,ipos_from+k-1)
                  conex(2,enptrex(1,iptr)+k-1)=con(2,ipos_from+k-1)
 102           continue
               goto 100
            endif
 101     continue
*
 100  continue
*
      return
      end




