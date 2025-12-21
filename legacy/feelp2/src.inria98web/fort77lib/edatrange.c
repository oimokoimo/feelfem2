/*
   FEEL p2  MAKE FORTRAN LIBRARY   edatrange
 */

#include <stdio.h>
#include "../feel_def/feel_def.h"
#include "../system/system.h"

#define FNAME "edatrange.f"
lib_edatrange()
{
   FILE *fp;
   StoreMakefile(FNAME,SYSTEM_LIBRARY);
   if(LIMIT_FILE == 1) return;
   fp = OpenFileToWrite( FNAME );
   F77("      subroutine edatrange(x,y,ielem,ne,np,XMIN,XMAX,YMIN,YMAX)\n");
   F77("*-------------------------------------------------------------------\n");
   F77("*  FEEL P2 System Subroutine\n");
   F77("*-------------------------------------------------------------------\n");
   F77("*  Purpose: Calculate the range of edat nodes\n");
   F77("*  \n");
   F77("*  Caution: This routine is for CONTOUR\n");
   F77("*\n");
   F77("*-------------------------------------------------------------------\n");
   F77("      implicit real*8 (a-h,o-z)\n");
   F77("      dimension x(*),y(*)\n");
   F77("      dimension ielem(np,ne)\n");
   F77("c\n");
   F77("      XMIN =  1.0d72\n");
   F77("      YMIN =  1.0d72\n");
   F77("      XMAX = -1.0d72\n");
   F77("      YMAX = -1.0d72\n");
   F77("      \n");
   F77("      do 100 i=1,ne\n");
   F77("         do 110 j=1,np\n");
   F77("            in = ielem(j,i)\n");
   F77("            xmin = min(xmin,x(in))\n");
   F77("            ymin = min(ymin,y(in))\n");
   F77("            xmax = max(xmax,x(in))\n");
   F77("            ymax = max(ymax,y(in))\n");
   F77(" 110     continue\n");
   F77(" 100  continue\n");
   F77("\n");
   F77("      return\n");
   F77("      end\n");
 CloseFile(fp);
 return;
}
