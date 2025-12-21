      subroutine solve03(feel,x,y,fem_u,fem_v)
c ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
c     feel p2 fort77 program
c     Copyright(C) NEC Corporation 1993
c ======================================
c ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
c Date: 
c User: 
c ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
      implicit real*8 (a-h,o-z)
c --------------------------------------------------------------------
      parameter (MAX_FEEL = 0)
      parameter (MAX_DOMAIN = 0)
      parameter (MAX_EDATSET = 0)
      parameter (MAX_NODESET = 0)
      parameter (MAX_NUMSET = 0)
      parameter (MAX_EWISE  = 0)
      parameter (MAX_EWISE_INFO = 0)
      parameter (N_SOLVE_TYPES = 37)
c --------------------------------------------------------------------
c --------------------------------------------------------------------
      prameter (NEG = 1)
c --------------------------------------------------------------------
      real*4 feel(*)
      dimension x(*),y(*)
      dimension fem_u(*),fem_v(*)
*
      dimension i_edatno(NEG)
      dimension i_nodeless(NEG)
c --------------------------------------------------------------------
      common /feel_geo/ndim,npmax,ndomain,nedat,nnodeset,nnumdat
      common /feel_ctl/mode_ex,mode_output,idble_word,max_heap
      common /feel_var/nvars_fem,nvars_ewise,np_fem,np_ewise,np_work,
     &                 np_heap
      common /feel_fil/io_in,io_out,io_stderr,io_edat,io_node,io_num,
     &                 io_fem
      common /feel_dat/n_domain(MAX_DOMAIN),n_edat(MAX_EDATSET,3),
     &                 n_node(MAX_NODESET),n_num(MAX_NUMSET),
     &                 n_ewise(MAX_EWISE,2)
      common /feel_sol/n_make(N_SOLVE_TYPES)
c ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
c --------------------------------------------------------------------
c-----------------------------
c 1th elementの属性定義      
c-----------------------------
c     対応する要素節点データ番号
      i_edatno(1)  =  1
      i_nodeless(1)=  0
c --------------------------------------------------------------------
      np_now = np_work
*     IPD(*) = feel(np_ipd)
      np_ipd = np_now
      np_now = np_now + npmax * idble_word
      call array_check(np_now,1,'solve-3,ipd')
*
      if(n_sol(3) .ne. 0) goto 2000
*
*------------------------------------------
* 連立一次方程式構成の為の情報配列作成
*------------------------------------------
      call zeroi(feel(np_ipd),npmax)
*
      np_push = np_now
*-------------------
      np_now = np_push
      np_ielem = no_now
      iedatno = i_edatno(1)
      np_now = np_now+n_edat(iedatno,1)*(n_edat(iedatno,2)+1)
      call array_check(np_now ,1, 'solve3')
      call elem44_4480090a(feel(np_ipd),iedatno,feel(np_ielem))
      np_now = np_push
c 累積自由度の計算
      call makeipd(feel(ipd),npmax)
