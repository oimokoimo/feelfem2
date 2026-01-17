/*
   FEEL p2  MAKE FORTRAN LIBRARY   p_read_rdat
 */

#include <stdio.h>
#include "../feel_def/feel_def.h"
#include "../system/system.h"

#define FNAME "p_read_rdat.f"
lib_p_read_rdat()
{
   FILE *fp;
   StoreMakefile(FNAME,SYSTEM_LIBRARY);
   if(LIMIT_FILE == 1) return;
   fp = OpenFileToWrite( FNAME );
   F77("      subroutine p_read_rdat(nrecvtable,nrecvnum,nrecvndkaz,\n");
   F77("     $     feel,iunit,np_nrenod,npmaxsub,npesum,idat,nbase,\n");
   F77("     $     ipe,nrecvlist)\n");
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
   F77("      dimension nrecvtable(npesum),nrecvndkaz(npesum)\n");
   F77("      dimension np_nrenod(npesum)\n");
   F77("      dimension idat(2,*),nbase(2,*)\n");
   F77("      dimension nrecvlist(npesum)\n");
   F77("*\n");
   F77("      if (nrecvlist(ipe).eq.1) then\n");
   F77("         do 10 i=1,nrecvnum\n");
   F77("*     \n");
   F77("            read (iunit,9001) nrecvndkaz(i)\n");
   F77("            nrdonum = nrecvndkaz(i)\n");
   F77("*\n");
   F77("            call f_alloc (np_nrenod(i),'Read nrenod(i)'.\n");
   F77("     $           nrdonum,0)\n");
   F77("*\n");
   F77("            call p_read_pedatC (feel(np_nrenod(i)),\n");
   F77("     $           nrdonum,nrevtable,i,iunit)\n");
   F77(" 10      continue\n");
   F77("      end if\n");
   F77("*\n");
   F77(" 9001 format(i8)\n");
   F77("      return\n");
   F77("      end\n");
 CloseFile(fp);
 return;
}
