/*
   FEEL p2  MAKE FORTRAN LIBRARY   MSFortran_erapse_time
 */

#include <stdio.h>
#include "../feel_def/feel_def.h"
#include "../system/system.h"

#define FNAME "MSFortran_erapse_time.f"
lib_MSFortran_erapse_time()
{
   FILE *fp;
   StoreMakefile(FNAME,SYSTEM_LIBRARY);
   if(LIMIT_FILE == 1) return;
   fp = OpenFileToWrite( FNAME );
   F77("      subroutine timeinit\n");
   F77("*--------------------------------------------------------------------\n");
   F77("* FEEL Fortran77 System subroutine\n");
   F77("*  \n");
   F77("* Date    : 98/03/19\n");
   F77("* Purpose : measure cputime for Fortran PowerStation for MS Windows\n");
   F77("* \n");
   F77("*--------------------------------------------------------------------\n");
   F77("      real*8 tm_total\n");
   F77("      real*4 timebuf(2),dtime,ret\n");
   F77("*\n");
   F77("      common /fem_tim/tm_total,timebuf\n");
   F77("*\n");
   F77("      ret      = dtime(timebuf)\n");
   F77("      tm_total = 0.0d0\n");
   F77("*\n");
   F77("      return\n");
   F77("      end\n");
   F77("      subroutine cputime(total,erapse)\n");
   F77("      real*8 total,erapse\n");
   F77("      real*8 tm_total\n");
   F77("      real*4 timebuf(2),dtime,ret\n");
   F77("*\n");
   F77("      common /fem_tim/tm_total,timebuf\n");
   F77("*\n");
   F77("      ret      = dtime(timebuf)\n");
   F77("      erapse   = dble(ret)\n");
   F77("      tm_total = dble(ret)+tm_total\n");
   F77("      total    = tm_total\n");
   F77("*  	\n");
   F77("      return\n");
   F77("      end\n");
   F77("      real*8 function erapstime()\n");
   F77("      implicit real*8 (a-h,o-z)\n");
   F77("      call cputime(total,erapse)        \n");
   F77("      erapstime=total\n");
   F77("      return\n");
   F77("      end\n");
   F77("      subroutine getdate( date16 )\n");
   F77("      character*16 date16\n");
   F77("      character*8  DATE,DATESTR\n");
   F77("      character*8  CLOCK,CLOCKSTR\n");
   F77("*\n");
   F77("      DATESTR = DATE()\n");
   F77("      read(DATESTR,100) IMONTH,IDAY,IYEAR\n");
   F77("100   format(i2,1x,i2,1x,i2)\n");
   F77("      if(IYEAR .GT. 50) then\n");
   F77("        IYEAR = IYEAR+1900\n");
   F77("      else\n");
   F77("        IYEAR = IYEAR+2000\n");
   F77("      endif\n");
   F77("*\n");
   F77("      CLOCKSTR=CLOCK()\n");
   F77("      read(CLOCKSTR,200) IHOUR,IMINUTE\n");
   F77("200   format(i2,1x,i2)\n");
   F77("*\n");
   F77("      write(date16,300) IYEAR,IMONTH,IDAY,IHOUR,IMINUTE\n");
   F77("300   format(i4,'/',i2,'/',i2,' ',i2,':',i2)\n");
   F77("*\n");
   F77("      if(date16(6:6)   .EQ. ' ') date16(6:6)  ='0'\n");
   F77("      if(date16(9:9)   .EQ. ' ') date16(9:9)  ='0'\n");
   F77("      if(date16(12:12) .EQ. ' ') date16(12:12)='0'\n");
   F77("      if(date16(15:15) .EQ. ' ') date16(15:15)='0'\n");
   F77("*\n");
   F77("      return\n");
   F77("      end\n");
   F77("\n");
   F77("\n");
 CloseFile(fp);
 return;
}
