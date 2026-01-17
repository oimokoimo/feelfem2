/*
 *  feelfem v1.0 NEC Corporation (C) 1999,2000,2001
 *                   Programmed  by  Hidehiro FUJIO
 *
 *  Filename : SL_report90.cpp
 *  Date     : 2002/09/30 16:32
 *  Purpose  : Library module generator
 *
 */
#include "SL_aistpcp90.hpp"

static int come_yet_report90 = 0;


void SL_aistpcp90::SL_report90(int makeFlag)
{
  char *sourceName;

  if(come_yet_report90 == 1)  return;
  else                  come_yet_report90 = 1;

  sourceName = GetSourceName("report90");
  OpenSource(sourceName,makeFlag);

  // ORIGINAL SOURCE STARTS-----------------


  writeSource("module report90");
  com();
  com();
  writeSource("! F90,F95 module to make a report");
  writeSource("! use system_clock to count time");
  com();
  writeSource("double precision  , private :: t1,tim,total,terapse");
  writeSource("integer           , private :: clock_tim,clock_2,clock_3");
  writeSource("integer, private :: outputLevel");
  com();
  writeSource("integer, private,parameter :: iunit = 8");
  com();
  com();
  writeSource("private  title");
  writeSource("private  drawline");
  writeSource("private  calctime");
  com();
  writeSource("contains");
  com();
  writeSource("subroutine report90init( output_level )");
  writeSource("implicit none");
  com();
  writeSource("integer , intent(in)  :: output_level  ! output level");
  com();
  com();
  writeSource("outputLevel = output_level  ! 0 no output");
  writeSource("                            ! 1 minimum output");
  writeSource("                            ! 2 medium");
  writeSource("                            ! 3 maximum");
  com();
  writeSource("if(outputLevel < 0 .or. outputLevel > 3) then");
  writeSource("  write(*,*) 'Argument for report90init invalid. (set to 1)'");
  writeSource("  outputLevel = 1");
  writeSource("endif");
  com();
  writeSource("call system_clock(clock_tim,clock_2,clock_3)");
  writeSource("tim         = dble(clock_tim)/dble(clock_2)");
  writeSource("total       = 0.0d0");
  com();
  com();
  writeSource("if( outputLevel == 0 ) return");
  com();
  writeSource("open(iunit,file='report.txt',action='write')");
  com();
  writeSource("  call drawline");
  writeSource("  call title");
  writeSource("  call drawline");
  com();
  com();
  writeSource("end subroutine report90init");
  com();
  writeSource("!---------------------------------------");
  writeSource("subroutine calctime");
  writeSource("implicit none");
  writeSource("call system_clock(clock_tim,clock_2,clock_3)");
  writeSource("t1      = dble(clock_tim)/dble(clock_2)");
  writeSource("terapse = t1 - tim");
  writeSource("total   = total+terapse");
  writeSource("tim     = t1");
  writeSource("end subroutine calctime");
  writeSource("!---------------------------------------");
  com();
  writeSource("subroutine report(cha)");
  writeSource("character(len=*)   ::  cha");
  com();
  writeSource("call calctime");
  com();
  writeSource("if( outputLevel == 0 ) return");
  com();
  writeSource("write(iunit,'(f9.4,f9.4,2x,a)') total,terapse,cha");
  com();
  writeSource("if( outputLevel == 3 )then");
  writeSource("write(*,'(f9.4,f9.4,2x,a)') total,terapse,cha");
  writeSource("endif");
  com();
  writeSource("end subroutine report");
  writeSource("subroutine reportmodule(cha)");
  writeSource("character(len=*)   ::  cha");
  com();
  writeSource("call calctime");
  com();
  writeSource("if( outputLevel == 0 ) return");
  com();
  writeSource("write(iunit,'(f9.4,f9.4,2x,a)') total,terapse,cha");
  com();
  writeSource("if( outputLevel == 3 )then");
  writeSource("write(*,'(f9.4,f9.4,2x,a)') total,terapse,cha");
  writeSource("endif");
  com();
  writeSource("end subroutine reportmodule");
  com();
  com();
  writeSource("subroutine report90FundamentalVars(ndim,npmax,nedat,nnset,nnum,nip)");
  writeSource("integer, intent(in)  :: ndim,npmax,nedat,nnset,nnum,nip");
  com();
  writeSource("if(outputLevel == 0) return");
  com();
  com();
  writeSource("write(iunit,9000)");
  writeSource("write(iunit,9001) ndim");
  writeSource("write(iunit,9002) npmax");
  writeSource("write(iunit,9003) nedat");
  writeSource("write(iunit,9004) nnset");
  writeSource("write(iunit,9005) nnum");
  writeSource("write(iunit,9006) nip");
  writeSource("write(iunit,9000)");
  com();
  writeSource("if(outputLevel == 3 ) then");
  writeSource("  write(*,9000)");
  writeSource("  write(*,9001) ndim");
  writeSource("  write(*,9002) npmax");
  writeSource("  write(*,9003) nedat");
  writeSource("  write(*,9004) nnset");
  writeSource("  write(*,9005) nnum");
  writeSource("  write(*,9006) nip");
  writeSource("  write(*,9000)");
  writeSource("endif");
  writeSource("9000 format('                    ----------------------------------')");
  writeSource("9001 format('                    ','Space dimension          :',i8)");
  writeSource("9002 format('                    ','Total number of nodes    :',i8)");
  writeSource("9003 format('                    ','Number of EDAT data sets :',i8)");
  writeSource("9004 format('                    ','Number of NSET data sets :',i8)");
  writeSource("9005 format('                    ','Number of NNUM data sets :',i8)");
  writeSource("9006 format('                    ','Number of IP points      :',i8)");
  com();
  writeSource("end subroutine report90FundamentalVars");
  com();
  writeSource("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
  writeSource("! Frequently used routines");
  writeSource("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
  writeSource("subroutine drawline");
  writeSource("  if(outputLevel == 3) then");
  writeSource("    write(*,*)  '-------------------------------------------------------------'");
  writeSource("  endif");
  writeSource("  write(iunit,*)'-------------------------------------------------------------'");
  writeSource("end subroutine drawline");
  com();
  writeSource("subroutine title");
  writeSource("  if(outputLevel == 3) then");
  writeSource("    write(*,*)   ' feelfem90 Program'");
  writeSource("  endif");
  writeSource("  write(iunit,*) ' feelfem90 Program'");
  writeSource("end subroutine title");
  com();
  writeSource("!---------------------------------------------------------");
  writeSource("end module report90");

  // ORIGINAL SOURCE END-------------------

  CloseSource();

  return;
}
