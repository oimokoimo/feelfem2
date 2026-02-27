/*
 *  feelfem v1.0 NEC Corporation (C) 1999,2000,2001
 *                   Programmed  by  Hidehiro FUJIO
 *
 *  Filename : SL_zero.cpp
 *  Date     : 2002/09/12 17:25
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
#include "SL_feelfem90.hpp"

static int come_yet_zero = 0;


void SL_feelfem90::SL_zero(int makeFlag)
{
  const char *sourceName;

  if(come_yet_zero == 1)  return;
  else                  come_yet_zero = 1;

  sourceName = GetSourceName("zero");
  OpenSource(sourceName,makeFlag);

  // ORIGINAL SOURCE STARTS-----------------


  writeSource("subroutine zeroi(dat,n)");
  writeSource("implicit none");
  writeSource("integer               :: n");
  writeSource("integer,dimension(n)  :: dat");
  com();
  writeSource("!auto");
  writeSource("integer               :: i");
  com();
  writeSource("do i=1,n");
  writeSource(" dat(i)=0");
  writeSource("end do");
  writeSource("end subroutine zeroi");
  writeSource("subroutine zerod(dat,n)");
  writeSource("use numeric");
  writeSource("implicit none");
  writeSource("integer                        :: n");
  writeSource("real(kind=REAL8),dimension(n)  :: dat");
  com();
  writeSource("!auto");
  writeSource("integer                        :: i");
  com();
  writeSource("do i=1,n");
  writeSource(" dat(i)=0.0");
  writeSource("end do");
  writeSource("end subroutine zerod");

  // ORIGINAL SOURCE END-------------------

  CloseSource();

  return;
}
