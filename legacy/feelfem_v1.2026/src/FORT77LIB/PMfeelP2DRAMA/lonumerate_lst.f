      subroutine lonumerate_lst(feel   ,myrank  ,nprocs,
     $                          loc    ,npmax_g ,
     $                          metis  ,nelem_g ,
     $                          nredat ,redatctr,
     $                          mynode ,myelem           )
*------------------------------------------------------------------
*     Make local indicies from REGIONAL EDAT set list
*
*     node has two enumerate/ local node number and PE number
* INPUT:
*     myrank,nprocs
*                             
*                             
* OUTPUT:
*                             
*     loc(1,i)  PE id for i-th(global) node
*     loc(2,i)  Node number for i-th(global) node in PE id
*               Original ordering is used.
*     ********* Loc(3,i)  Work space for calculating myrelnode
*                                        
*     mynode     Number of my own nodes
*     myelem     Number of my elements
*------------------------------------------------------------------
      parameter (MAXPE       =256)
      parameter (NIDPLUS     =  1)
      parameter (NOTYETFLAG  = -1)
*------------------------------------
      real*4    feel(*)
*
      integer*4 npmax_g,nelem_g
*
      integer*4 loc(2,npmax_g)
      integer*4 metis(nelem_g)
*
      integer*4 nredat 
      integer*4 redatctr(5,*)

      integer*4 myelem,mynode,myrelnode

      dimension icount(MAXPE)
*------------------------------------------------------------------
      if(npmax_g .LT. 1) then
         call abortexit(myrank,'npmax_g ERROR')
      endif
      if(MAXPE  .LT. nprocs) then
         call abortexit(myrank,'lonumerate_loc(MAXPE too small)')
      endif
*------------------
* Initialization
*------------------
      myelem    = 0
      mynode    = 0
      myrelnode = 0
*
      do 11 i=1,nprocs
        icount(i) = 0
11    continue
*---
      write(*,*) 'myrank =',myrank,'  npmax_g =',npmax_g
      do 10 i=1,npmax_g
         loc(1,i) =  NOTYETFLAG
         loc(2,i) =  0
 10   continue
*----------------------------------------
      do 100 i=1,nredat
         no       = redatctr(1,i)
         np       = redatctr(2,i)
         nelem    = redatctr(3,i)
         np_ielem = redatctr(4,i)
         np_matno = redatctr(5,i)
*
         if(nelem .ne. nelem_g) then
            call abortexit(myrank,'(lonumerate_lst, nelem.NE.nelem_g)')
         endif
*-----------------------
* Compute loc(*,npmax_g)
*-----------------------
         myelem_ind =0 
         call lonumerate_lst_co(myrank,nprocs,
     $              loc,np,nelem,feel(np_ielem),metis,
     $              myelem_ind,
     $              NOTYETFLAG )
*     
         if(myelem .eq. 0) then
            myelem = myelem_ind
            if(myelem .EQ. 0) then
               call abortexit(myrank,'MYELEM.EQ.0 (lonumerate_lst)')
            endif
         else
            if(myelem .ne. myelem_ind) then
             call abortexit(myrank,
     $                     'myelem.ne.myelem_ind(lonumerate_lst)')
            endif
         endif
*
 100  continue
 
*-------------------------------
* Compute loc(2,*),mynode
*-------------------------------
      do 200 i=1,npmax_g

         id   = loc(1,i)
         if(id .EQ. NOTYETFLAG) then
            call abortexit(myrank,
     $                    'loc(1,i).EQ.NOTYETFLAG(lonumerate_lst)')
         endif
*
         iptr = id + NIDPLUS
*
         icount(iptr) = icount(iptr)+1
         loc(2,i)     = icount(iptr)
*
 200  continue
*
      mynode = icount(myrank + NIDPLUS)
*
      return
      end
      subroutine lonumerate_lst_co(myrank,nprocs,
     $                             loc,np,nelem,ielem,metis,
     $                             myelem_ind,NOTYETFLAG)
*------------------------------------------------------------------
* Compute loc(1,*) data (node's PE assignment)
*------------------------------------------------------------------
      integer*4 myrank,nprocs
      integer*4 loc(2,*)
      integer*4 ielem(np,nelem)
      integer*4 metis(nelem)
      integer*4 myelem_ind
      integer*4 NOTYETFLAG
*------------------------------------------------------------------
      mypeid = myrank
*------------------------------------------------------------------
      do 200 i=1,nelem
*
* element No.i is belonging to PE-id   (id starts 0 to nPE-1)
*
         id = metis(i)
         if(id .eq. mypeid)  myelem_ind = myelem_ind + 1

         do 201 j=1,np
*
*     ipt is global node number
*     loc(1,ipt) contains the PE number of (No. ipt)'s node
*
*     the node belongs to the youngest number of PE 
*
            ipt = ielem(j,i)
*
*           NOTYETFLAG means it appears first time
*
*----------
* loc(1,x)
*----------
            if(loc(1,ipt) .eq. NOTYETFLAG  ) then
               loc(1,ipt) = id
            else
*
*  CHECK IF IT BELONGS TO MORE YOUNGER PE'S ELEMENT
*
               if(loc(1,ipt) .gt. id  ) then
                  loc(1,ipt) = id
               endif
*
            endif
 201     continue
 200  continue
*
      return
      end
