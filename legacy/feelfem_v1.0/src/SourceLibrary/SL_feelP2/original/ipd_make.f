      subroutine makeipd(ipf,ipd,npmax,neq)
*-------------------------------------------------------------------
*  FEEL P2 System Subroutine  MAKEIPD
*-------------------------------------------------------------------
*  Purpose: 節点自由度から、累積節点自由度配列を作成する
*  
*  Caution: IPF(*)は、節点毎自由度
*
*           IPD(*)配列の意味は次の通り
*           IPD(*)は各節点毎に値を持つ
*           IPD(*) = 0 なる節点には 自由度が無い
*           IPD(n) = K IPF(n) = 3 なら、節点番号 n には、
*           方程式番号 K,K+1,K+2  の自由度が対応している
*-------------------------------------------------------------------
      dimension IPF(npmax),IPD(npmax)
*
      neq = 0
*
*     自由度がある最初の節点を探索
*
      do 100 i=1,npmax
       if(IPF(i) .ne. 0) then
         istart = i
         goto 200
       endif
 100  continue
 150  stop 'makeipd error'
*---
 200  continue
*
      nowfree = IPF(istart)
      IPD(istart) = 1
*
      do 300 i=istart+1,npmax
        if(IPF(i) .eq. 0) goto 300
*
        IPD(i) = nowfree + 1
        nowfree = nowfree + IPF(i)
 300  continue
*
      neq = nowfree
*
      return
      end
