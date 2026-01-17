/*
   FEEL p2  MAKE FORTRAN LIBRARY   p_read_ndat
 */

#include <stdio.h>
#include "../feel_def/feel_def.h"
#include "../system/system.h"

#define FNAME "p_read_ndat.f"
lib_p_read_ndat()
{
   FILE *fp;
   StoreMakefile(FNAME,SYSTEM_LIBRARY);
   if(LIMIT_FILE == 1) return;
   fp = OpenFileToWrite( FNAME );
   F77("      subroutine p_read_ndat (iunit,np_ibsubelem,neukaz,neunum,\n");
   F77("     $     ndisub,neusub,feelpara,idat,nbase,nhenkaz1,nmade,ipe)\n");
   F77("*\n");
   F77("*------------------------------\n");
   F77("*\n");
   F77("*     Neumann条件の読み込み\n");
   F77("*\n");
   F77("*----------------------------\n");
   F77("      implicit real*8 (a-h,o-z)\n");
   F77("*\n");
   F77("      real*4 feelpara(*)\n");
   F77("      dimension np_ibsubelem(neusub)\n");
   F77("      dimension neukaz(neusub),neunum(neusub)\n");
   F77("      dimension idat(2,*),nbase(2,*)\n");
   F77("*\n");
   F77("*\n");
   F77("      do 10 i=1,neusub\n");
   F77("         if (neukaz(i).gt.0) then\n");
   F77("            read (iunit,9001) nosub\n");
   F77("*\n");
   F77("*     境界要素内節点と部分節点番号との対応\n");
   F77("            call f_alloc (np_ibsubelem(i),'Read ibsubelem',\n");
   F77("     $           neukaz(i)*neunum(i),0)\n");
   F77("            idat(1,nmade+23+i+2*ndisub)=np_ibsubelem(i)\n");
   F77("     $           -nbase(1,ipe)+nbase(1,1)\n");
   F77("            idat(2,nmade+23+i+2*ndisub)=neukaz(i)*neunum(i)\n");
   F77("*\n");
   F77("            call p_read_n_edat (iunit,neukaz(i),neunum(i),\n");
   F77("     $           feelpara(np_ibsubelem(i)))\n");
   F77("*\n");
   F77("         end if\n");
   F77(" 10   continue\n");
   F77("*\n");
   F77(" 9001 format(i8)\n");
   F77("*\n");
   F77("      return\n");
   F77("      end\n");
 CloseFile(fp);
 return;
}
