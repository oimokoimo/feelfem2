/*
   FEEL p2  MAKE FORTRAN LIBRARY   p_unsym_mscg
 */

#include <stdio.h>
#include "../feel_def/feel_def.h"
#include "../system/system.h"

#define FNAME "p_unsym_mscg.f"
lib_p_unsym_mscg()
{
   FILE *fp;
   StoreMakefile(FNAME,SYSTEM_LIBRARY);
   if(LIMIT_FILE == 1) return;
   fp = OpenFileToWrite( FNAME );
   F77("      subroutine p_unsym_mscg(rank,feelpara,A,MJ,neq_sub,JA,JDP,\n");
   F77("     $     B,U,naisum,naieq,nintotal,ninner,npesum,nsendnum,\n");
   F77("     $     nrecvnum,nsesum,nresum,nsendlist,nrecvlist,\n");
   F77("     $     nsendkaz,nrecvkaz,nsendtable,nrecvtable,\n");
   F77("     $     np_nsrequ,srb,eps,IPM,IT,W,rnorm,\n");
   F77("     $     KTI)\n");
   F77("c\n");
   F77("c---------------------------------------------------\n");
   F77("c     Scaled BiCGSTAB method (two dimensional array)\n");
   F77("c---------------------------------------------------\n");
   F77("c\n");
   F77("      implicit real*8 (a-h,o-z)\n");
   F77("      integer rank\n");
   F77("*\n");
   F77("      real*4 feelpara(*)\n");
   F77("*\n");
   F77("      dimension A(neq_sub,MJ),JA(neq_sub,MJ),B(neq_sub)\n");
   F77("      dimension U(neq_sub)\n");
   F77("*\n");
   F77("      dimension naieq(naisum)\n");
   F77("      dimension ninner(nintotal)\n");
   F77("      dimension nsendlist(npesum),nrecvlist(npesum)\n");
   F77("      dimension nsendkaz(npesum),nrecvkaz(npesum)\n");
   F77("      dimension nsendtable(npesum),nrecvtable(npesum)\n");
   F77("      dimension np_nsrequ(npesum)\n");
   F77("      dimension srb(nsesum+nresum)\n");
   F77("c\n");
   F77("      dimension IPM(*)\n");
   F77("c\n");
   F77("      dimension W(neq_sub,8)\n");
   F77("*\n");
   F77("      if (IPM(1).eq.0) then\n");
   F77("*\n");
   F77("*-----------------------\n");
   F77("*     IPM(1)=0 -> diagonal scaling\n");
   F77("*----------------------\n");
   F77("*     Unsymmetric solver : BiCGSTAB method \n");
   F77("*                        : p_sbicgstab1\n");
   F77("*---------------------\n");
   F77("*\n");
   F77("c\n");
   F77("         call p_msbicg_stab (rank,npesum,U,\n");
   F77("     $        B,neq_sub,\n");
   F77("     $        naisum,naieq,ninner,\n");
   F77("     $        nintotal,IT,A,JA,MJ,\n");
   F77("     $        W,eps,\n");
   F77("     $        IPM,\n");
   F77("     $        srb,feelpara(np_nsrequ(1)),nsendnum,\n");
   F77("     $        nrecvnum,\n");
   F77("     $        nsesum,nresum,rnorm,nsendlist,nrecvlist,\n");
   F77("     $        nsendkaz,nrecvkaz,nsendtable,nrecvtable,\n");
   F77("     $        JDP,KTI,feelpara)\n");
   F77("*\n");
   F77("*\n");
   F77("      end if\n");
   F77("c\n");
   F77("      return\n");
   F77("      end\n");
   F77("\n");
   F77("\n");
   F77("\n");
   F77("\n");
   F77("\n");
 CloseFile(fp);
 return;
}
