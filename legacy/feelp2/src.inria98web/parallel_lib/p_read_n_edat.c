/*
   FEEL p2  MAKE FORTRAN LIBRARY   p_read_n_edat
 */

#include <stdio.h>
#include "../feel_def/feel_def.h"
#include "../system/system.h"

#define FNAME "p_read_n_edat.f"
lib_p_read_n_edat()
{
   FILE *fp;
   StoreMakefile(FNAME,SYSTEM_LIBRARY);
   if(LIMIT_FILE == 1) return;
   fp = OpenFileToWrite( FNAME );
   F77("      subroutine p_read_n_edat (iunit,nbnesum1,nbnesum2,\n");
   F77("     $     ibsubelem)\n");
   F77("*\n");
   F77("*++++++++++++++++++++++++++++++\n");
   F77("*     FEEL/P2/Cenju-3/MPI subprogram\n");
   F77("*++++++++++++++++++++++++++\n");
   F77("*     \n");
   F77("*     Read Neumann data from dat.PE@@@.X file\n");
   F77("*\n");
   F77("*+++++++++++++++++++++++++++\n");
   F77("      implicit real*8 (a-h,o-z)\n");
   F77("*\n");
   F77("      character*20 fmt\n");
   F77("*\n");
   F77("      dimension ibsubelem(nbnesum2,nbnesum1)\n");
   F77("*\n");
   F77("      write (fmt,8001) nbnesum2\n");
   F77(" 8001 format('(',i,'i8)')\n");
   F77("      read (iunit,fmt) (ibsubelem(j,1),j=1,nbnesum2)\n");
   F77("      do 10 i=2,nbnesum1\n");
   F77("         read (iunit,9001) ndummy\n");
   F77("         read (iunit,fmt) (ibsubelem(j,i),j=1,nbnesum2)\n");
   F77(" 10   continue\n");
   F77("*\n");
   F77(" 9001 format(i8)\n");
   F77("      return\n");
   F77("      end\n");
 CloseFile(fp);
 return;
}
