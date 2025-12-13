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
