      subroutine solve01(feel,x,y,fem_u,fem_v,fem_p,ewise_p,istat)
c----------------------------------------------------------------
c     feel は 全体配列
c     x,y,z,は次元によって決定する
c     fem_* は fem変数
c     ew_*  は ewise変数
c     -----------------------------------------------
c     istat は、solve文に関するstatusを示す
c        0  全初期化
c        1  メッシュの構成が変化
c        2  LU分解済み(線形問題、LU分解不要) 
c     -----------------------------------------------
c     
c     
c     
c     
c     
c----------------------------------------------------------------
      implicit real*8 (a-h,o-z)
c --------------------------------------------------------------------
      parameter (MAX_FEEL = 40000)
      parameter (MAX_ELEMG = 10)
      parameter (MAX_NODESET = 20)
      parameter (MAX_NUMSET = 20)
      parameter (MAX_EWISE  = 10)
      parameter (MAX_EWISE_INFO = 12)
c --------------------------------------------------------------------
c  問題定義パラメータ文
c --------------------------------------------------------------------
      parameter (NEG = 3)        要素グループ数
      parameter (NREG_DOMX = 1)  要素番号のパラメータ文
      parameter (NREG_DOMY = 2)
      parameter (NREG_DOMZ = 3)
c --------------------------------------------------------------------
      real*4    feel(*)
c
      dimension x(*),y(*)
      dimension fem_u(*),fem_v(*),fem_p(*)
      dimension ewise_p(*)
c --------------------------------------------------------------------
      dimension IENO(NEG)    要素番号        →  データ文
c --------------------------------------------------------------------
      data    IENO/NREG_DOMX,NREG_DOMY,NREG_DOMZ/
c --------------------------------------------------------------------
      common /feel_geo/ndim,npmax,nelemg,nnodeset,nnumdat
      common /feel_ctl/mode_ex,mode_output,idble_word,max_heap
      common /feel_var/nvars_fem,nvars_ewise,np_fem,np_ewise,np_work,
     &                 np_heap
      common /feel_fil/io_in,io_out,io_stderr,io_elem,io_node,io_num,
     &                 io_fem
      common /feel_dat/n_elem(MAX_ELEMG,3),n_node(MAX_NODESET),
     &                 n_num(MAX_NUMSET),
     &                 n_ewise(MAX_EWISE,MAX_EWISE_INFO)
c --------------------------------------------------------------------
c     節点
c --------------------------------------------------------------------
      if(iremake_flag .eq. 1) then
c
c       読み込み対象 
c       ipd 累積節点自由度
c       KLD スカイライン情報配列
c
c       要素情報配列の読み込みは、各要素組み立て時に…
c  
c
      endif
c---------------------------------------------------------------------
      np_now = np_work
      np_ipd = np_now
      np_now = np_now + npmax 
c
      call zeroi(feel(np_ipd),npmax)
c
      nn = 0
      do 5  i=1,NEG
         nn = nn + n_elem(IENO(i),3)
 5    continue
c
      if( nn .ne. 0) then
c     
c     ied(*) は要素自由度の方程式番号を求める
c     iewise(*)を作る為の作業用配列
c     
         np_ied = np_now
         np_now = np_now + npmax
c         
      endif

      np_push = np_now           ;ベース
c
      do 10 i=1,NEG
c
         ns = n_elem(IENO(i),1)   ; 要素数 
         nf = n_elem(IENO(i),2)   ; 要素内節点数
         nn = n_elem(IENO(i),3)   ; 節点なし自由度
         nr = n_elem(IENO(i),4)   ; 領域番号

         np_now   = np_push
c
c ief(*) は局所節点毎自由度
c
         np_ief   = np_now 
         np_now   = np_now + nf
c
c ielem(nf,*) は要素節点対応行列
c
         np_ielem = np_now
         np_now   = np_now + ns*(nf + 1) ;MATNOの分
c-----------------------------------------------------
c 節点less自由度のある場合の領域取得
c-----------------------------------------------------
c     
         call array_check( np_now , i , 'making IPD array')      
         
c全自由度の計算
c
c  異種要素接合時にも自由度等の整合性がとれていること
c
         call g_edat1(IENO(i),feel(np_ief),feel(np_ielem),ns,nf,nf+1)
c
         

cスカイライン情報配列の作成



         subroutine g_edat1(no,ief,ielem,ns,nf,nf1)
         implicit real*8 (a-h,o-z)
c
         dimension 
