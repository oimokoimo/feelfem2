/*
   FEEL p2  MAKE FORTRAN LIBRARY   p_read_sdat
 */

#include <stdio.h>
#include "../feel_def/feel_def.h"
#include "../system/system.h"

#define FNAME "p_read_sdat.f"
lib_p_read_sdat()
{
   FILE *fp;
   StoreMakefile(FNAME,SYSTEM_LIBRARY);
   if(LIMIT_FILE == 1) return;
   fp = OpenFileToWrite( FNAME );
   F77("      subroutine p_read_sdat(nsendtable,nsendnum,nsendndkaz,\n");
   F77("     $     feel,iunit,np_nsenod,npmaxsub,npesum,ipe,nsendlist)\n");
   F77("*++++++++++++++++++++++++++++++\n");
   F77("*     FEEL/P2/Cenju-3/MPI subprogram\n");
   F77("*++++++++++++++++++++++++++\n");
   F77("*     Read node set data from dat.PE@@@.X file\n");
   F77("*\n");
   F77("*++++++++++++++++++++++++++\n");
   F77("      implicit real*8 (a-h,o-z)\n");
   F77("*-------------------------\n");
   F77("      real*4 feel(*)\n");
   F77("*\n");
   F77("      dimension nsendtable(npesum),nsendndkaz(npesum)\n");
   F77("      dimension np_nsenod(npesum)\n");
   F77("      dimension nsendlist(npesum)\n");
   F77("*\n");
   F77("      if (nsendlist(ipe).eq.1) then\n");
   F77("         do 10 i=1,nsendnum\n");
   F77("*     \n");
   F77("            read (iunit,9001) nsendndkaz(i)\n");
   F77("            nsdonum = nsendndkaz(i)\n");
   F77("*\n");
   F77("            call f_alloc (np_nsenod(i),'Read nsenod(i)',\n");
   F77("     $           nsdonum,0,0)\n");
   F77("*\n");
   F77("            call p_read_pedatC (feel(np_nsenod(i)),\n");
   F77("     $           nsdonum,nsendtable,i,iunit)\n");
   F77(" 10      continue\n");
   F77("      end if\n");
   F77("*\n");
   F77(" 9001 format(i8)\n");
   F77("      return\n");
   F77("      end\n");
   F77("\n");
 CloseFile(fp);
 return;
}
