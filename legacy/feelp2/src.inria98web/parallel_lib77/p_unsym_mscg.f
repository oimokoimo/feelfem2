      subroutine p_unsym_mscg(rank,feelpara,A,MJ,neq_sub,JA,JDP,
     $     B,U,naisum,naieq,nintotal,ninner,npesum,nsendnum,
     $     nrecvnum,nsesum,nresum,nsendlist,nrecvlist,
     $     nsendkaz,nrecvkaz,nsendtable,nrecvtable,
     $     np_nsrequ,srb,eps,IPM,IT,W,rnorm,
     $     KTI)
c
c---------------------------------------------------
c     Scaled BiCGSTAB method (two dimensional array)
c---------------------------------------------------
c
      implicit real*8 (a-h,o-z)
      integer rank
*
      real*4 feelpara(*)
*
      dimension A(neq_sub,MJ),JA(neq_sub,MJ),B(neq_sub)
      dimension U(neq_sub)
*
      dimension naieq(naisum)
      dimension ninner(nintotal)
      dimension nsendlist(npesum),nrecvlist(npesum)
      dimension nsendkaz(npesum),nrecvkaz(npesum)
      dimension nsendtable(npesum),nrecvtable(npesum)
      dimension np_nsrequ(npesum)
      dimension srb(nsesum+nresum)
c
      dimension IPM(*)
c
      dimension W(neq_sub,8)
*
      if (IPM(1).eq.0) then
*
*-----------------------
*     IPM(1)=0 -> diagonal scaling
*----------------------
*     Unsymmetric solver : BiCGSTAB method 
*                        : p_sbicgstab1
*---------------------
*
c
         call p_msbicg_stab (rank,npesum,U,
     $        B,neq_sub,
     $        naisum,naieq,ninner,
     $        nintotal,IT,A,JA,MJ,
     $        W,eps,
     $        IPM,
     $        srb,feelpara(np_nsrequ(1)),nsendnum,
     $        nrecvnum,
     $        nsesum,nresum,rnorm,nsendlist,nrecvlist,
     $        nsendkaz,nrecvkaz,nsendtable,nrecvtable,
     $        JDP,KTI,feelpara)
*
*
      end if
c
      return
      end





