/*
   FEEL p2  MAKE FORTRAN LIBRARY   mpi_util
 */

#include <stdio.h>
#include "../feel_def/feel_def.h"
#include "../system/system.h"

#define FNAME "mpi_util.f"
lib_mpi_util()
{
   FILE *fp;
   StoreMakefile(FNAME,SYSTEM_LIBRARY);
   if(LIMIT_FILE == 1) return;
   fp = OpenFileToWrite( FNAME );
   F77("      subroutine MPP_movedata(IFROM,ITO,N)\n");
   F77("      integer * 4 IFROM(*),ITO(*)\n");
   F77("      do 100 i=1,N\n");
   F77("         ITO(i) = IFROM(i)\n");
   F77(" 100  continue\n");
   F77("      return\n");
   F77("      end\n");
 CloseFile(fp);
 return;
}
