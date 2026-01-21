      subroutine p_read_n_edat (iunit,nbnesum1,nbnesum2,
     $     ibsubelem)
*
*++++++++++++++++++++++++++++++
*     FEEL/P2/Cenju-3/MPI subprogram
*++++++++++++++++++++++++++
*     
*     Read Neumann data from dat.PE@@@.X file
*
*+++++++++++++++++++++++++++
      implicit real*8 (a-h,o-z)
*
      character*20 fmt
*
      dimension ibsubelem(nbnesum2,nbnesum1)
*
      write (fmt,8001) nbnesum2
 8001 format('(',i,'i8)')
      read (iunit,fmt) (ibsubelem(j,1),j=1,nbnesum2)
      do 10 i=2,nbnesum1
         read (iunit,9001) ndummy
         read (iunit,fmt) (ibsubelem(j,i),j=1,nbnesum2)
 10   continue
*
 9001 format(i8)
      return
      end
