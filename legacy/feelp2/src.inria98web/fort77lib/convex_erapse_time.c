/*
   FEEL p2  MAKE FORTRAN LIBRARY   convex_erapse_time
 */

#include <stdio.h>
#include "../feel_def/feel_def.h"
#include "../system/system.h"

#define FNAME "convex_erapse_time.f"
lib_convex_erapse_time()
{
   FILE *fp;
   StoreMakefile(FNAME,SYSTEM_LIBRARY);
   if(LIMIT_FILE == 1) return;
   fp = OpenFileToWrite( FNAME );
   F77("      subroutine timeinit\n");
   F77("*-------------------------------------------------------------------\n");
   F77("*  FEEL P2 System Subroutine\n");
   F77("*-------------------------------------------------------------------\n");
   F77("      real * 4 tzero,CPUTIME\n");
   F77("      common /eratime/tzero\n");
   F77("*      \n");
   F77("      tzero = CPUTIME( 0.0 )\n");
   F77("      return\n");
   F77("      end\n");
   F77("*-------------------------------------------------------------------\n");
   F77("      real*8 function erapstime()\n");
   F77("      implicit real*8 (a-h,o-z)\n");
   F77("      real *4 tzero,CPUTIME,time\n");
   F77("      common /eratime/tzero\n");
   F77("      time = CPUTIME( tzero )\n");
   F77("      erapstime = dble( time )\n");
   F77("      return\n");
   F77("      end\n");
 CloseFile(fp);
 return;
}
