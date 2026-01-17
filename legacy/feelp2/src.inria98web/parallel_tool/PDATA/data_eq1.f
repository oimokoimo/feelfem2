      subroutine data_eq1 (feelpara,npos,ia,npesub,npenum,
     $     npeloc,npeint,npeai,jain,npmax,npesum,nk1,nk2,
     $     nsuu)
*
*
*-------------------------------------------------
*     領域分割後、並列化に必要なデータの作成。
*     インターフェース上の方程式番号の共有関係
*     内点上の節点の自由度に対する方程式番号のデータも作る。      
*     npesub(npmax): 引数は全体節点番号 。属する部分領域の数。
*     npenum(npmax) : 各全体節点番号の属する部分領域の番号。
*     npesum : 部分領域の数
*     npmax : 全領域における全節点数。
*     nlnodes : 部分領域に含まれる最大節点数。
*
      implicit real*8 (a-h,o-z)
      real*4 feelpara(*)
*
      dimension npos(npmax,0:npesum),ia(npmax,npesum)
      dimension nsuu(npmax)
*
      dimension npesub(0:npmax)
      dimension npenum(npmax*npesum)
      dimension npeloc(npmax*npesum)
      dimension npeint(npmax*npesum,2)
      dimension npeai(npmax,2)
      dimension jain(0:npmax)
*     
*     npesub(*)のゼロクリア
      do 1 ip=1,npmax
         npesub(ip)=0
 1    continue
*     
*     npesub(*)の計算
      do 100 i=1,npmax
        npesub(i)=npesub(i)+nsuu(i)
 100  continue
*
      npesub(0)=1
      do 110 i=1,npmax
         npesub(i)=npesub(i-1)+npesub(i)
 110  continue
*
*
      do 130 i=1,npmax
         do 150 k=1,nsuu(i)
            npenum(npesub(i-1)+k-1)=npos(i,k)
            npeloc(npesub(i-1)+k-1)=ia(i,k) 
 150     continue
 130  continue
*
*     初期設定
      jain(0)=1
      nk1=0
      nk2=0            
*
      do 160 i=1,npmax
         if ((npesub(i)-npesub(i-1)).ge.2) then
            nk1=nk1+1
            jain(nk1)=jain(nk1-1)+npesub(i)-npesub(i-1)
            do 170 j1=jain(nk1-1),jain(nk1)-1
               npeint(j1,1)=npenum(j1-jain(nk1-1)
     $              +npesub(i-1))
               npeint(j1,2)=npeloc(j1-jain(nk1-1)
     $              +npesub(i-1))
 170        continue
         else if ((npesub(i)-npesub(i-1)).eq.1) then
            nk2=nk2+1
            npeai(nk2,1)=npenum(npesub(i-1))
            npeai(nk2,2)=npeloc(npesub(i-1))
         end if
*
 160  continue
*     
*
      return
      end
*
*---------------------------
*     
      subroutine data_eq2 (feelpara,npesub,npenum,npeloc,npeint,
     $     npeai,jain,npmax,npesum,nk1,nk2,ilnode,ignode,
     $     neelem,nenode,nelem,icheck,nfue,nbb)
*---------------------------------------------
*     各全体剛性行列用EDAT集合に対して作る。
*
*----------------------------------------------
*
      implicit real*8 (a-h,o-z)
*---------------
      real*4 feelpara(*)
      dimension nbb(0:npesum)
      dimension ilnode(nenode,nelem)
      dimension ignode(nenode,nelem)
* 
      dimension npesub(0:npmax)
      dimension icheck(npmax)
      dimension npenum(npmax*npesum)
      dimension npeloc(npmax*npesum)
      dimension npeint(npmax*npesum,2)
      dimension npeai(npmax,2)
      dimension nfue(0:npmax)
      dimension jain(0:npmax)
*     
*     npesub(*)のゼロクリア
      do 1 ip=1,npmax
         npesub(ip)=0
 1    continue
*     
      do 5 ip=1,npesum
*     部分領域 ip におけるicheck(jp)をゼロクリア
         do 6 jp=1,npmax
            icheck(jp)=0
 6       continue
*     
         do 10 ie=1,nbb(ip)-nbb(ip-1)
            do 20 ln=1,nenode
               if (icheck(ilnode(ln,ie+nbb(ip-1))).eq.0) then
                  icheck(ilnode(ln,ie+nbb(ip-1)))=1
*     
                  npesub(ignode(ln,ie+nbb(ip-1)))
     $                 =npesub(ignode(ln,ie+nbb(ip-1)))
     $                 +1
               end if
 20         continue
 10      continue
 5    continue
*
*
      npesub(0)=1
      do 30 in=1,npmax
         npesub(in)=npesub(in-1)+npesub(in)
 30   continue
*     
      do 35 in=0,npmax
         nfue(in)=0
 35   continue
*     
      do 40 ip=1,npesum
*     部分領域 ip におけるicheck(jp)をゼロクリア
         do 46 jp=1,npmax
            icheck(jp)=0
 46      continue         
*
         do 50 ie=1,nbb(ip)-nbb(ip-1)
            do 60 ln=1,nenode
               if (icheck(ilnode(ln,ie+nbb(ip-1))).eq.0) then
                  icheck(ilnode(ln,ie+nbb(ip-1)))=1
                  nfue(ignode(ln,ie+nbb(ip-1))-1)=
     $                 nfue(ignode(ln,ie+nbb(ip-1))-1)+1
                  npenum(npesub(ignode(ln,ie+nbb(ip-1))-1)+nfue(
     $                 ignode(ln,ie+nbb(ip-1))-1)-1)=
     $                 ip
                  npeloc(npesub(ignode(ln,ie+nbb(ip-1))-1)+nfue(
     $                 ignode(ln,ie+nbb(ip-1))-1)-1)=
     $                 ilnode(ln,ie+nbb(ip-1))
*     
               end if
 60         continue
 50      continue
 40   continue
*
*     初期設定
      jain(0)=1
      nk1=0
      nk2=0
      do 70 i=1,npmax
         if ((npesub(i)-npesub(i-1)).ge.2) then
            nk1=nk1+1
            jain(nk1)=jain(nk1-1)+npesub(i)-npesub(i-1)
            do 80 j1=jain(nk1-1),jain(nk1)-1
               npeint(j1,1)=npenum(j1-jain(nk1-1)
     $              +npesub(i-1))
               npeint(j1,2)=npeloc(j1-jain(nk1-1)
     $              +npesub(i-1))
 80         continue
         else if ((npesub(i)-npesub(i-1)).eq.1) then
            nk2=nk2+1
            npeai(nk2,1)=npenum(npesub(i-1))
            npeai(nk2,2)=npeloc(npesub(i-1))
         end if
 70   continue
*     
*
      return
      end



