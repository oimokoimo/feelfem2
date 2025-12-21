/*
   FEEL p2  MAKE FORTRAN LIBRARY   diskio
 */

#include <stdio.h>
#include "../feel_def/feel_def.h"
#include "../system/system.h"

#define FNAME "diskio.f"
lib_diskio()
{
   FILE *fp;
   StoreMakefile(FNAME,SYSTEM_LIBRARY);
   if(LIMIT_FILE == 1) return;
   fp = OpenFileToWrite( FNAME );
   F77("      subroutine diskwrti(iunit,num,idat)\n");
   F77("*-------------------------------------------------------------------\n");
   F77("*  FEEL P2 System Subroutine\n");
   F77("*-------------------------------------------------------------------\n");
   F77("*  Purpose: 整数配列をファイルに書く\n");
   F77("*-------------------------------------------------------------------\n");
   F77("      dimension idat(num)\n");
   F77("*\n");
   F77("      write(iunit) (idat(i),i=1,num)\n");
   F77("      return\n");
   F77("      end\n");
   F77("      subroutine diskwrtd(iunit,num,dat)\n");
   F77("*-------------------------------------------------------------------\n");
   F77("*  FEEL P2 System Subroutine\n");
   F77("*-------------------------------------------------------------------\n");
   F77("*  Purpose: 実数配列をファイルに書く\n");
   F77("*-------------------------------------------------------------------\n");
   F77("      implicit real*8 (a-h,o-z)\n");
   F77("      dimension dat(num)\n");
   F77("*\n");
   F77("      write(iunit) (dat(i),i=1,num)\n");
   F77("      return\n");
   F77("      end\n");
   F77("      subroutine diskrdi(iunit,num,idat)\n");
   F77("*-------------------------------------------------------------------\n");
   F77("*  FEEL P2 System Subroutine\n");
   F77("*-------------------------------------------------------------------\n");
   F77("*  Purpose: 整数配列をファイルから読む\n");
   F77("*-------------------------------------------------------------------\n");
   F77("      dimension idat(num)\n");
   F77("*\n");
   F77("      read(iunit) (idat(i),i=1,num)\n");
   F77("      return\n");
   F77("      end\n");
   F77("      subroutine diskrdd(iunit,num,dat)\n");
   F77("*-------------------------------------------------------------------\n");
   F77("*  FEEL P2 System Subroutine\n");
   F77("*-------------------------------------------------------------------\n");
   F77("*  Purpose: 実数配列をファイルから読む\n");
   F77("*-------------------------------------------------------------------\n");
   F77("      implicit real*8 (a-h,o-z)\n");
   F77("      dimension dat(num)\n");
   F77("*\n");
   F77("      read(iunit) (dat(i),i=1,num)\n");
   F77("      return\n");
   F77("      end\n");
 CloseFile(fp);
 return;
}
