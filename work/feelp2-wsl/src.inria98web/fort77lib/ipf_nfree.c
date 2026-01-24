/*
   FEEL p2  MAKE FORTRAN LIBRARY   ipf_nfree
 */

#include <stdio.h>
#include "../feel_def/feel_def.h"
#include "../system/system.h"

#define FNAME "ipf_nfree.f"
void lib_ipf_nfree()
{
   FILE *fp;
   StoreMakefile(FNAME,SYSTEM_LIBRARY);
   if(LIMIT_FILE == 1) return;
   fp = OpenFileToWrite( FNAME );
   F77("      subroutine ipf_nfree(neelem,nenode,IPF,ielem,nenfre)\n");
   F77("*-------------------------------------------------------------------\n");
   F77("*  FEEL P2 System Subroutine\n");
   F77("*-------------------------------------------------------------------\n");
   F77("*   Purpose: 配列IPFに節点毎自由度を設定する。\n");
   F77("*            IPF(*)は0クリアされていること\n");
   F77("*  \n");
   F77("* Variables: neelem  要素数\n");
   F77("*            nenode  要素内節点数\n");
   F77("*            IPF     節点毎自由度配列\n");
   F77("*            ielem   要素節点対応配列\n");
   F77("*            nenfre  要素局所節点毎自由度\n");
   F77("*            \n");
   F77("*-------------------------------------------------------------------\n");
   F77("      dimension IPF(*),ielem(nenode,neelem),nenfre(*)\n");
   F77("*---\n");
   F77("      do 100 i=1,neelem\n");
   F77("         do 200 j=1,nenode\n");
   F77("\n");
   F77("            IPF(ielem(j,i)) = nenfre(j)\n");
   F77("\n");
   F77(" 200     continue\n");
   F77(" 100  continue\n");
   F77("*---  \n");
   F77("      return\n");
   F77("*---\n");
   F77("      end\n");
   F77("\n");
 CloseFile(fp);
 return;
}
