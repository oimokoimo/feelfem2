/*
   FEEL p2  MAKE FORTRAN LIBRARY   p_read_d_nset
 */

#include <stdio.h>
#include "../feel_def/feel_def.h"
#include "../system/system.h"

#define FNAME "p_read_d_nset.f"
lib_p_read_d_nset()
{
   FILE *fp;
   StoreMakefile(FNAME,SYSTEM_LIBRARY);
   if(LIMIT_FILE == 1) return;
   fp = OpenFileToWrite( FNAME );
   F77("      subroutine p_read_d_nset(iunit,nbdisum1,nbdisum2,\n");
   F77("     $     nsyori,inset)\n");
   F77("*++++++++++++++++++++++++++++++\n");
   F77("*     FEEL/P2/Cenju-3/MPI subprogram\n");
   F77("*++++++++++++++++++++++++++\n");
   F77("*     \n");
   F77("*     Read Dirichlet data from dat.PE@@@.X file\n");
   F77("*\n");
   F77("*+++++++++++++++++++++++++++\n");
   F77("      implicit real*8 (a-h,o-z)\n");
   F77("*\n");
   F77("      character*20 fmt\n");
   F77("*     \n");
   F77("      dimension inset(nbdisum2,nbdisum1),nsyori(nbdisum1)\n");
   F77("*\n");
   F77("      write (fmt,8001) nbdisum2+1\n");
   F77(" 8001 format('(',i,'i8)')\n");
   F77("*\n");
   F77("      read (iunit,fmt) nsyori(1),(inset(j,1),j=1,nbdisum2)\n");
   F77("      do 10 i=2,nbdisum1\n");
   F77("         read (iunit,9001) ndummy\n");
   F77("         read (iunit,fmt) nsyori(i),(inset(j,i),j=1,\n");
   F77("     $        nbdisum2)\n");
   F77(" 10   continue\n");
   F77("*\n");
   F77(" 9001 format(i8)\n");
   F77("*\n");
   F77("      return\n");
   F77("      end\n");
   F77("      \n");
 CloseFile(fp);
 return;
}
