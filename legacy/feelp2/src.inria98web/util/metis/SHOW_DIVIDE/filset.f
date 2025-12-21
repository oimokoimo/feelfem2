      subroutine filset
c ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
c     feel p2 fort77 program
c     Copyright(C) NEC Corporation 1993
c ======================================
c ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
c Date: Wed Jul 12 20:02:55 JST 1995
c User: Hidehiro Fujio
c ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
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
      io_in     = 10
      io_out    = 12
      io_stderr =  7
      open(unit=io_stderr,file='/dev/tty',status='UNKNOWN')
c
      open(unit=io_in,status='old',file='feel_dat')
      open(unit=io_out,file='feel_dat.wrt',status='UNKNOWN')
c
      io_edat = io_out  + 1
      io_node = io_edat + MAX_EDATSET
      io_num  = io_node + MAX_NODESET
      io_fem  = io_num  + MAX_NUMSET
      io_tmp  = io_fem  + MAX_SOLVE
*
c---------------------------------------
      return
      end
