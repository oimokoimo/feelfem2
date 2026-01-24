/*
   FEEL p2  MAKE FORTRAN LIBRARY   ipd_make
 */

#include <stdio.h>
#include "../feel_def/feel_def.h"
#include "../system/system.h"

#define FNAME "ipd_make.f"
void lib_ipd_make()
{
   FILE *fp;
   StoreMakefile(FNAME,SYSTEM_LIBRARY);
   if(LIMIT_FILE == 1) return;
   fp = OpenFileToWrite( FNAME );
   F77("      subroutine makeipd(ipf,ipd,npmax,neq)\n");
   F77("*-------------------------------------------------------------------\n");
   F77("*  FEEL P2 System Subroutine  MAKEIPD\n");
   F77("*-------------------------------------------------------------------\n");
   F77("*  Purpose: 節点自由度から、累積節点自由度配列を作成する\n");
   F77("*  \n");
   F77("*  Caution: IPF(*)は、節点毎自由度\n");
   F77("*\n");
   F77("*           IPD(*)配列の意味は次の通り\n");
   F77("*           IPD(*)は各節点毎に値を持つ\n");
   F77("*           IPD(*) = 0 なる節点には 自由度が無い\n");
   F77("*           IPD(n) = K IPF(n) = 3 なら、節点番号 n には、\n");
   F77("*           方程式番号 K,K+1,K+2  の自由度が対応している\n");
   F77("*-------------------------------------------------------------------\n");
   F77("      dimension IPF(npmax),IPD(npmax)\n");
   F77("*\n");
   F77("      neq = 0\n");
   F77("*\n");
   F77("*     自由度がある最初の節点を探索\n");
   F77("*\n");
   F77("      do 100 i=1,npmax\n");
   F77("       if(IPF(i) .ne. 0) then\n");
   F77("         istart = i\n");
   F77("         goto 200\n");
   F77("       endif\n");
   F77(" 100  continue\n");
   F77(" 150  stop 'makeipd error'\n");
   F77("*---\n");
   F77(" 200  continue\n");
   F77("*\n");
   F77("      nowfree = IPF(istart)\n");
   F77("      IPD(istart) = 1\n");
   F77("*\n");
   F77("      do 300 i=istart+1,npmax\n");
   F77("        if(IPF(i) .eq. 0) goto 300\n");
   F77("*\n");
   F77("        IPD(i) = nowfree + 1\n");
   F77("        nowfree = nowfree + IPF(i)\n");
   F77(" 300  continue\n");
   F77("*\n");
   F77("      neq = nowfree\n");
   F77("*\n");
   F77("      return\n");
   F77("      end\n");
 CloseFile(fp);
 return;
}
