      subroutine p_solve_plset (rank,feelpara,neq_sub,B,
     $     srb,np_nsrequ,nsendnum,nrecvnum,
     $     npesum,nsesum,nresum,
     $     nsendkaz,nrecvkaz,nsendlist,nrecvlist,nsendtable,
     $     nrecvtable)  
*
*++++++++++++++++++++++++++++++
*     FEEL/P2/Cenju-3/MPI subprogram
*     Purpose : np_nsrequ(npesum) <->np_npsre
*             : summation of the values on the interface for 
*               solving
*++++++++++++++++++++++++++
*     
      implicit real*8 (a-h,o-z)
*
      real*4 feelpara(*)
*
      integer rank
*
      dimension B(neq_sub)
*
      dimension srb(nsesum+nresum)
      dimension np_nsrequ(npesum)
*
*
      dimension nsendkaz(npesum),nrecvkaz(npesum)
      dimension nsendtable(npesum),nrecvtable(npesum)
      dimension nsendlist(npesum),nrecvlist(npesum)
c
      call data_plus (rank,neq_sub,B,srb,
     $     feelpara(np_nsrequ(1)),
     $     nsendnum,nrecvnum,
     $     npesum,nsesum,nresum,nsendkaz,nrecvkaz,nsendlist,
     $     nrecvlist,nsendtable,nrecvtable)
*
      return
      end
