/*
   FEEL p2  MAKE FORTRAN LIBRARY   p_memory_move
 */

#include <stdio.h>
#include "../feel_def/feel_def.h"
#include "../system/system.h"

#define FNAME "p_memory_move.f"
lib_p_memory_move()
{
   FILE *fp;
   StoreMakefile(FNAME,SYSTEM_LIBRARY);
   if(LIMIT_FILE == 1) return;
   fp = OpenFileToWrite( FNAME );
   F77("      subroutine p_memory_move (ia,ib,nsize)\n");
   F77("*\n");
   F77("*     ---------------------\n");
   F77("*     メモリの移動を行う。\n");
   F77("*\n");
   F77("*     --------------------\n");
   F77("      implicit real*8 (a-h,o-z)\n");
   F77("*\n");
   F77("*\n");
   F77("      dimension ia(*),ib(*)\n");
   F77("      do 1 i=1,nsize\n");
   F77("         ib(i)=ia(i)\n");
   F77(" 1    continue\n");
   F77("*\n");
   F77("      return\n");
   F77("      end\n");
   F77("\n");
   F77("\n");
   F77("\n");
   F77("\n");
 CloseFile(fp);
 return;
}
