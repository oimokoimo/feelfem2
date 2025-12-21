      program data_main
*+++++++++++++++++++++++++++++
*     並列用データ生成ツール
*
*+++++++++++++++++++++++++++++
      implicit real*8(a-h,o-z)
*
      parameter (nskai=6)
*+++++++++++++ FEELからのデータ +++++
c      parameter (MAX_FEEL=2500000)
      parameter (MAX_FEEL=10000000)
c8/14      parameter (MAX_FEEL=25000000)
      parameter (MAX_DOMAIN=10)
      parameter (MAX_EDATSET=38)
      parameter (MAX_NODESET=20)
      parameter (MAX_NUMSET = 20)
      parameter (MAX_EWISE  = 20)
*+++++++++++++ FEELからのデータ +++++
      real*4 feelpara(MAX_FEEL)
      real*8 dfeelpara
*
      equivalence (feelpara, dfeelpara)
*
      common /feel_dat/ n_edat(MAX_EDATSET,3),
     $     n_nset(MAX_NODESET,2),
     $     n_ewise(MAX_EWISE,2)
      common /feel_var/np_work,np_x,np_y,np_z,nvars_fem,
     $     nvars_ewise,
     &     np_fem,np_ewise,np_heap
      common /feel_ctl/mode_ex,mode_output,max_heap
*
ccccccccccccccccccccc3/31時間計測
cc         call report ('initial')
cccccccccccccccccc3/31時間計測
      np_work    = 1
      np_heap    = MAX_FEEL
      max_heap   = 1
*
*     ------------
*     feel_datの読み込みおよび必要なデータ生成
*     ------------
      call read_data(feelpara,nskai,nmatrix)
*
ccccccccccccccccccccc3/31時間計測
ccc         call report ('after read_data')
cccccccccccccccccc3/31時間計測
*
      end

