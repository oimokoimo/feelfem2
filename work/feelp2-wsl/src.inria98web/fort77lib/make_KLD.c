/*
   FEEL p2  MAKE FORTRAN LIBRARY   make_KLD
 */

#include <stdio.h>
#include "../feel_def/feel_def.h"
#include "../system/system.h"

#define FNAME "make_KLD.f"
void lib_make_KLD()
{
   FILE *fp;
   StoreMakefile(FNAME,SYSTEM_LIBRARY);
   if(LIMIT_FILE == 1) return;
   fp = OpenFileToWrite( FNAME );
   F77("      subroutine make_KLD(KH,KLD,neq,ncof)\n");
   F77("*-------------------------------------------------------------------\n");
   F77("*  FEEL P2 System Subroutine  make_KLD\n");
   F77("*-------------------------------------------------------------------\n");
   F77("*  Purpose: スカイラインの高さを持つ配列KHより格納情報配列KLDを作成\n");
   F77("*  \n");
   F77("*  Caution: book p.302 参照\n");
   F77("*\n");
   F77("*  KH    列の高さ\n");
   F77("*  KLD   スカイライン情報配列\n");
   F77("*  neq   方程式の本数\n");
   F77("*  ncof  係数マトリックスの為の大きさ(上、下各三角形のもの)\n");
   F77("*-------------------------------------------------------------------      \n");
   F77("      dimension KH(*),KLD(*)\n");
   F77("*---\n");
   F77("      KLD(1) = 1\n");
   F77("      KLD(2) = 1\n");
   F77("*---\n");
   F77("      do 100 i = 3,neq+1\n");
   F77("         KLD(i) = KLD(i-1) + KH(i-1)\n");
   F77(" 100  continue\n");
   F77("*---\n");
   F77("      ncof = KLD(neq + 1) - 1\n");
   F77("*---\n");
   F77("      return\n");
   F77("      end\n");
 CloseFile(fp);
 return;
}
