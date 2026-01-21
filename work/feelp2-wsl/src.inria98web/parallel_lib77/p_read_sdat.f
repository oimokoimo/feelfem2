      subroutine p_read_sdat(nsendtable,nsendnum,nsendndkaz,
     $     feel,iunit,np_nsenod,npmaxsub,npesum,ipe,nsendlist)
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
      dimension nsendtable(npesum),nsendndkaz(npesum)
      dimension np_nsenod(npesum)
      dimension nsendlist(npesum)
*
      if (nsendlist(ipe).eq.1) then
         do 10 i=1,nsendnum
*     
            read (iunit,9001) nsendndkaz(i)
            nsdonum = nsendndkaz(i)
*
            call f_alloc (np_nsenod(i),'Read nsenod(i)',
     $           nsdonum,0)
*
            call p_read_pedatC (feel(np_nsenod(i)),
     $           nsdonum,nsendtable,i,iunit)
 10      continue
      end if
*
 9001 format(i8)
      return
      end

