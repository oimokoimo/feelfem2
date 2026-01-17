/*
   FEEL p2  MAKE FORTRAN LIBRARY   scal
 */

#include <stdio.h>
#include "../feel_def/feel_def.h"
#include "../system/system.h"

#define FNAME "scal.f"
lib_scal()
{
   FILE *fp;
   StoreMakefile(FNAME,SYSTEM_LIBRARY);
   if(LIMIT_FILE == 1) return;
   fp = OpenFileToWrite( FNAME );
   F77("C*************************************************************\n");
   F77("C\n");
   F77("C     FUNCTION SCAL(X,Y,N)             scal.f\n");
   F77("C\n");
   F77("C**************************************************************\n");
   F77("      REAL * 8 FUNCTION SCAL(X,Y,N)\n");
   F77("C\n");
   F77("      IMPLICIT REAL*8(A-H,O-Z)\n");
   F77("C\n");
   F77("      DIMENSION X(1),Y(1)\n");
   F77("C\n");
   F77("      DATA ZERO/0.0D0/\n");
   F77("C\n");
   F77("      SCAL = ZERO\n");
   F77("      DO 10 I = 1,N\n");
   F77("         SCAL = SCAL + X( I ) * Y( I )\n");
   F77(" 10   CONTINUE\n");
   F77("C\n");
   F77("      RETURN\n");
   F77("      END\n");
 CloseFile(fp);
 return;
}
