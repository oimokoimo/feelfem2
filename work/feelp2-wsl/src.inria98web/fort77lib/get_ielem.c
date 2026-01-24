/*
   FEEL p2  MAKE FORTRAN LIBRARY   get_ielem
 */

#include <stdio.h>
#include "../feel_def/feel_def.h"
#include "../system/system.h"

#define FNAME "get_ielem.f"
void lib_get_ielem()
{
   FILE *fp;
   StoreMakefile(FNAME,SYSTEM_LIBRARY);
   if(LIMIT_FILE == 1) return;
   fp = OpenFileToWrite( FNAME );
   F77("      subroutine get_ielem(iunit,ielem,matno,neelem,nenode)\n");
   F77("*-------------------------------------------------------------------\n");
   F77("*  FEEL P2 System Subroutine\n");
   F77("*-------------------------------------------------------------------\n");
   F77("*  Purpose: read ielem,matno array\n");
   F77("*  \n");
   F77("*  Caution:\n");
   F77("*\n");
   F77("*-------------------------------------------------------------------\n");
   F77("      dimension ielem(nenode,neelem)\n");
   F77("      dimension matno(neelem)\n");
   F77("*\n");
   F77("      rewind(iunit)\n");
   F77("*\n");
   F77("      read(iunit) ne,np\n");
   F77("*\n");
   F77("      if(ne .ne. neelem .or. np.ne. nenode) stop 'get_ielem mismatch'\n");
   F77("*\n");
   F77("      read(iunit) ((ielem(i,j),i=1,nenode),j=1,neelem)\n");
   F77("      read(iunit) (matno(i),i=1,neelem)\n");
   F77("*\n");
   F77("      return\n");
   F77("      end\n");
   F77("\n");
 CloseFile(fp);
 return;
}
