/*
   FEEL p2  MAKE FORTRAN LIBRARY   p_solve_plset
 */

#include <stdio.h>
#include "../feel_def/feel_def.h"
#include "../system/system.h"

#define FNAME "p_solve_plset.f"
lib_p_solve_plset()
{
   FILE *fp;
   StoreMakefile(FNAME,SYSTEM_LIBRARY);
   if(LIMIT_FILE == 1) return;
   fp = OpenFileToWrite( FNAME );
   F77("      subroutine p_solve_plset (rank,feelpara,neq_sub,B,\n");
   F77("     $     srb,np_nsrequ,nsendnum,nrecvnum,\n");
   F77("     $     npesum,nsesum,nresum,\n");
   F77("     $     nsendkaz,nrecvkaz,nsendlist,nrecvlist,nsendtable,\n");
   F77("     $     nrecvtable)  \n");
   F77("*\n");
   F77("*++++++++++++++++++++++++++++++\n");
   F77("*     FEEL/P2/Cenju-3/MPI subprogram\n");
   F77("*     Purpose : np_nsrequ(npesum) <->np_npsre\n");
   F77("*             : summation of the values on the interface for \n");
   F77("*               solving\n");
   F77("*++++++++++++++++++++++++++\n");
   F77("*     \n");
   F77("      implicit real*8 (a-h,o-z)\n");
   F77("*\n");
   F77("      real*4 feelpara(*)\n");
   F77("*\n");
   F77("      integer rank\n");
   F77("*\n");
   F77("      dimension B(neq_sub)\n");
   F77("*\n");
   F77("      dimension srb(nsesum+nresum)\n");
   F77("      dimension np_nsrequ(npesum)\n");
   F77("*\n");
   F77("*\n");
   F77("      dimension nsendkaz(npesum),nrecvkaz(npesum)\n");
   F77("      dimension nsendtable(npesum),nrecvtable(npesum)\n");
   F77("      dimension nsendlist(npesum),nrecvlist(npesum)\n");
   F77("c\n");
   F77("      call data_plus (rank,neq_sub,B,srb,\n");
   F77("     $     feelpara(np_nsrequ(1)),\n");
   F77("     $     nsendnum,nrecvnum,\n");
   F77("     $     npesum,nsesum,nresum,nsendkaz,nrecvkaz,nsendlist,\n");
   F77("     $     nrecvlist,nsendtable,nrecvtable)\n");
   F77("*\n");
   F77("      return\n");
   F77("      end\n");
 CloseFile(fp);
 return;
}
