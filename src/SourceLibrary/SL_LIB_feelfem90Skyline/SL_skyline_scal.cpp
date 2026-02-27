/*
 *  feelfem v1.0 NEC Corporation (C) 1999,2000,2001
 *                   Programmed  by  Hidehiro FUJIO
 *
 *  Filename : SL_skyline_scal.cpp
 *  Date     : 2002/04/19 01:54
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
#include "SL_LIB_feelfem90Skyline.hpp"

static int come_yet_skyline_scal = 0;


void SL_LIB_feelfem90Skyline::SL_skyline_scal(int makeFlag)
{
  const char *sourceName;

  if(come_yet_skyline_scal == 1)  return;
  else                  come_yet_skyline_scal = 1;

  sourceName = GetSourceName("skyline_scal");
  OpenSource(sourceName,makeFlag);

  // ORIGINAL SOURCE STARTS-----------------


  writeSource("  double precision FUNCTION SCAL(X,Y,N)");
  com();
  writeSource("    implicit none");
  writeSource("!    double precision,dimension(*)         :: x,y");
  writeSource("    double precision x(*),y(*)");
  writeSource("    integer                               :: n");
  com();
  writeSource("    integer                               :: i");
  writeSource("    double precision                      :: zero");
  com();
  writeSource("    DATA ZERO/0.0D0/");
  writeSource("    !");
  writeSource("    SCAL = ZERO");
  writeSource("    DO I = 1,N");
  writeSource("       SCAL = SCAL + X( I ) * Y( I )");
  writeSource("    end do");
  writeSource("    !");
  writeSource("    RETURN");
  com();
  writeSource("  end function scal");
  com();

  // ORIGINAL SOURCE END-------------------

  CloseSource();

  return;
}
