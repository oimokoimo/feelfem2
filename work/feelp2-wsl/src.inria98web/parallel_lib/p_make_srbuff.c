/*
   FEEL p2  MAKE FORTRAN LIBRARY   p_make_srbuff
 */

#include <stdio.h>
#include "../feel_def/feel_def.h"
#include "../system/system.h"

#define FNAME "p_make_srbuff.f"
lib_p_make_srbuff()
{
   FILE *fp;
   StoreMakefile(FNAME,SYSTEM_LIBRARY);
   if(LIMIT_FILE == 1) return;
   fp = OpenFileToWrite( FNAME );
   F77("      subroutine p_make_srbuff (p_rank,nsendnum,nrecvnum,npesum,\n");
   F77("     $     nsendkaz,nrecvkaz,nsendlist,nrecvlist,nsesum,nresum)\n");
   F77("*      \n");
   F77("      implicit real*8 (a-h,o-z)\n");
   F77("*\n");
   F77("      integer p_rank\n");
   F77("      dimension nsendkaz(npesum),nrecvkaz(npesum)\n");
   F77("      dimension nsendlist(npesum),nrecvlist(npesum)\n");
   F77("*\n");
   F77("*-------------------------------------\n");
   F77("*     initialization of nsesum,nresum\n");
   F77("*-------------------------------------\n");
   F77("*\n");
   F77("      nsesum=0\n");
   F77("      nresum=0\n");
   F77("*\n");
   F77("*-------------------------------------------\n");
   F77("*  nsesum : number of the total sending data \n");
   F77("*           in each sending subdomain \n");
   F77("*-------------------------------------------\n");
   F77("*\n");
   F77("      if (nsendlist(p_rank+1).eq.1) then\n");
   F77("         do 100 i=1,nsendnum\n");
   F77("            nsesum=nsesum+nsendkaz(i)\n");
   F77(" 100     continue\n");
   F77("      end if\n");
   F77("*---------------------------------------------\n");
   F77("*  nresum : number of the total receiving data \n");
   F77("*           in each receiving subdomain \n");
   F77("*---------------------------------------------\n");
   F77("*\n");
   F77("*\n");
   F77("      if (nrecvlist(p_rank+1).eq.1) then \n");
   F77("         do 110 i=1,nrecvnum\n");
   F77("            nresum=nresum+nrecvkaz(i)\n");
   F77(" 110     continue\n");
   F77("      end if\n");
   F77("      return\n");
   F77("      end\n");
   F77("\n");
 CloseFile(fp);
 return;
}
