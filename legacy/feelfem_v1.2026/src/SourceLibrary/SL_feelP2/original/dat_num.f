      subroutine dat_num(dat)
c ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
c     feel p2 fort77 program
c     Copyright(C) NEC Corporation 1993
c ======================================
      implicit real*8 (a-h,o-z)
c --------------------------------------------------------------------
      parameter (MAX_FEEL = 10000000)
      parameter (MAX_DOMAIN = 10)
      parameter (MAX_EDATSET = 38)
      parameter (MAX_NODESET = 20)
      parameter (MAX_NUMSET = 10)
      parameter (MAX_EWISE  = 20)
      parameter (MAX_IP    = 5)
      parameter (MAX_SOLVE = 1)
c --------------------------------------------------------------------
      dimension dat(*)
c --------------------------------------------------------------------
      common /feel_geo/ndim,npmax,ndomain,nedat,nnodeset,nnumdat,nip
      common /feel_ctl/mode_ex,mode_output,max_heap
      common /feel_var/np_x,np_y,np_z,nvars_fem,nvars_ewise,
     &                 np_fem,np_ewise,np_heap
      common /feel_fil/io_in,io_tmp,io_out,io_stderr,
     &                 io_edat,io_node,io_num,io_fem
      common /feel_dat/n_edat(MAX_EDATSET,3),
     &                 n_nset(MAX_NODESET,2),n_num(MAX_NUMSET),
     &                 n_ewise(MAX_EWISE,2),n_nodeno(MAX_IP)
      common /feel_sol/n_sstat(MAX_SOLVE),n_smaxp(MAX_SOLVE)
c ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
      read(io_in,9001) no,nsetno
c   
c  no     Nodeset number
c  nsetno Number of nodes
c
 9001 format(2i8)
c
      if(no .gt. MAX_NODESET .or. no .le. 0) goto 8901
      ns = n_nset(no,1)
      if(ns .eq. 0) goto 8902
c
      if(ns*2 + np_work_get_falloc() .gt. np_heap) goto 8900
c
      n_num(no) = nsetno
c
      iunit = io_num + no - 1
      open(unit=iunit,status='scratch',form='unformatted')
      call closefil(iunit)
c
      read(io_in,9010,end=8903) (dat(i),i=1,ns)
 9010 format((5e14.5))
c
      write(iunit) ns,(dat(i),i=1,ns)
c
      return
c---------------------------------------------------------
 8900 write(io_stderr,*) 'no space left(inp_nset)'
      write(io_stderr,*) ns*2+np_work_get_falloc()-np_heap
      stop 'inp_nset'
c----------------------
 8901 write(io_stderr,*) 'node set no error(数値データ入力時)'
      stop 'inp_nset'
c----------------------
 8902 write(io_stderr,*) '指定した節点集合データが定義されない'
      stop 'inp_nset'
c----------------------
 8903 write(io_stderr,*) 'node set data error'
      stop 'inp_nset'
c---------------------------------------------------------
      end
