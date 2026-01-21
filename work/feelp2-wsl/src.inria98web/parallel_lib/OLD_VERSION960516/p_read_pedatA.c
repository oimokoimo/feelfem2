/*
   FEEL p2  MAKE FORTRAN LIBRARY   p_read_pedatA
 */

#include <stdio.h>
#include "../feel_def/feel_def.h"
#include "../system/system.h"

#define FNAME "p_read_pedatA.f"
lib_p_read_pedatA()
{
   FILE *fp;
   StoreMakefile(FNAME,SYSTEM_LIBRARY);
   if(LIMIT_FILE == 1) return;
   fp = OpenFileToWrite( FNAME );
   F77("      subroutine p_read_pedatA(iunit,npesum,npmaxsub,\n");
   F77("     $     nelemsub,np,ndisub,\n");
   F77("     $     neusub,\n");
   F77("     $     isubelem,nelegru,\n");
   F77("     $     nloglo,matno,\n");
   F77("     $     nsendlist,nrecvlist,\n");
   F77("     $     ndikaz,ndinum,neukaz,neunum,ipe,\n");
   F77("     $     nmatrix)\n");
   F77("*+++++++++++++++++++++++++++++++++++++++++++++++\n");
   F77("*     Date: 1995 9/21\n");
   F77("*+++++++++++++++++++++++++++++++++++++++++++++\n");
   F77("      implicit real*8 (a-h,o-z)\n");
   F77("*\n");
   F77("*\n");
   F77("*----------------------------------------\n");
   F77("*     nloglo(npmaxsub): nloglo(i)$B$OItJ,NN0h(Brank+1\n");
   F77("*     $B$G$NItJ,@aE@HV9f(Bi$B$NA4BN@aE@HV9f(B\n");
   F77("*\n");
   F77("*     $B3F%W%m%;%C%5C4Ev$NItJ,NN0h?t!'(Bnelemsub=nel(ip)\n");
   F77("*     isubelem(np,nelemsub): isubelem(ln,ie)=\n");
   F77("*                           ilnode(ln,ie,ip)(\n");
   F77("*               $BItJ,NN0hHV9f(Bip$B$G@.N)(B)\n");
   F77("*     nelegru(nelemsub): nelegru(i)=ngru(i+nbb(ip-1,nankai))\n");
   F77("*                ($BItJ,NN0hHV9f(Bip$B$G@.N)(B)\n");
   F77("*     matno(nelemsub) :$BA4BNMWAGHV9f$G(Bngru(i+nbb(ip-1,nankai))\n");
   F77("*     $B$NMWAG:`NAHV9f(B\n");
   F77("*     nrecvlist(npesum) : $B%$%s%?!<%U%'!<%9>e$N(B\n");
   F77("*     $B%G!<%?$NB-$79~$_$r9T$&ItJ,NN0hHV9f!#(B(\n");
   F77("*     $BMW$9$k$K%G!<%?$r:G=i<u?.$9$kItJ,NN0hHV9f(B)\n");
   F77("*\n");
   F77("*     nsendlist(npesum) : $B%$%s%?!<%U%'!<%9>e$N(B\n");
   F77("*     $B%G!<%?$rB-$79~$_$N0Y$KAw?.$9$kItJ,NN0hHV9f!#(B(\n");
   F77("*     $BMW$9$k$K%G!<%?$r:G=iAw?.$9$kItJ,NN0hHV9f(B)\n");
   F77("*\n");
   F77("*\n");
   F77("*&------------------------------------\n");
   F77("*\n");
   F77("      character*20 fmt\n");
   F77("*\n");
   F77("      dimension nloglo(npmaxsub)\n");
   F77("      dimension nelegru(nelemsub),isubelem(np,nelemsub)\n");
   F77("      dimension matno(nelemsub)\n");
   F77("      dimension ndikaz(*),ndinum(*),neukaz(*),neunum(*)\n");
   F77("      dimension nsendlist(*),nrecvlist(*)\n");
   F77("*\n");
   F77("*     ----- $B3F%W%m%;%C%5$KI,MW$J%G!<%?$NFI$_9~$_(B ----\n");
   F77("* ---- $B3FItJ,NN0h$NItJ,@aE@HV9f$HA4BN@aE@HV9f$H$NBP1~(B ---\n");
   F77("      do 10 is=1,npmaxsub\n");
   F77("         read (iunit,9001) nloglo(is)\n");
   F77(" 10   continue\n");
   F77("*\n");
   F77("*     ---- $B%$%s%?!<%U%'!<%9>e$N%G!<%?$rAw?.$9$kItJ,NN0hHV9f(B--      \n");
   F77("      do 20 is=1,npesum\n");
   F77("         read (iunit,9001) nsendlist(is)\n");
   F77(" 20   continue\n");
   F77("*\n");
   F77("*     ---- $B%$%s%?!<%U%'!<%9>e$N%G!<%?$r<u?.$9$kItJ,NN0hHV9f(B--      \n");
   F77("      do 30 is=1,npesum\n");
   F77("         read (iunit,9001) nrecvlist(is)\n");
   F77(" 30   continue\n");
   F77("*     \n");
   F77("*     ++++++++++++++++++++++++++++\n");
   F77("*     $BMWAGFb@aE@HV9f$HItJ,@aE@HV9f$H$NBP1~!\"(B\n");
   F77("*     $BMWAG:`NAHV9f$rFI$_9~$`!#(B\n");
   F77("*     ++++++++++++++++++++++++++++\n");
   F77("      write (fmt,8001) np+1\n");
   F77(" 8001 format ('(',i,'i8)')\n");
   F77("      do 31 i=1,nelemsub\n");
   F77("         read (iunit,fmt) (isubelem(ln,i),ln=1,np),\n");
   F77("     $        matno(i)\n");
   F77(" 31   continue\n");
   F77("*\n");
   F77("      do 50 j=1,nelemsub\n");
   F77("         read (iunit,9001) nelegru(j)\n");
   F77(" 50   continue\n");
   F77("*\n");
   F77("*     ------ $B3FItJ,NN0h(Biq$B$G(BDirichlet$B>r7o(B(feel_dat$B$G@aE@=89g(B\n");
   F77("*     'NSET'$B$H$7$F(Bin$BHVL\(B)$B$,2]$5$l$F$$$k?t$H$=$N(B\n");
   F77("*     $BNs$N?t$rFI$_9~$`!#(B---\n");
   F77("*\n");
   F77("      do 60 in=1,ndisub\n");
   F77("         read (iunit,9011) ndikaz(in),ndinum(in)\n");
   F77(" 60   continue      \n");
   F77("*    ------ $B3FItJ,NN0h(Biq(rank+1)$B$G(BNeumann$B>r7o(B(feel_dat$B$G6-3&MWAG(B\n");
   F77("*     $B$H$7$F(Bin$BHVL\(B)$B$,2]$5$l$F$$$k?t$rFI$_9~$`!#(B---\n");
   F77("*     ----- $BMWAG@aE@=89g(BEDAT$B$N?t(B-1\"neusub\"-----\n");
   F77("      do 70 in=1,neusub\n");
   F77("         read (iunit,9011) neukaz(in),neunum(in)\n");
   F77(" 70   continue\n");
   F77("*     \n");
   F77(" 9001 format(i8)\n");
   F77(" 9011 format(2i8)\n");
   F77("      return\n");
   F77("      end\n");
 CloseFile(fp);
 return;
}
