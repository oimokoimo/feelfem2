      subroutine data_aiin (feelpara,npeint,npeai,jain,
     $     nk1,nk2,npesum,npmax,nsum)
*
      implicit real*8 (a-h,o-z)
*
      real*4 feelpara(*) 
      dimension npeint(npmax*npesum,2),npeai(npmax,2)
      dimension jain(0:npmax)
      dimension nsum(2,npesum)
*
*++++++++++++++++++++++++++++++++++++++++++++++++
*     --- 各部分領域上のインターフェース上の部分節点番号と
*        内点の部分節点番号の数 : nsum(2,npesum),nsum(1,npesum)
*     を計算する。 ------
*++++++++++++++++++++++++++++++++++++++++++++++++
*
      do 1 i=1,npesum
         nsum(1,i)=0
 1    continue
*     ----- まず内点部分節点番号を落す。---
      do 9 i=1,nk2
         nsum(1,npeai(i,1))=nsum(1,npeai(i,1))+1
 9    continue
*     ---- 内点上の部分節点番号処理終了。-----
*     ---- インターフェース上の部分節点番号の処理。----
      do 2 i=1,npesum
         nsum(2,i)=0
 2    continue
      do 7 i=1,nk1
         do 8 j=jain(i-1),jain(i)-1
            nsum(2,npeint(j,1))=nsum(2,npeint(j,1))+1
 8       continue
 7    continue
*
*     各部分領域 i の内点数nsum(1,i)
      do 10 i=1,npesum
         write (14+i+5*npesum,9001) nsum(1,i)
 10   continue
*
*     各部分領域 npeai(i,1)での内点の部分節点番号
      do 20 i=1,nk2
         write (14+npeai(i,1)+5*npesum,9001) npeai(i,2)
 20   continue
*
*     各部分領域 iのインターフェース上の節点数
      do 30 i=1,npesum
         write (14+i+5*npesum,9001) nsum(2,i)
 30   continue
*
*     各部分領域 npeint(j,1)のインターフェース上
*     の部分節点番号
      do 50 i=1,nk1
         do 60 j=jain(i-1),jain(i)-1
            write (14+npeint(j,1)+5*npesum,9001) npeint(j,2)
 60      continue
 50   continue
*
 9001 format(i8)
      return
      end


