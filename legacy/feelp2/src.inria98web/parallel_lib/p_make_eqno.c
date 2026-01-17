/*
   FEEL p2  MAKE FORTRAN LIBRARY   p_make_eqno
 */

#include <stdio.h>
#include "../feel_def/feel_def.h"
#include "../system/system.h"

#define FNAME "p_make_eqno.f"
lib_p_make_eqno()
{
   FILE *fp;
   StoreMakefile(FNAME,SYSTEM_LIBRARY);
   if(LIMIT_FILE == 1) return;
   fp = OpenFileToWrite( FNAME );
   F77("      subroutine p_make_eqno(nodsum,nnod,\n");
   F77("     $     IPFsub,ipdsub,nneq,neqsum,npmaxsub)\n");
   F77("*\n");
   F77("*\n");
   F77("      dimension nnod(nodsum)\n");
   F77("      dimension nneq(neqsum)\n");
   F77("*\n");
   F77("*     \n");
   F77("      dimension IPFsub(npmaxsub),ipdsub(npmaxsub)\n");
   F77("*++++++++++++++++++++++++++++++++++++++++\n");
   F77("*     Make equation number array(nneq(neqsum)) from\n");
   F77("*     node number array(nnod(nodsum))\n");
   F77("*++++++++++++++++++++++++++++++++++++++++++++++++\n");
   F77("      nruiseki=1\n");
   F77("      do 10 i=1,nodsum\n");
   F77("         if (IPFsub(nnod(i)).eq.0) then\n");
   F77("            stop 'nnod error'\n");
   F77("         end if\n");
   F77("         do 20 j=1,IPFsub(nnod(i))\n");
   F77("            nneq(nruiseki+j-1)=ipdsub(nnod(i))+\n");
   F77("     $           j-1\n");
   F77(" 20      continue\n");
   F77("         nruiseki=nruiseki+IPFsub(nnod(i))\n");
   F77(" 10   continue\n");
   F77("*\n");
   F77("      return\n");
   F77("      end\n");
 CloseFile(fp);
 return;
}
