/*
   FEEL p2  MAKE FORTRAN LIBRARY   p_get_band
 */

#include <stdio.h>
#include "../feel_def/feel_def.h"
#include "../system/system.h"

#define FNAME "p_get_band.f"
lib_p_get_band()
{
   FILE *fp;
   StoreMakefile(FNAME,SYSTEM_LIBRARY);
   if(LIMIT_FILE == 1) return;
   fp = OpenFileToWrite( FNAME );
   F77("      subroutine p_get_band (il,ir,neq_sub,A,JA,MJ,JDP,jl,jr)\n");
   F77("c\n");
   F77("c------------------------------------------------\n");
   F77("c     Calculation of \"JL,JR\"\n");
   F77("c                 JL : bandwidth of lower part\n");
   F77("c                 JR : bandwidth of upper part\n");
   F77("c------------------------------------------------\n");
   F77("c     \n");
   F77("      implicit real*8 (a-h,o-z)\n");
   F77("c\n");
   F77("      dimension il(neq_sub),ir(neq_sub)\n");
   F77("      dimension A(neq_sub,MJ),JA(neq_sub,MJ)\n");
   F77("*\n");
   F77("      jl=0\n");
   F77("      jr=JDP\n");
   F77("      do 10 i=1,neq_sub\n");
   F77("         il(i)=0\n");
   F77("         ir(i)=JDP\n");
   F77(" 10   continue\n");
   F77("*\n");
   F77("      do 20 i=1,neq_sub\n");
   F77("         do 30 j=1,JDP-1 \n");
   F77("            if ((JA(i,j).lt.i).and.(JA(i,j).ge.1)) then\n");
   F77("               il(i)=j\n");
   F77("            end if\n");
   F77(" 30      continue\n");
   F77("         jl=max0(jl,il(i))\n");
   F77(" 20   continue\n");
   F77("*\n");
   F77("      do 40 i=1,neq_sub\n");
   F77("         do 50 j=JDP+1,MJ\n");
   F77("            if ((JA(i,j).gt.i).and.(JA(i,j).le.neq_sub)) then\n");
   F77("               ir(i)=j\n");
   F77("            end if\n");
   F77(" 50      continue\n");
   F77("         jr=max0(jr,ir(i))\n");
   F77(" 40   continue\n");
   F77("*\n");
   F77("      return\n");
   F77("      end\n");
   F77("      \n");
   F77("               \n");
   F77("\n");
   F77("\n");
 CloseFile(fp);
 return;
}
