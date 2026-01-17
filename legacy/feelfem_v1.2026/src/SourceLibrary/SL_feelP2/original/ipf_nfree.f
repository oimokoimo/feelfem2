      subroutine ipf_nfree(neelem,nenode,IPF,ielem,nenfre)
*-------------------------------------------------------------------
*  FEEL P2 System Subroutine
*-------------------------------------------------------------------
*   Purpose: 配列IPFに節点毎自由度を設定する。
*            IPF(*)は0クリアされていること
*  
* Variables: neelem  要素数
*            nenode  要素内節点数
*            IPF     節点毎自由度配列
*            ielem   要素節点対応配列
*            nenfre  要素局所節点毎自由度
*            
*-------------------------------------------------------------------
      dimension IPF(*),ielem(nenode,neelem),nenfre(*)
*---
      do 100 i=1,neelem
         do 200 j=1,nenode

            IPF(ielem(j,i)) = nenfre(j)

 200     continue
 100  continue
*---  
      return
*---
      end

