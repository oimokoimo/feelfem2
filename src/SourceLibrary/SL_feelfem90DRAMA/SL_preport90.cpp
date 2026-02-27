/*
 *  feelfem v1.0 NEC Corporation (C) 1999,2000,2001
 *                   Programmed  by  Hidehiro FUJIO
 *
 *  Filename : SL_preport90.cpp
 *  Date     : 2003/03/02 20:50
 *  Purpose  : Library module generator
 *
 *
 *  feelfem2 (modernized/ported)
 *  Copyright (C) 2025-2026 Hidehiro Fujio and contributors
 *  SPDX-License-Identifier: BSD-3-Clause
 *  Repository: https://github.com/oimokoimo/feelfem2
 *
 *
 *  Notes:
 *
 */
#include "SL_feelfem90DRAMA.hpp"

static int come_yet_preport90 = 0;


void SL_feelfem90DRAMA::SL_preport90(int makeFlag)
{
  const char *sourceName;

  if(come_yet_preport90 == 1)  return;
  else                  come_yet_preport90 = 1;

  sourceName = GetSourceName("preport90");
  OpenSource(sourceName,makeFlag);

  // ORIGINAL SOURCE STARTS-----------------


  writeSource("module preport90");
  com();
  com();
  writeSource("! F90,F95/MPI module to make a report");
  com();
  writeSource("double precision  , private :: t1,tim,tdiff,total,terapse");
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
  writeSource("subroutine preport90init( output_level )");
  writeSource("implicit none");
  writeSource("include 'mpif.h'");
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
  writeSource("  write(*,*) 'Argument for preport90init invalid. (set to 1)'");
  writeSource("  outputLevel = 1");
  writeSource("endif");
  com();
  writeSource("tim         = MPI_WTIME()");
  writeSource("tdiff       = MPI_WTIME()");
  writeSource("tdiff       = tdiff - tim");
  com();
  writeSource("tim         = MPI_WTIME()");
  writeSource("total       = 0.0d0");
  com();
  com();
  writeSource("if( outputLevel == 0 ) return");
  com();
  writeSource("open(iunit,file='preport.txt',action='write')");
  com();
  writeSource("  call drawline");
  writeSource("  call title");
  writeSource("  call drawline");
  com();
  com();
  writeSource("end subroutine preport90init");
  com();
  writeSource("!---------------------------------------");
  writeSource("subroutine calctime");
  writeSource("implicit none");
  writeSource("include 'mpif.h'");
  writeSource("t1      = MPI_WTIME()");
  writeSource("terapse = t1 - tim - tdiff");
  writeSource("total   = total+terapse");
  writeSource("tim     = t1");
  writeSource("end subroutine calctime");
  writeSource("!---------------------------------------");
  com();
  writeSource("subroutine preport(cha)");
  writeSource("character*(*) cha");
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
  writeSource("end subroutine preport");
  writeSource("subroutine preportmodule(cha)");
  writeSource("character*(*) cha");
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
  writeSource("end subroutine preportmodule");
  com();
  com();
  writeSource("subroutine preport90FundamentalVars(ndim,npmax,nedat,nnset,nnum,nip)");
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
  writeSource("end subroutine preport90FundamentalVars");
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
  writeSource("end module preport90");

  // ORIGINAL SOURCE END-------------------

  CloseSource();

  return;
}
