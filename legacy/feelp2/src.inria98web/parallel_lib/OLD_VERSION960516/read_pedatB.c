/*
   FEEL p2  MAKE FORTRAN LIBRARY   read_pedatB
 */

#include <stdio.h>
#include "../feel_def/feel_def.h"
#include "../system/system.h"

#define FNAME "read_pedatB.f"
lib_read_pedatB()
{
   FILE *fp;
   StoreMakefile(FNAME,SYSTEM_LIBRARY);
   if(LIMIT_FILE == 1) return;
   fp = OpenFileToWrite( FNAME );
   F77("      subroutine read_pedatb(iunit,nsum,nnod)\n");
   F77("*++++++++++++++++++++++++++++++\n");
   F77("*     FEEL/P2/Cenju-3/MPI subprogram\n");
   F77("*++++++++++++++++++++++++++\n");
   F77("*     Read node set data from dat.PE@@@.X file\n");
   F77("*     nsum   : number of nodes\n");
   F77("*     nnod(*): node number array\n");
   F77("*++++++++++++++++++++++++++\n");
   F77("      implicit real*8 (a-h,o-z)\n");
   F77("*---------------------------\n");
   F77("      dimension nnod(nsum)\n");
   F77("*\n");
   F77("      do 10 i=1,nsum\n");
   F77("         read (iunit,9001) nnod(i)\n");
   F77(" 10   continue\n");
   F77(" 9001 format(i8)\n");
   F77("      return\n");
   F77("      end \n");
 CloseFile(fp);
 return;
}
