      subroutine p_read_d_nset(iunit,nbdisum1,nbdisum2,
     $     nsyori,inset)
*++++++++++++++++++++++++++++++
*     FEEL/P2/Cenju-3/MPI subprogram
*++++++++++++++++++++++++++
*     
*     Read Dirichlet data from dat.PE@@@.X file
*
*+++++++++++++++++++++++++++
      implicit real*8 (a-h,o-z)
*
      character*20 fmt
*     
      dimension inset(nbdisum2,nbdisum1),nsyori(nbdisum1)
*
      write (fmt,8001) nbdisum2+1
 8001 format('(',i,'i8)')
*
      read (iunit,fmt) nsyori(1),(inset(j,1),j=1,nbdisum2)
      do 10 i=2,nbdisum1
         read (iunit,9001) ndummy
         read (iunit,fmt) nsyori(i),(inset(j,i),j=1,
     $        nbdisum2)
 10   continue
*
 9001 format(i8)
*
      return
      end
      
