      subroutine p_read_pedatB (iunit,nsum,nnod)
*
*++++++++++++++++++++++++++
*  FEEL /P2/Cenju-3/MPI subprogram
*++++++++++++++++++++++++++
      implicit real*8 (a-h,o-z)
*
      dimension nnod(nsum)
*
      do 10 i=1,nsum
         read (iunit,9001) nnod(i)
 10   continue
 9001 format(i8)
      return
      end 


