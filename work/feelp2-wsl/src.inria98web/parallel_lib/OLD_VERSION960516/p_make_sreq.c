/*
   FEEL p2  MAKE FORTRAN LIBRARY   p_make_sreq
 */

#include <stdio.h>
#include "../feel_def/feel_def.h"
#include "../system/system.h"

#define FNAME "p_make_sreq.f"
lib_p_make_sreq()
{
   FILE *fp;
   StoreMakefile(FNAME,SYSTEM_LIBRARY);
   if(LIMIT_FILE == 1) return;
   fp = OpenFileToWrite( FNAME );
   F77("      subroutine p_make_sreq (nsendtable,nsendnum,nsendndkaz,\n");
   F77("     $     feel,iunit,np_nsenod,IPFsub,ipdsub,npmaxsub,\n");
   F77("     $     np_nsrequ,nmade,nsendkaz,nrecvnum,npesum,\n");
   F77("     $     idat,nbase,ipe,nrecvtable,nrecvndkaz,np_nrenod,\n");
   F77("     $     nrecvndkaz,nsendlist,nrecvlist,ndisub,neusub,npe)\n");
   F77("*++++++++++++++++++++++++++++++\n");
   F77("*     FEEL/P2/Cenju-3/MPI subprogram\n");
   F77("*     Purpose : change node data to equation data\n");
   F77("*++++++++++++++++++++++++++\n");
   F77("*\n");
   F77("      implicit real*8 (a-h,o-z)\n");
   F77("*\n");
   F77("      real*4 feel(*)\n");
   F77("*\n");
   F77("      dimension nsendtable(npesum),nsendndkaz(npesum)\n");
   F77("      dimension nsendkaz(npesum)\n");
   F77("      dimension np_nsenod(npesum)\n");
   F77("      dimension np_nsrequ(npesum)\n");
   F77("      dimension IPFsub(npmaxsub),ipdsub(npmaxsub)\n");
   F77("      dimension idat(2,*),nbase(2,*)\n");
   F77("      dimension nrecvtable(npesum),nrecvndkaz(npesum)\n");
   F77("      dimension nrecvkaz(npesum),np_nrenod(npesum)\n");
   F77("      dimension nsendlist(npesum),nrecvlist(npesum)\n");
   F77("*-----------------------\n");
   F77("*\n");
   F77("      if (nsendlist(ipe).eq.1) then\n");
   F77("         do 20 i=1,nsendnum\n");
   F77("            nsdonum=nsendndkaz(i)\n");
   F77("            call p_calc_neq (nsdonum,feel(np_nsenod(i)),\n");
   F77("     $           nseqnum,IPFsub,npmaxsub)\n");
   F77("            nsendkaz(i)=nseqnum\n");
   F77("*\n");
   F77("            call f_alloc (np_nsrequ(i),'Read nsrequ(i)',\n");
   F77("     $           nseqnum,0)\n");
   F77("*\n");
   F77("            idat(1,nmade+23+2*ndisub+neusub+i)\n");
   F77("     $           =np_nsrequ(i)-nbase(1,ipe)+nbase(1,1)\n");
   F77("            idat(2,nmade+23+2*ndisub+neusub+i)\n");
   F77("     $           =nseqnum\n");
   F77("*\n");
   F77("            call p_make_eqno (nsdonum,feel(np_nsenod(i)),\n");
   F77("     $           IPFsub,ipdsub,feel(np_nsrequ(i)),\n");
   F77("     $           nseqnum,npmaxsub)\n");
   F77("*\n");
   F77(" 20      continue\n");
   F77("      end if\n");
   F77("*\n");
   F77("*     ++++++$B<u?.MQ%G!<%?$rJ}Dx<0?t!\"J}Dx<0HV9f$KD>$9!#(B++++\n");
   F77("      if (nrecvlist(ipe).eq.1) then\n");
   F77("         do 21 i=1,nrecvnum\n");
   F77("            nrdonum=nrecvndkaz(i)\n");
   F77("            call p_calc_neq (nrdonum,feel(np_nrenod(i)),\n");
   F77("     $           nreqnum,IPFsub,npmaxsub)\n");
   F77("            nrecvkaz(i)=nreqnum\n");
   F77("*\n");
   F77("            call f_alloc (np_nsrequ(i+nsendnum),'Read nsrequ(i)',\n");
   F77("     $           nreqnum,0)\n");
   F77("*\n");
   F77("            idat(1,nmade+23+2*ndisub+neusub+npe+i)\n");
   F77("     $           =np_nsrequ(i+nsendnum)-nbase(1,ipe)+nbase(1,1)\n");
   F77("            idat(2,nmade+23+2*ndisub+neusub+npe+i)\n");
   F77("     $           =nreqnum\n");
   F77("*\n");
   F77("            call p_make_eqno (nrdonum,feel(np_nrenod(i)),\n");
   F77("     $           IPFsub,ipdsub,feel(np_nsrequ(i+nsendnum)),\n");
   F77("     $           nreqnum,npmaxsub)\n");
   F77("*     \n");
   F77(" 21      continue\n");
   F77("      end if\n");
   F77("*\n");
   F77("      if ((nsendlist(ipe).eq.0).and.(nrecvlist(ipe).eq.0))\n");
   F77("     $     then\n");
   F77("         call f_alloc (np_nsrequ(1),'Read nsrequ(1)',\n");
   F77("     $        1,0)\n");
   F77("         idat(1,nmade+23+2*ndisub+neusub+1)\n");
   F77("     $        =np_nsrequ(1)-nbase(1,ipe)+nbase(1,1)\n");
   F77("         idat(2,nmade+23+2*ndisub+neusub+1)\n");
   F77("     $        =1\n");
   F77("      end if\n");
   F77("*\n");
   F77("      return\n");
   F77("      end      \n");
   F77("\n");
   F77("\n");
 CloseFile(fp);
 return;
}
