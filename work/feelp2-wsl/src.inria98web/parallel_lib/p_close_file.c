/*
   FEEL p2  MAKE FORTRAN LIBRARY   p_close_file
 */

#include <stdio.h>
#include "../feel_def/feel_def.h"
#include "../system/system.h"

#define FNAME "p_close_file.f"
lib_p_close_file()
{
   FILE *fp;
   StoreMakefile(FNAME,SYSTEM_LIBRARY);
   if(LIMIT_FILE == 1) return;
   fp = OpenFileToWrite( FNAME );
   F77("      subroutine p_close_file\n");
   F77("c\n");
   F77("      implicit real*8 (a-h,o-z)\n");
   F77("c\n");
   F77("      integer p_rank\n");
   F77("      common /feel_geo/ndim,npmax,ndomain,nedat,nnodeset,nnumdat,nip\n");
   F77("      common /feel_fil/io_in,io_tmp,io_out,io_stderr,\n");
   F77("     &                 io_edat,io_node,io_num,io_fem\n");
   F77("      common /feel_para/npe,p_rank,ncont1,ncont2\n");
   F77("c\n");
   F77("      do 10 no=1,nedat\n");
   F77("         close (io_edat + no - 1)\n");
   F77(" 10   continue\n");
   F77("c\n");
   F77("      do 20 no=1,nnodeset\n");
   F77("         close (io_node + no -1)\n");
   F77(" 20   continue\n");
   F77("c\n");
   F77("      close (io_stderr)\n");
   F77("      close (io_in)\n");
   F77("      close (io_out)\n");
   F77("c\n");
   F77("      do 30 no = 1 , nnumdat\n");
   F77("         close (io_num+no-1) \n");
   F77(" 30   continue\n");
   F77("c\n");
   F77("      return\n");
   F77("      end\n");
 CloseFile(fp);
 return;
}
