      subroutine makeIPDex(IPF,IPD,npmax,neq)
*-------------------------------------------------------------------
*  FEELFEM  makeIPDex
*
*  2000/05/30 (feelfem_stokes version)
*-------------------------------------------------------------------
*  Purpose: Make summed up array for the degree of freedom
*  
*  Caution: IPD(n) = m     The equation number of node n begins m
*           IPD(n) = 0     There is no degree of freedom with node n
*           IPD(n) = k and IPF(n)= 3  -> Equation No. k,k+1,k+2 to node n
*-------------------------------------------------------------------
      dimension IPF(npmax),IPD(npmax)
*
      neq = 0
      do 1 i=1,npmax
         IPD(i) = 0
 1    continue
*------------------------------------------------------
*  Search the first node of actual degree of freedom
*------------------------------------------------------
      do 100 i=1,npmax
       if(IPF(i) .ne. 0) then
         istart = i
         goto 200
       endif
 100  continue
 150  call abortexit(-999, 'makeipdex error')
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
