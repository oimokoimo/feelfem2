      subroutine dat_edat(no,nelem,np,ielem,matno)
c ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
c     feel p2 fort77 program
c     Copyright(C) NEC Corporation 1993
c ======================================
      implicit real*8 (a-h,o-z)
c --------------------------------------------------------------------
      parameter (MAX_FEEL = 2000000)
      parameter (MAX_DOMAIN = 10)
      parameter (MAX_EDATSET = 38)
      parameter (MAX_NODESET = 20)
      parameter (MAX_NUMSET = 20)
      parameter (MAX_EWISE  = 20)
      parameter (MAX_IP    = 100)
      parameter (MAX_SOLVE = 1)
c --------------------------------------------------------------------
c --------------------------------------------------------------------
      dimension ielem(np,nelem),matno(nelem)
      character*20 fmt
*
c --------------------------------------------------------------------
      common /feel_geo/ndim,npmax,ndomain,nedat,nnodeset,nnumdat,nip
      common /feel_ctl/mode_ex,mode_output,max_heap
      common /feel_var/np_work,np_x,np_y,np_z,nvars_fem,nvars_ewise,
     &                 np_fem,np_ewise,np_heap
      common /feel_fil/io_in,io_tmp,io_out,io_stderr,
     &                 io_edat,io_node,io_num,io_fem
      common /feel_dat/n_edat(MAX_EDATSET,3),
     &                 n_nset(MAX_NODESET,2),n_num(MAX_NUMSET),
     &                 n_ewise(MAX_EWISE,2),n_nodeno(MAX_IP)
      common /feel_sol/n_sstat(MAX_SOLVE)
c --------------------------------------------------------------------
*
      iunit = io_edat + no - 1
      open(unit=iunit,status='scratch',form='unformatted')
*
      write(fmt,9003) np+1
 9003 format('(',I2,'I8)')
*
      do 100 i=1,nelem
        read(io_in,fmt,end=8902) (ielem(j,i),j=1,np),matno(i)
  100 continue
*
      write(iunit) nelem,np
      write(iunit) ((ielem(i,j),i=1,np),j=1,nelem)
      write(iunit) (matno(i),i=1,nelem)
*
      return
*----------------------------------------------------------------------
 8902 write(io_stderr,*) 'edat data error'
      stop 'inp_edat'
*----------------------------------------------------------------------
      end
