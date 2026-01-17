      subroutine cal_ht_a(ielem,neelem,nenode,KHa,npmax)
*---------------------------------------------------------------------
*  FEEL P2 System Subroutine
*---------------------------------------------------------------------
*  Purpose: スカイライン行列の列の高さを計算する補助プログラム
*           要素内の最小節点番号を探し出す
*
*        KHaは、各節点における接続最小節点番号
*
*  注意: KHaは、0クリアされているはず
*
*---------------------------------------------------------------------
      dimension ielem(nenode,neelem),KHa(*)
*---
      do 10 i=1,npmax
         KHa(i) = npmax + 1
 10   continue
*---
      do 100 i=1,neelem
         
         ip_min = ielem(1,i)

*---  各要素内の最小節点番号を求める
         do 120 j=2,nenode
            if(ip_min .gt. ielem(j,i)) ip_min = ielem(j,i)
 120     continue
         
         do 130 j=1,nenode
            if(KHa(ielem(j,i)) .gt. ip_min) KHa(ielem(j,i)) = ip_min
 130     continue
         
 100  continue

c      do 200 j=1,468
c       write(*,*) 'KHa(',j,')= ',kha(j)
c 200  continue
*---
      return
      end
      subroutine cal_ht(KHa,KH,IPF,IPD,npmax,neq)
*---------------------------------------------------------------------
*  FEEL P2 System Subroutine
*---------------------------------------------------------------------
*  Purpose: スカイライン行列の列の高さを計算するプログラム
*
*  注意: 配列KHaの0は、未使用節点の意味
*
*  変数: KHa(npmax)     各節点に関連する最小節点番号
*        KH (neq)       スカイライン行列の列の高さ、対角のみの場合の0から始める
*        IPF(npmax)     節点毎自由度
*        IPD(npmax)     累積節点自由度
*        npmax      入  総節点数
*        neq        入  方程式の本数(連立一次方程式の連立の数)
*---------------------------------------------------------------------
      dimension KHa(npmax),KH(neq),IPF(npmax),IPD(npmax)
*---
      do 100 i=1,npmax
         
         if(IPF(i) .eq. 0) goto 100
*
* min_np は節点 i における最小 関連方程式番号
*
         min_np  = IPD( KHa(i) )
         ip_base = IPD( i )
*---
         do 200 j=1,IPF(i)
            KH( ip_base + j - 1) = min_np 
 200     continue
*---
 100  continue
*---
      do 300 i=1,neq
         KH(i) = i - KH(i)
C         write(*,*) 'KH(',i,') = ',kh(i)
 300  continue
      return
      end

