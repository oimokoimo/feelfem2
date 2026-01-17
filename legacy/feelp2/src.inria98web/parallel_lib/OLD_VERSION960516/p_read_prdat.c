/*
   FEEL p2  MAKE FORTRAN LIBRARY   p_read_prdat
 */

#include <stdio.h>
#include "../feel_def/feel_def.h"
#include "../system/system.h"

#define FNAME "p_read_prdat.f"
lib_p_read_prdat()
{
   FILE *fp;
   StoreMakefile(FNAME,SYSTEM_LIBRARY);
   if(LIMIT_FILE == 1) return;
   fp = OpenFileToWrite( FNAME );
   F77("      subroutine p_read_prdat (iunit,innersum,innernd)\n");
   F77("*\n");
   F77("*++++++++++++++++++++++++++++++\n");
   F77("*     FEEL/P2/Cenju-3/MPI subprogram\n");
   F77("*     Read node set data from dat.PE@@@.X file\n");
   F77("*     innersum   : number of nodes\n");
   F77("*     innernd(*): node number array\n");
   F77("*++++++++++++++++++++++++++\n");
   F77("      implicit real*8 (a-h,o-z)\n");
   F77("*\n");
   F77("      do 10 i=1,innersum\n");
   F77("         read (iunit,9001) innernd(i)\n");
   F77(" 10   continue\n");
   F77("*\n");
   F77(" 9001 format(i8)\n");
   F77("      return\n");
   F77("      end      \n");
 CloseFile(fp);
 return;
}
