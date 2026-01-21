      subroutine p_read_prdat (iunit,innersum,innernd)
*
*++++++++++++++++++++++++++++++
*     FEEL/P2/Cenju-3/MPI subprogram
*     Read node set data from dat.PE@@@.X file
*     innersum   : number of nodes
*     innernd(*): node number array
*++++++++++++++++++++++++++
      implicit real*8 (a-h,o-z)
      dimension innernd(innersum)
*
      do 10 i=1,innersum
         read (iunit,9001) innernd(i)
 10   continue
*
 9001 format(i8)
      return
      end      
