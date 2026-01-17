      subroutine p_read_pedatC(nsrnod,nsum,ntbe,number,
     $     iunit)
*
*++++++++++++++++++++++++++++++
*     FEEL/P2/Cenju-3/MPI subprogram
*++++++++++++++++++++++++++
*     Read node set data from dat.PE@@@.X file
*     nsum   : number of nodes
*     nsrnod(*): node number array
*     ntbe(*): subdomain number array
*++++++++++++++++++++++++++
      implicit real*8 (a-h,o-z)
*---------------------------
*     
      dimension nsrnod(nsum)
      dimension ntbe(*)
*
      do 10 i=1,nsum
         read(iunit,9001) ntbe(number),nsrnod(i)
 10   continue
*
 9001 format(2i8)
      return
      end
