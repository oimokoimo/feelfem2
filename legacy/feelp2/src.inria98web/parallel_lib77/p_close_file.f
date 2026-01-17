      subroutine p_close_file
c
      implicit real*8 (a-h,o-z)
c
      integer p_rank
      common /feel_geo/ndim,npmax,ndomain,nedat,nnodeset,nnumdat,nip
      common /feel_fil/io_in,io_tmp,io_out,io_stderr,
     &                 io_edat,io_node,io_num,io_fem
      common /feel_para/npe,p_rank,ncont1,ncont2
c
      do 10 no=1,nedat
         close (io_edat + no - 1)
 10   continue
c
      do 20 no=1,nnodeset
         close (io_node + no -1)
 20   continue
c
      close (io_stderr)
      close (io_in)
      close (io_out)
c
      do 30 no = 1 , nnumdat
         close (io_num+no-1) 
 30   continue
c
      return
      end
