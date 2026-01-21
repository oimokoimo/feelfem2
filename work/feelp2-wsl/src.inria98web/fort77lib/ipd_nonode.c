/*
   FEEL p2  MAKE FORTRAN LIBRARY   ipd_nonode
 */

#include <stdio.h>
#include "../feel_def/feel_def.h"
#include "../system/system.h"

#define FNAME "ipd_nonode.f"
lib_ipd_nonode()
{
   FILE *fp;
   StoreMakefile(FNAME,SYSTEM_LIBRARY);
   if(LIMIT_FILE == 1) return;
   fp = OpenFileToWrite( FNAME );
   F77("      subroutine ipd_nonode(iarg1,iarg2,iarg3,farg1,farg2)\n");
   F77("*-------------------------------------------------------------------\n");
   F77("*  FEEL P2 System Subroutine\n");
   F77("*-------------------------------------------------------------------\n");
   F77("*  Purpose: nodeless freedom \n");
   F77("*-------------------------------------------------------------------\n");
   F77("      stop 'Future Function(ipd_nonode)'\n");
   F77("      end\n");
 CloseFile(fp);
 return;
}
