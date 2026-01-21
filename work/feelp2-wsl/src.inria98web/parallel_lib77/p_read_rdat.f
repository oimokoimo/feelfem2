      subroutine p_read_rdat(nrecvtable,nrecvnum,nrecvndkaz,
     $     feel,iunit,np_nrenod,npmaxsub,npesum,
     $     ipe,nrecvlist)
*++++++++++++++++++++++++++++++
*     FEEL/P2/Cenju-3/MPI subprogram
*++++++++++++++++++++++++++
*     Read node set data from dat.PE@@@.X file
*
*++++++++++++++++++++++++++
      implicit real*8 (a-h,o-z)
*-------------------------
      real*4 feel(*)
*
      dimension nrecvtable(npesum),nrecvndkaz(npesum)
      dimension np_nrenod(npesum)
      dimension nrecvlist(npesum)
*
      if (nrecvlist(ipe).eq.1) then
         do 10 i=1,nrecvnum
*     
            read (iunit,9001) nrecvndkaz(i)
            nrdonum = nrecvndkaz(i)
*
            call f_alloc(np_nrenod(i),'Read nrenod(i)',
     $           nrdonum,0)
*
            call p_read_pedatC (feel(np_nrenod(i)),
     $           nrdonum,nrecvtable,i,iunit)
 10      continue
      end if
*
 9001 format(i8)
      return
      end
