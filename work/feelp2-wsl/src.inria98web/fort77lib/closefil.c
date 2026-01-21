/*
   FEEL p2  MAKE FORTRAN LIBRARY   closefil
 */

#include <stdio.h>
#include "../feel_def/feel_def.h"
#include "../system/system.h"

#define FNAME "closefil.f"
lib_closefil()
{
   FILE *fp;
   StoreMakefile(FNAME,SYSTEM_LIBRARY);
   if(LIMIT_FILE == 1) return;
   fp = OpenFileToWrite( FNAME );
   F77("      subroutine closefil(no)\n");
   F77("      parameter(MAX=100)\n");
   F77("      dimension iunits(MAX)\n");
   F77("      common /feel_dbg/ip,iunits\n");
   F77("      if(no .EQ. 0) then\n");
   F77("       ip = 0\n");
   F77("       return\n");
   F77("      endif\n");
   F77("      if(no .LT. 0) then\n");
   F77("      do 100 i=1,ip\n");
   F77("       close(unit=iunits(i))\n");
   F77("100   continue\n");
   F77("      return\n");
   F77("      endif\n");
   F77("*\n");
   F77("      if(ip.EQ.MAX) stop 'too many close file to store'\n");
   F77("      ip=ip+1\n");
   F77("      iunits(ip) = no\n");
   F77("      return\n");
   F77("      end\n");
   F77("      subroutine doclosefil(no)\n");
   F77("      parameter(MAX=100)\n");
   F77("      dimension iunits(MAX)\n");
   F77("      common /feel_dbg/ip,iunits\n");
   F77("      do 100 i=1,ip\n");
   F77("       close(unit=iunits(i))\n");
   F77("100   continue\n");
   F77("      ip = 0\n");
   F77("      return\n");
   F77("      end\n");

 CloseFile(fp);
 return;
}




