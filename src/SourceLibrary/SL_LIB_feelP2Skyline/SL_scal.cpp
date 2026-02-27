/*
 *  feelfem v1.0 NEC Corporation (C) 1999,2000,2001
 *                   Programmed  by  Hidehiro FUJIO
 *
 *  Filename : SL_scal.cpp
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
#include "SL_LIB_feelP2Skyline.hpp"

static int come_yet_scal = 0;


void SL_LIB_feelP2Skyline::SL_scal(int makeFlag)
{
  const char *sourceName;

  if(come_yet_scal == 1)  return;
  else                  come_yet_scal = 1;

  sourceName = GetSourceName("scal");
  OpenSource(sourceName,makeFlag);

  // ORIGINAL SOURCE STARTS-----------------


  writeSource("C*************************************************************");
  com();
  writeSource("C     FUNCTION SCAL(X,Y,N)             scal.f");
  com();
  writeSource("C**************************************************************");
  writeSource("      REAL * 8 FUNCTION SCAL(X,Y,N)");
  com();
  writeSource("      IMPLICIT REAL*8(A-H,O-Z)");
  com();
  writeSource("      DIMENSION X(1),Y(1)");
  com();
  writeSource("      DATA ZERO/0.0D0/");
  com();
  writeSource("      SCAL = ZERO");
  writeSource("      DO 10 I = 1,N");
  writeSource("         SCAL = SCAL + X( I ) * Y( I )");
  writeSource(" 10   CONTINUE");
  com();
  writeSource("      RETURN");
  writeSource("      END");

  // ORIGINAL SOURCE END-------------------

  CloseSource();

  return;
}
