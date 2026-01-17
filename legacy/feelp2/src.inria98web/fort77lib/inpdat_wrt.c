/*
   FEEL p2  MAKE FORTRAN LIBRARY   inpdat_wrt
 */

#include <stdio.h>
#include "../feel_def/feel_def.h"
#include "../system/system.h"

#define FNAME "inpdat_wrt.f"
lib_inpdat_wrt()
{
   FILE *fp;
   StoreMakefile(FNAME,SYSTEM_LIBRARY);
   if(LIMIT_FILE == 1) return;
   fp = OpenFileToWrite( FNAME );
   F77("      subroutine inpdat_wrt\n");
   F77("*-------------------------------------------------------------------\n");
   F77("*  FEEL P2 System Subroutine\n");
   F77("*-------------------------------------------------------------------\n");
   F77("*  Purpose: show input data\n");
   F77("*  \n");
   F77("*  Caution:\n");
   F77("*\n");
   F77("*-------------------------------------------------------------------\n");
   common_parameters(fp);
   COM;
   CommonBlock(fp);
   comment1(fp);
   F77("      write(*,*) 'READ feel_dat FILE'\n");
   F77("*\n");
   F77("*      write(*,*) 'ndim  = ',ndim\n");
   F77("*      write(*,*) 'npmax = ',npmax\n");
   F77("*      write(*,*) 'nedat = ',nedat\n");
   F77("*      write(*,*) 'nnodeset =',nnodeset\n");
   F77("*      write(*,*) 'nnumdat = ',nnumdat\n");
   F77("*      write(*,*) 'io_edat = ',io_edat\n");
   F77("*      write(*,*) 'np_work=',np_work_get_falloc()\n");
   F77("\n");
   F77("      return\n");
   F77("      end\n");
   F77("\n");
 CloseFile(fp);
 return;
}
