/*
   FEEL p2  MAKE FORTRAN LIBRARY   data_nodsub
 */

#include <stdio.h>
#include "../feel_def/feel_def.h"
#include "../system/system.h"

#define FNAME "data_nodsub.f"
lib_data_nodsub()
{
   FILE *fp;
   StoreMakefile(FNAME,SYSTEM_LIBRARY);
   if(LIMIT_FILE == 1) return;
   fp = OpenFileToWrite( FNAME );
   F77("      subroutine data_nodsub1 (iunit,x,npmaxsub)\n");
   F77("*\n");
   F77("      implicit real*8 (a-h,o-z)\n");
   F77("*\n");
   F77("      dimension x(*)\n");
   F77("\n");
   F77("      do 10 i=1,npmaxsub\n");
   F77("         read (iunit,9001) x(i)\n");
   F77(" 10   continue\n");
   F77("*     \n");
   F77(" 9001 format(1PE12.5)\n");
   F77("      return\n");
   F77("      end\n");
   F77("*\n");
   F77("*++++++++++++++++++++++++++++++++++++++++++\n");
   F77("      subroutine data_nodsub2 (iunit,x,y,npmaxsub)\n");
   F77("*\n");
   F77("      implicit real*8 (a-h,o-z)\n");
   F77("*\n");
   F77("      dimension x(*),y(*)\n");
   F77("*\n");
   F77("      do 10 i=1,npmaxsub\n");
   F77("         read (iunit,9001) x(i),y(i)\n");
   F77(" 10   continue\n");
   F77("*     \n");
   F77(" 9001 format(1PE12.5,1PE12.5)\n");
   F77("      return\n");
   F77("      end \n");
   F77("*++++++++++++++++++++++++++++++++++     \n");
   F77("      subroutine data_nodsub3 (iunit,x,y,z,npmaxsub)\n");
   F77("*\n");
   F77("      implicit real*8 (a-h,o-z)\n");
   F77("*\n");
   F77("      dimension x(*),y(*),z(*)\n");
   F77("*\n");
   F77("      do 10 i=1,npmaxsub\n");
   F77("         read (iunit,9001) x(i),y(i),z(i)\n");
   F77(" 10   continue\n");
   F77("*     \n");
   F77(" 9001 format(1PE12.5,1PE12.5,1PE12.5)\n");
   F77("      return\n");
   F77("      end\n");
   F77("      \n");
   F77("\n");
   F77("\n");
 CloseFile(fp);
 return;
}
