/*
   FEEL p2  MAKE FORTRAN LIBRARY   f_free
 */

#include <stdio.h>
#include "../feel_def/feel_def.h"
#include "../system/system.h"

#define FNAME "f_free.f"
lib_f_free()
{
   FILE *fp;
   StoreMakefile(FNAME,SYSTEM_LIBRARY);
   if(LIMIT_FILE == 1) return;
   fp = OpenFileToWrite( FNAME );
   F77("      subroutine f_free(cha , n , itype)\n");
   F77("*-------------------------------------------------------------------\n");
   F77("*  FEEL P2 System Subroutine f_free\n");
   F77("*-------------------------------------------------------------------\n");
   F77("*  Purpose: free allocated memory\n");
   F77("*-------------------------------------------------------------------\n");
   common_parameters(fp);
   COM;
   CommonBlock(fp);
   comment1(fp);
   F77("*\n");
   
   F77("      write(*,*) 'changement 2001/01/27 f_alloc modify'\n");
   F77("      write(*,*) 'f_free is not used, I suppose.'\n");
   F77("      stop 'f_free'\n");
   F77("*\n");


   F77("      nn = 0\n");
   F77("      if(itype.eq. 0) then\n");
   F77("	nn = n\n");
   F77("      endif\n");
   F77("      if(itype .eq. 1) then\n");
   F77("	nn = n * 2\n");
   F77("      endif\n");
   F77("      if(nn.eq.0) then\n");
   F77("	write(io_stderr,*) 'f_free: itype error'\n");
   F77("	stop 'f_free'\n");
   F77("      endif\n");
   F77("\n");
   F77("      np_work = np_work - nn\n");
   F77("      if(np_work .lt. 1) then\n");
   F77("	write(io_stderr,*) 'f_free <1 error for ',cha\n");
   F77("	stop 'f_free'\n");
   F77("      endif\n");
   F77("      return\n");
   F77("      end\n");
   F77("\n");
 CloseFile(fp);
 return;
}
