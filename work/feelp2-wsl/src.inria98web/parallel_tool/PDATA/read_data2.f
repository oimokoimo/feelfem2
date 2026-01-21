      subroutine read_data2 (feelpara,np_ielem,nmatrix,
     $     nedat,np_matno,np_ibelem,np_ibmatno,
     $     np_inset,nodeset,ndim,npmax,
     $     nbb,nankai,
     $     np_ilnode,np_ignode)
*
      implicit real*8 (a-h,o-z)
*
      parameter (MAX_FEEL=2000000)
      parameter (MAX_DOMAIN=10)
      parameter (MAX_EDATSET=38)
      parameter (MAX_NODESET=20)
      parameter (MAX_NUMSET = 20)
      parameter (MAX_EWISE  = 20)
*
      character*10 word
      real*4 feelpara(*)
*
      dimension np_npesubw(MAX_EDATSET)
      dimension np_npenumw(MAX_EDATSET)
      dimension np_npelocw(MAX_EDATSET)
      dimension np_npeintw(MAX_EDATSET)
      dimension np_npeaiw(MAX_EDATSET)
      dimension np_jainw(MAX_EDATSET)
      dimension mk1(MAX_EDATSET)
      dimension mk2(MAX_EDATSET)
*
*     +++++data_sdrv1用++++++
      dimension np_nreadsd(MAX_EDATSET)
      dimension np_nreadrv(MAX_EDATSET)
      dimension np_nsendlist(MAX_EDATSET)
      dimension np_nrecvlist(MAX_EDATSET)
*
*     ++++ data_prod用+++++++
      dimension np_ninner(MAX_EDATSET)
*     
*     ++++++data_dcond1用 ++++++
      dimension np_ndikaz(MAX_NODESET)
*     ++++++data_ncond1用 ++++++
      dimension np_neukaz(MAX_EDATSET)
*
      dimension np_ilnode(nmatrix),np_ignode(nmatrix)
      dimension nbb(0:2**nankai)
      dimension np_ielem(nmatrix),np_matno(nmatrix)
c8/9修正
      dimension np_ibelem(nedat)
      dimension np_ibmatno(nedat)
c8/9修正
c8/9修正
      dimension np_inset(*)
c8/9修正
*
*
      common /feel_dat/ n_edat(MAX_EDATSET,3),
     $     n_nset(MAX_NODESET,2),
     $     n_ewise(MAX_EWISE,2)
*
      common /feel_var/np_work,np_x,np_y,np_z,nvars_fem,
     $     nvars_ewise,
     &     np_fem,np_ewise,np_heap
      common /feel_ctl/mode_ex,mode_output,max_heap
*
*     ------ 読み込むEDAT集合の数の初期化 ----
*     最初から全体剛性行列用EDAT集合があると仮定！！！！
      numedat=0
      numnod=0
      numnset=0
 8000 continue
      read (15,9000) word
 9000 format(a4)
*
*+++++++2次元要素の対応表を読む++++++++++
*     全体剛性行列用のEDAT集合を読む。
      if (word.eq.'EDAT') then
         numedat=numedat+1
*
         read (15,9001) no,nelem,np
 9001    format(3i8)
*     
         n_edat(no,1)=nelem
         n_edat(no,2)=np
*     
         if (numedat.le.nmatrix) then
*
            call f_alloc (np_ielem(numedat),'Read ielem',
     $           nelem*np,0)
*
            call f_alloc (np_matno(numedat),'Read matno',
     $           nelem,0)
*     
            call read_edat (feelpara(np_ielem(numedat)),
     $           nelem,np,feelpara(np_matno(numedat)))
*            
         else if (numedat.gt.nmatrix) then
*     
*     -----境界要素の読み込み ---
*
            call f_alloc (np_ibelem(numedat-nmatrix),
     $           'Read ibelem',
     $           nelem*np,0)
            call f_alloc (np_ibmatno(numedat-nmatrix),
     $           'Read ibmatno',
     $           nelem,0)
            call read_edat (feelpara(np_ibelem(numedat-nmatrix)),
     $           nelem,np,
     $           feelpara(np_ibmatno(numedat-nmatrix)))
*
         end if
      end if
*
      if (word.eq.'NODE') then
*     節点データ(節点座標値を読み込む)
*     
         numnod=numnod+1
         if (mod(np_work,2).eq.0) then
            np_x=np_work+1
            np_work=np_work+1
         else if (mod(np_work,2).eq.1) then
            np_x=np_work
         end if
*
         np_y=np_x+(npmax*2)
         np_z=np_y+(npmax*2)
*
         if (ndim.eq.1) np_work=np_y
         if (ndim.eq.2) np_work=np_z
         if (ndim.eq.3) np_work=np_z+(npmax*2)
*
         if (ndim.eq.1) call read_node1(feelpara(np_x),
     $        npmax)
         if (ndim.eq.2) call read_node2(feelpara(np_x),
     $        feelpara(np_y),npmax)
         if (ndim.eq.3) call read_node3(feelpara(np_x),
     $        feelpara(np_y),feelpara(np_z),npmax)
      end if
*
      if (word.eq.'NSET') then
         numnset=numnset+1
         read (15,'(3i8)') no,nodes,np
*
         if(no .lt. 1 .or. no .gt.nodeset) then
            write(*,*) 'nodeset no = ',no
            stop 'nodeset error'
         endif
*
         n_nset(no,1)=nodes
         n_nset(no,2)=np
*
         call f_alloc (np_inset(no),'Read inset',
     $        nodes*np,0)
         call read_nset (feelpara(np_inset(no)),
     $        nodes,np)
      end if
*
*     NODE集合は1つと仮定している。
      if ((numnset.lt.nodeset).or.(numedat.lt.nedat).or.
     $     (numnod.lt.1)) go to 8000
*
      close (15)
*
      do 1 i=1,(2**nankai+1)/6
         read (16,9011) (nbb(k),k=(i-1)*6,i*6-1)
 1    continue
*
      if (((2**nankai+1)/6)*6.le.2**nankai) then
         read (16,9011) (nbb(k),k=((2**nankai+1)/6)*6,
     $        2**nankai)
      end if
 9011 format(6i8)
*
*     全要素数
      nelem=nbb(2**nankai)
*     全部分領域数
      npesum=2**nankai
*
      call f_alloc (np_ngru,'Read ngru',nelem,0)
      call f_alloc (np_nzoku,'Read nzoku',nelem,0)
*
      call read_mesh (feelpara(np_ngru),feelpara(np_nzoku),
     $     nelem,nankai)
*     
      close (16)
ccccc9/18付け加えた。
      do 1000 i=1,nmatrix
*------------------------------------------
*     feel_datの各PE版のファイル'dat.PE*'オープン
*----------------------------------------
      do 5 iw=1,npesum
         mkar1=(iw-1)/100
         mkar2=(iw-1-mkar1*100)/10
         mkar3=iw-1-mkar1*100-mkar2*10
         if (iw.le.10) then
            open (14+iw+5*npesum,file='dat.PE'//char(48+mkar3)
     $           //'.'//char(48+i))
         else if ((iw.gt.10).and.
     $           (iw.le.100)) then
            open (14+iw+5*npesum,file='dat.PE'
     $           //char(48+mkar2)//
     $           char(48+mkar3)//'.'//char(48+i))
         else if ((iw.gt.100).and.
     $           (iw.le.1000)) then
            open (14+iw+5*npesum,file='dat.PE'
     $           //char(48+mkar1)//char(48+mkar2)//
     $           char(48+mkar3)//'.'//char(48+i))
         else if (iw.gt.1000) then
            stop 'iw over 1000'
         end if
 5    continue
*     +++++++++++++++++++++++++++++++++++++++++++
*     npos,nelを決定する。
*     
*     ++++++++++++++++++++++++++++++++++++++++++++
      call f_alloc (np_nel,'Read nel',npesum,0)
      call f_alloc (np_npos,'Read npos',npmax*(1+npesum),0)      
      call f_alloc (np_nsuu,'Read nsuu',npmax,0)
cccこの部分書き替え9/19
ccc      do 10 i=1,nmatrix
cccこの部分書き替え9/19
         neelem=n_edat(i,1)
         nenode=n_edat(i,2)
*
         call f_alloc (np_ignode(i),'Read ignode',
     $        nenode*nelem,0)
*
         call data_num0 (feelpara,feelpara(np_ielem(i)),
     $        feelpara(np_ngru),feelpara(np_nzoku),
     $        feelpara(np_npos),nbb,npesum,nelem,
     $        feelpara(np_nel),i,feelpara(np_nsuu),
     $        feelpara(np_ignode(i)),neelem,nenode,
     $        npmax)
cccこの部分書き替え9/19
ccc 10   continue
cccこの部分書き替え9/19
*
      call f_alloc (np_mryo,'Read mryo',npesum,0)
      call f_alloc (np_ia,'Read ia',npmax*npesum,0)
*
      call data_num1 (feelpara(np_npos),feelpara(np_nsuu),
     $     feelpara(np_mryo),feelpara(np_ia),npmax,
     $     npesum)
*     ++++++++++++++++++++++++++++++++++++++++
*     各全体剛性行列用EDAT集合に対して
*     ilnode,を作る。
*     +++++++++++++++++++++++++++++++++++++++
*
cccこの部分書き替え9/19
ccc      do 20 i=1,nmatrix
cccこの部分書き替え9/19
         neelem=n_edat(i,1)
         nenode=n_edat(i,2)
         call f_alloc (np_ilnode(i),'Read ilnode',
     $        nenode*neelem,0)
*
*     
         call data_num2 (feelpara,feelpara(np_nel),
     $        feelpara(np_ilnode(i)),feelpara(np_ia),
     $        feelpara(np_ielem(i)),nbb,
     $        feelpara(np_ignode(i)),feelpara(np_npos),
     $        feelpara(np_ngru),feelpara(np_nsuu),
     $        feelpara(np_mryo),
     $        npesum,nenode,nelem,npmax,neelem)
cccこの部分書き替え9/19
ccc 20   continue
cccこの部分書き替え9/19
*     
*    +++++++ 部分節点番号と全体節点番号との対応 ++++
*     nloglo(*,**)を決定する。
      call f_alloc (np_nloglo,'Read nloglo',npmax*npesum,0)
*
      call data_num3 (feelpara(np_nloglo),feelpara(np_ia),
     $     feelpara(np_npos),feelpara(np_nsuu),
     $     feelpara(np_mryo),npmax,npesum)
*
      call f_alloc (np_npesub,'Read npesub',1+npmax,0)
      call f_alloc (np_npenum,'Read npenum',npmax*npesum,0)
      call f_alloc (np_npeloc,'Read npeloc',npmax*npesum,0)
      call f_alloc (np_npeint,'Read npeint',npmax*npesum*2,0)
      call f_alloc (np_npeai,'Read npeai',npmax*2,0)
      call f_alloc (np_jain,'Read jain',1+npmax,0)
*
*     +++全体剛性行列用EDAT集合用のEDAT集合の和集合用データ 
*     +++++++++
      call data_eq1 (feelpara,feelpara(np_npos),feelpara(np_ia),
     $     feelpara(np_npesub),feelpara(np_npenum),
     $     feelpara(np_npeloc),feelpara(np_npeint),
     $     feelpara(np_npeai),feelpara(np_jain),npmax,npesum,
     $     nk1,nk2,feelpara(np_nsuu))
*
*     ++++各全体剛性行列用EDAT集合用のデータ++++
      call f_alloc (np_nfue,'Read nfue',1+npmax,0)
      call f_alloc (np_icheck,'Read icheck',npmax,0)
cccこの部分書き替え9/19
ccc      do 30 i=1,nmatrix
cccこの部分書き替え9/19
         neelem=n_edat(i,1)
         nenode=n_edat(i,2)
*
         call f_alloc (np_npesubw(i),'Read npesubw',
     $        1+npmax,0)
         call f_alloc (np_npenumw(i),'Read npenumw',
     $        npmax*npesum,0)
         call f_alloc (np_npelocw(i),'Read npelocw',
     $        npmax*npesum,0)
         call f_alloc (np_npeintw(i),'Read npeintw',
     $        npmax*npesum*2,0)
         call f_alloc (np_npeaiw(i),'Read npeaiw',
     $        npmax*2,0)
         call f_alloc (np_jainw(i),'Read jainw',
     $        1+npmax,0)
*
         call data_eq2 (feelpara,
     $        feelpara(np_npesubw(i)),feelpara(np_npenumw(i)),
     $        feelpara(np_npelocw(i)),feelpara(np_npeintw(i)),
     $        feelpara(np_npeaiw(i)),feelpara(np_jainw(i)),
     $        npmax,npesum,
     $        mk1(i),mk2(i),feelpara(np_ilnode(i)),
     $        feelpara(np_ignode(i)),neelem,nenode,nelem,
     $        feelpara(np_icheck),feelpara(np_nfue),nbb)
*
cccこの部分書き替え9/19
ccc 30   continue
cccこの部分書き替え9/19
*
*     +++++++++++++++
*     とりあえずdat.PE*用ファイルのformatに
*     従ってデータを一部書いていく。
*     +++++++++++++++
*     
      call data_wrt1 (ndim,npesum,nbb,feelpara(np_mryo),
     $     nmatrix,nedat,nodeset)
*
*
*
*     ++++各全体剛性行列用EDAT集合用のデータから
*     送信、受信用データ(以前のse1,re1.PE*データを作る。)
*
cccこの部分書き替え9/19
ccc      do 50 i=1,nmatrix 
cccこの部分書き替え9/19
         call f_alloc (np_nreadsd(i),'Read nreadsd',
     $        npesum,0)
         call f_alloc (np_nreadrv(i),'Read nreadrv',
     $        npesum,0)
         call f_alloc (np_nsendlist(i),'Read nsendlist',
     $        npesum,0)
         call f_alloc (np_nrecvlist(i),'Read nrecvlist',
     $        npesum,0)
         call data_sdrv1 (feelpara(np_nreadsd(i)),
     $        feelpara(np_nreadrv(i)),npesum,
     $        feelpara(np_jainw(i)),feelpara(np_npeintw(i)),
     $        npmax,feelpara(np_nsendlist(i)),
     $        feelpara(np_nrecvlist(i)),mk1(i))
*
*
cccこの部分書き替え9/19
ccc 50   continue
cccこの部分書き替え9/19
*     
*     +++++++++++++++++++++++++++
*     各部分領域に属す節点のx,y座標値を書く。
*     及び部分節点番号と全体節点番号との対応も書く。
*     +++++++++++++++++++++++++++
      if (ndim.ne.2) then
         stop 'xy error'
      end if
      call data_wrt2 (feelpara(np_x),feelpara(np_y),npmax,
     $     feelpara(np_mryo),npesum,feelpara(np_nloglo))
*
*
*     +++++++++++++++++++++++++
*     全体剛性行列用EDAT集合用nsendlist,nrecvlistを書く。
*     +++++++++++++++++++++++++
cccこの部分書き替え9/19
ccc      do 53 i=1,nmatrix
cccこの部分書き替え9/19
         call data_wrt3 (feelpara(np_nsendlist(i)),
     $        npesum)
cccこの部分書き替え9/19
ccc 53   continue
cccこの部分書き替え9/19
ccc      do 56 i=1,nmatrix
         call data_wrt3 (feelpara(np_nrecvlist(i)),npesum)
ccc 56   continue
cccこの部分書き替え9/19
*
*     
*     ++++++++++++++++++++++++
*     全体剛性行列用EDAT集合毎に各部分領域での要素内節点と
*     部分節点番号との対応及び要素材料番号
*     +++++++++++++++++++++++
      nelem=nbb(npesum)
cccこの部分書き替え9/19
ccc      do 58 i=1,nmatrix
cccこの部分書き替え9/19
         neelem=n_edat(i,1)
         nenode=n_edat(i,2)
         call data_wrt4 (feelpara(np_ilnode(i)),neelem,
     $        nenode,feelpara(np_matno(i)),nbb,npesum,
     $        nelem)
cccこの部分書き替え9/19
ccc 58   continue
cccこの部分書き替え9/19
*
*     ++++++++++++++++++++++++++++++++++++++++
*     部分要素番号と全体要素番号との対応を書く。
*     ++++++++++++++++++++++++++++++++++++++++
      call data_wrt5 (feelpara(np_ngru),nbb,
     $     npesum,nelem)
*
*     ++++++++
*     Dirichlet条件集合(NSET集合)のdat.PE*への書き込み
*     ndikaz(im)を求める。(im=1,nodeset)(これを先に行う)
*     +++++++
      do 55 im=1,nodeset
         nodes=n_nset(im,1)
         np=n_nset(im,2)
*
         call f_alloc (np_ndikaz(im),'Read ndikaz',
     $        npesum,0)
         call data_dcond0 (feelpara(np_inset(im)),im,
     $        feelpara(np_npesub),feelpara(np_npenum),
     $        npmax,npesum,feelpara(np_ndikaz(im)),
     $        nodes,np)
 55   continue         
*
      do 57 im=1,nodeset
         np=n_nset(im,2)
         call data_wrt6 (feelpara(np_ndikaz(im)),np,
     $        npesum)
 57   continue
*      
*++++++++++++++++++++++++++++++++
*     Neumann条件用データEDAT集合のdat.PE*への書き込み
*     neukaz(im)(im=1,nedat-nmatrix)を求める。
*+++++++++++++++++++++++++++++++
*
      do 65 im=1,nedat-nmatrix
         neelem=n_edat(im+nmatrix,1)
         nenode=n_edat(im+nmatrix,2)
*
         call f_alloc (np_neukaz(im),'Read neukaz',
     $        npesum,0)
*
         call data_ncond0 (feelpara(np_ibelem(im)),
     $        neelem,nenode,
     $        npmax,npesum,feelpara(np_npesub),
     $        feelpara(np_npenum),feelpara(np_neukaz(im)),
     $        im,ndim)

 65   continue
*     
*++++++++++++++++++++++++++++++++
*     Neumann条件用データEDAT集合のdat.PE*への書き込み
*     neukaz(im)(im=1,nedat-nmatrix)を書く。
*+++++++++++++++++++++++++++++++
      do 66 im=1,nedat-nmatrix
         nenode=n_edat(im+nmatrix,2)
*     
         call data_wrt6 (feelpara(np_neukaz(im)),nenode,
     $        npesum)
 66   continue
*     
**++++++++++++++++++++++++++++++++++++++++++++++++
*     --- 各部分領域上のインターフェース上の部分節点番号と
*        内点の部分節点番号の数 : nsum(2,npesum),nsum(1,npesum)
*     を計算し、かつファイルに落す。
*++++++++++++++++++++++++++++++++++++++++++++++++
      call f_alloc (np_nsum,'Read nsum',npesum*2,0)
*
      call data_aiin (feelpara,feelpara(np_npeint),
     $     feelpara(np_npeai),feelpara(np_jain),
     $     nk1,nk2,npesum,npmax,feelpara(np_nsum))
*
* +++++++++++++++++++++++++++++++
*     各全体剛性行列用EDAT集合に対して各部分領域に
*     属す送信、受信関係のデータをファイルに落す。
*     (以前のse2.PE*,re2.PE*の様なファイルを作成する。)
* ++++++++++++++++++++++++++++++
*-------------------------------------------
*     この辺のワーク領域は修正する必要があるぞー
*--------------------------------------------
      call f_alloc (np_ntable,'Read ntable',npesum,0)
      call f_alloc (np_nkrt,'Read nkrt',npesum,0)
      call f_alloc (np_nlsd,'Read nlsd',npmax,0)
      call f_alloc (np_nsub,'Read nsub',npmax,0)
      call f_alloc (np_lread,'Read lread',2*npesum,0)
      call f_alloc (np_mcheban,'Read mcheban',npesum,0)
      call f_alloc (np_nsequ,'Read nsequ',npmax*npesum,0)
cccこの部分書き替え9/19
ccc      do 67 i=1,nmatrix
cccこの部分書き替え9/19
         call data_sdrv2 (feelpara(np_nsendlist(i)),
     $        feelpara(np_nrecvlist(i)),feelpara(np_nreadsd(i)),
     $        feelpara(np_nreadrv(i)),npesum,npmax,
     $        feelpara(np_ntable),feelpara(np_nkrt),
     $        feelpara(np_nlsd),feelpara(np_nsub),
     $        feelpara(np_lread),feelpara(np_icheck),
     $        feelpara(np_mcheban),feelpara(np_nsequ))
cccこの部分書き替え9/19
ccc 67   continue
cccこの部分書き替え9/19
*
*
*     +++++++++++++++++++++++++++++
*     ベクトルの内積に必要なデータをファイルに落す
*     ++++++++++++++++++++++++++++++
cccこの部分書き替え9/19
ccc      do 68 i=1,nmatrix
cccこの部分書き替え9/19
*
         call f_alloc (np_ninner(i),'Read ninner',
     $        npmax,0)
*
         call data_prod(npmax,npesum,feelpara(np_nreadrv(i)),
     $        feelpara(np_nrecvlist(i)),feelpara(np_ninner(i)),
     $        feelpara(np_icheck))
 68   continue
*
*  ++++++++++++++++++++++++++++++++++++++++
*  各NSET集合の節点を各部分領域に部分節点番号で
*   落す。
* +++++++++++++++++++++++++++++++++++++++++
      do 60 im=1,nodeset
         nodes=n_nset(im,1)
         np=n_nset(im,2)
*
         call data_dcond1 (feelpara(np_inset(im)),im,
     $        feelpara(np_npesub),feelpara(np_npenum),
     $        feelpara(np_npeloc),npmax,npesum,
     $        nodes,np)
*
 60   continue
*
*
*++++++++++++++++++++++++++++++++
*     Neumann条件用データEDAT集合のdat.PE*への書き込み
*     im+nmatrix番目のEDAT集合(im=1,nedat-nmatrix)
*     の境界要素内節点番号を部分節点番号で落す。
*+++++++++++++++++++++++++++++++
*
      call f_alloc (np_nregi,'Read nregi',npmax,0)
      do 70 im=1,nedat-nmatrix
         neelem=n_edat(im+nmatrix,1)
         nenode=n_edat(im+nmatrix,2)
*
         call data_ncond1 (feelpara(np_ibelem(im)),
     $        feelpara(np_ibmatno(im)),neelem,
     $        nenode,npmax,npesum,feelpara(np_npesub),
     $        feelpara(np_npenum),feelpara(np_npeloc),
     $        feelpara(np_nregi),
     $        im)
*
 70   continue
*
*     ファイルのclose 
      do 800 ir=1,npesum
         close (14+ir+5*npesum)
 800  continue
 1000 continue
      return
      end
*
*------------------------------
*
      subroutine read_edat (ielem,nelem,np,matno)
*
      implicit real*8 (a-h,o-z)
*
*---------------------------
      parameter (MAX_FEEL=2000000)
      parameter (MAX_DOMAIN=10)
      parameter (MAX_EDATSET=38)
      parameter (MAX_NODESET=20)
      parameter (MAX_NUMSET = 20)
      parameter (MAX_EWISE  = 20)
*---------------------------------------
      character*20 fmt
      dimension ielem(np,nelem),matno(nelem)
*
      common /feel_dat/ n_edat(MAX_EDATSET,3),
     $     n_nset(MAX_NODESET,2),
     $     n_ewise(MAX_EWISE,2)
      common /feel_var/np_work,np_x,np_y,np_z,nvars_fem,
     $     nvars_ewise,
     &     np_fem,np_ewise,np_heap
      common /feel_ctl/mode_ex,mode_output,max_heap
*
      write(fmt,9003) np+1
 9003 format('(',i,'i8)')
      do 10 i=1,nelem
         read (15,fmt) (ielem(j,i),j=1,np),matno(i)
 10   continue
      return
      end
*
*----------------------------------------------
*
      subroutine read_nset (inset,nodes,np)
*
*   -----------------------
*     全体節点番号、及び節点上自由度を読む
*   -----------------------
*     
      implicit real*8 (a-h,o-z)
*
      character*10 fmt
      dimension inset(np,nodes)
*
      write(fmt,90) np
 90   format('(',i2,'i8)')
      do 10 i=1,nodes
         read (15,fmt) (inset(j,i),j=1,np)
 10   continue
      return
      end

