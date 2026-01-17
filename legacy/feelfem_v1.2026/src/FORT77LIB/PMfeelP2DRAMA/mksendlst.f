      subroutine mksendlst(feel,myrank,nprocs,
     $                     enptr ,con,nelem,npmax,
     $                     eflag,nflag  ,
     $                     ne2send,nconsiz,nn2send        )
*----------------------------------------------------------
*     Count the total number and necessary words to send 
*     element information
*
*     STEP 1: Perform message passing for exchanging required nodes 
*             information
*
*     STEP 2: With the result of STEP1, Make flag array for send list
*   
*    (elements required to send means there is another
*     processors' nodes                               )
*
*     Send Element = There is another PE's nodes.
*
*     ne2send     number of elements to send
*     nconsiz     send 'con' array size  -> con(2,nconsiz)
*     nn2send     number of my node to send
*----------------------------------------------------------
      real*4  feel(*)
      integer enptr(2,*),con(2,*)
      integer eflag(*),nflag(*)
*----------------------
* initialization
*---------------
      mypeid      = myrank
*
      ne2send     = 0
      nconsiz     = 0
      nn2send     = 0
*--------------
      do 1 i=1,nelem
         eflag(i) = 0
 1    continue
      do 2 i=1,npmax
         nflag(i) = 0
 2    continue
*----------------------

*------------------------------------------------------------------
* STEP 1-1
* Count the other PE's node in my element
* (In current implementation, duplication of sending nodes occures)
* In addition, Calculation of eflag(*) array 
*------------------------------------------------------------------
      nodeinother = 0
*
      do 100 i=1,nelem

         ipos_from = enptr(1,i  )
         ipos_end  = enptr(1,i+1)-1

         do 101 j=ipos_from,ipos_end
            if(con(2,j) .NE. mypeid) then
               nodeinother = nodeinother + 1
               eflag(i)    = 1
            endif
 101     continue
 100  continue
*-------------------------------------------------------------------
      call f_alloc_push
      if(nodeinother .NE. 0 ) then
         call f_alloc(np_ndreqlst,'ndreqlst',nodeinother*2,0,0)
      else
         np_ndreqlst = 1
         GOTO 152
      endif
*-------------------------------------------------------------------
      iptr = 0
      do 150 i=1,nelem
         ipos_from = enptr(1,i  )
         ipos_end  = enptr(1,i+1)-1

         do 151 j=ipos_from,ipos_end
            if(con(2,j) .NE. mypeid) then
               iptr = iptr + 1
               call feelset_npi(feel,np_ndreqlst,(iptr-1)*2+1,con(1,j))
               call feelset_npi(feel,np_ndreqlst,(iptr-1)*2+2,con(2,j))
            endif
 151     continue
 150  continue
 152  continue
*-------------------------------------------------------------------
* STEP 1-2  Gather/scatter required node information
* These node information necessary for other PE's element
*-------------------------------------------------------------------
      call feelgathervbcast(myrank,nprocs,feel,
     $                      nodeinother*2,feel(np_ndreqlst),
     $                      np_ibuf,np_counts,np_displs     )
*-------------------------------------------------------------------
* STEP 1-3   SET nflag list for other PE's request
*-------------------------------------------------------------------
      call mksendlst_sub(mypeid,nprocs,nflag,
     $     feel(np_ibuf),feel(np_counts),feel(np_displs))
*-------------------------------------------------------------------
* STEP 1-4   clear the buffer for work array
*-------------------------------------------------------------------
      call f_alloc_pop

*-------------------------------------------------------------------
* STEP 2-1 Count send buffer information for element
*-------------------------------------------------------------------
      do 200 i=1,nelem

         if(eflag(i) .EQ. 1) then
            ne2send     = ne2send + 1
            nconsiz     = nconsiz + (ipos_end-ipos_from+1)
         endif
 200  continue

*-------------------------------------------------------------------
* STEP 2-2 Count send buffer information for my node
*-------------------------------------------------------------------
      do 210 i=1,nelem
         
         if(eflag(i) .NE. 1) goto 210
         
         ipos_from = enptr(1,i  )
         ipos_end  = enptr(1,i+1)-1

         do 211 j=ipos_from,ipos_end
            if(con(2,j) .EQ. mypeid) then
               nflag(con(1,j))    = 1
            endif
 211     continue
 210  continue
*-------------------------------------------------------------------
* STEP 2-3 Count total nodes to send
*-------------------------------------------------------------------
      do 300 i=1,npmax
         nn2send = nn2send + nflag(i)
 300  continue
*---
      return
      end
      subroutine mksendlst_sub(mypeid,nprocs,nflag,
     $                         ibuf,counts,displs    )
*--------------------------------------------------------------------
* 2000/05/30 (feelfem_stokes version (name changed sub1 to sub))
*
* Set nflag for request from other PE's element information
* (Already gather/scatterd)
* 
* INPUT:  mypeid
*         nprocs
*         ibuf(*)
*         counts(*)
*         displs(*)
*         
* OUTPUT: nflag(*)
*
*--------------------------------------------------------------------
      integer*4 nflag(*)

      dimension ibuf(*)
      integer   counts(*)
      integer   displs(*)
*--------------------------------------------------------------------
      do 100 i=1,nprocs

         ncts  = counts(i)
         ncts  = ncts / 2
         if(ncts *2 .NE. counts(i)) then
            call abortexit(mypeid,'MKSENDLST_sub1')
         endif
*
         if(ncts .eq. 0) goto 100
*
         nbase = displs(i)
*
         do 200 j=1,ncts
            npeid   = ibuf(nbase+(j-1)*2+2)
            if(mypeid .ne. npeid) goto 200

            node_no = ibuf(nbase+(j-1)*2+1)
            nflag(node_no) = 1
 200     continue
*
 100  continue
*
      return
      end
