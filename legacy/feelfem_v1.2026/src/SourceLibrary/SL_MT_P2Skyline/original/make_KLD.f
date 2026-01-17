      subroutine make_KLD(KH,KLD,neq,ncof)
*-------------------------------------------------------------------
*  FEEL P2 System Subroutine  make_KLD
*-------------------------------------------------------------------
*  Purpose: スカイラインの高さを持つ配列KHより格納情報配列KLDを作成
*  
*  Caution: book p.302 参照
*
*  KH    列の高さ
*  KLD   スカイライン情報配列
*  neq   方程式の本数
*  ncof  係数マトリックスの為の大きさ(上、下各三角形のもの)
*-------------------------------------------------------------------      
      dimension KH(*),KLD(*)
*---
      KLD(1) = 1
      KLD(2) = 1
*---
      do 100 i = 3,neq+1
         KLD(i) = KLD(i-1) + KH(i-1)
 100  continue
*---
      ncof = KLD(neq + 1) - 1
*---
      return
      end
