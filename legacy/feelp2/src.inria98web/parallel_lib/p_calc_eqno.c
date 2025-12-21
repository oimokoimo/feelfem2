/*
   FEEL p2  MAKE FORTRAN LIBRARY   p_calc_eqno
 */

#include <stdio.h>
#include "../feel_def/feel_def.h"
#include "../system/system.h"

#define FNAME "p_calc_eqno.f"
lib_p_calc_eqno()
{
   FILE *fp;
   StoreMakefile(FNAME,SYSTEM_LIBRARY);
   if(LIMIT_FILE == 1) return;
   fp = OpenFileToWrite( FNAME );
   F77("      subroutine p_calc_eqno(nodsum,nnod,neqsum,\n");
   F77("     $     IPFsub,npmaxsub)\n");
   F77("*\n");
   F77("      dimension nnod(nodsum)\n");
   F77("*     \n");
   F77("      dimension IPFsub(npmaxsub)\n");
   F77("*+++++++++++++++++++++++++++++++++++++++++++++++++\n");
   F77("*     calculate neqsum(maximum of equation number)\n");
   F77("*+++++++++++++++++++++++++++++++++++++++++++++++++\n");
   F77("      neqsum=0\n");
   F77("      do 10 i=1,nodsum\n");
   F77("         neqsum=neqsum+IPFsub(nnod(i))\n");
   F77(" 10   continue\n");
   F77("      if (neqsum.eq.0) then\n");
   F77("         stop 'neqsum error'\n");
   F77("      end if\n");
   F77("      return\n");
   F77("      end\n");
 CloseFile(fp);
 return;
}
