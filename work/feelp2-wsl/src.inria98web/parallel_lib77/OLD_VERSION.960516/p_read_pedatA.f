      subroutine p_read_pedatA(iunit,npesum,npmaxsub,
     $     nelemsub,np,ndisub,
     $     neusub,
     $     isubelem,nelegru,
     $     nloglo,matno,
     $     nsendlist,nrecvlist,
     $     ndikaz,ndinum,neukaz,neunum,ipe,
     $     nmatrix)
*+++++++++++++++++++++++++++++++++++++++++++++++
*     Date: 1995 9/21
*+++++++++++++++++++++++++++++++++++++++++++++
      implicit real*8 (a-h,o-z)
*
*
*----------------------------------------
*     nloglo(npmaxsub): nloglo(i)は部分領域rank+1
*     での部分節点番号iの全体節点番号
*
*     各プロセッサ担当の部分領域数：nelemsub=nel(ip)
*     isubelem(np,nelemsub): isubelem(ln,ie)=
*                           ilnode(ln,ie,ip)(
*               部分領域番号ipで成立)
*     nelegru(nelemsub): nelegru(i)=ngru(i+nbb(ip-1,nankai))
*                (部分領域番号ipで成立)
*     matno(nelemsub) :全体要素番号でngru(i+nbb(ip-1,nankai))
*     の要素材料番号
*     nrecvlist(npesum) : インターフェース上の
*     データの足し込みを行う部分領域番号。(
*     要するにデータを最初受信する部分領域番号)
*
*     nsendlist(npesum) : インターフェース上の
*     データを足し込みの為に送信する部分領域番号。(
*     要するにデータを最初送信する部分領域番号)
*
*
*&------------------------------------
*
      character*20 fmt
*
      dimension nloglo(npmaxsub)
      dimension nelegru(nelemsub),isubelem(np,nelemsub)
      dimension matno(nelemsub)
      dimension ndikaz(*),ndinum(*),neukaz(*),neunum(*)
      dimension nsendlist(*),nrecvlist(*)
*
*     ----- 各プロセッサに必要なデータの読み込み ----
* ---- 各部分領域の部分節点番号と全体節点番号との対応 ---
      do 10 is=1,npmaxsub
         read (iunit,9001) nloglo(is)
 10   continue
*
*     ---- インターフェース上のデータを送信する部分領域番号--      
      do 20 is=1,npesum
         read (iunit,9001) nsendlist(is)
 20   continue
*
*     ---- インターフェース上のデータを受信する部分領域番号--      
      do 30 is=1,npesum
         read (iunit,9001) nrecvlist(is)
 30   continue
*     
*     ++++++++++++++++++++++++++++
*     要素内節点番号と部分節点番号との対応、
*     要素材料番号を読み込む。
*     ++++++++++++++++++++++++++++
      write (fmt,8001) np+1
 8001 format ('(',i,'i8)')
      do 31 i=1,nelemsub
         read (iunit,fmt) (isubelem(ln,i),ln=1,np),
     $        matno(i)
 31   continue
*
      do 50 j=1,nelemsub
         read (iunit,9001) nelegru(j)
 50   continue
*
*     ------ 各部分領域iqでDirichlet条件(feel_datで節点集合
*     'NSET'としてin番目)が課されている数とその
*     列の数を読み込む。---
*
      do 60 in=1,ndisub
         read (iunit,9011) ndikaz(in),ndinum(in)
 60   continue      
*    ------ 各部分領域iq(rank+1)でNeumann条件(feel_datで境界要素
*     としてin番目)が課されている数を読み込む。---
*     ----- 要素節点集合EDATの数-1"neusub"-----
      do 70 in=1,neusub
         read (iunit,9011) neukaz(in),neunum(in)
 70   continue
*     
 9001 format(i8)
 9011 format(2i8)
      return
      end
