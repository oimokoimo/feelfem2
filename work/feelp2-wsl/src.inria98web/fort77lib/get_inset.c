/*
   FEEL p2  MAKE FORTRAN LIBRARY   get_inset
 */

#include <stdio.h>
#include "../feel_def/feel_def.h"
#include "../system/system.h"

#define FNAME "get_inset.f"
void lib_get_inset()
{
   FILE *fp;
   StoreMakefile(FNAME,SYSTEM_LIBRARY);
   if(LIMIT_FILE == 1) return;
   fp = OpenFileToWrite( FNAME );
   F77("      subroutine get_inset(iunit,inset,nodes,np)\n");
   F77("*-------------------------------------------------------------------\n");
   F77("*  FEEL P2 System Subroutine\n");
   F77("*-------------------------------------------------------------------\n");
   F77("*  Purpose: read insetrm  array\n");
   F77("*  \n");
   F77("*  Caution:\n");
   F77("*\n");
   F77("*-------------------------------------------------------------------\n");
   F77("      dimension inset(np,nodes)\n");
   F77("*\n");
   F77("      rewind(iunit)\n");
   F77("*\n");
   F77("      read(iunit) n1,n2\n");
   F77("*\n");
   F77("      if(n1 .ne. nodes .or. n2 .ne. np) stop 'get_inset mismatch'\n");
   F77("*\n");
   F77("      read(iunit) ((inset(i,j),i=1,np),j=1,nodes)\n");
   F77("*\n");
   F77("      return\n");
   F77("      end\n");
   F77("\n");
 CloseFile(fp);
 return;
}
