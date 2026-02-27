/*
 *  feelfem v1.0 NEC Corporation (C) 1999,2000,2001
 *                   Programmed  by  Hidehiro FUJIO
 *
 *  Filename : SL_set.cpp
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
#include "SL_feelP2.hpp"

static int come_yet_set = 0;


void SL_feelP2::SL_set(int makeFlag)
{
  const char *sourceName;

  if(come_yet_set == 1)  return;
  else                  come_yet_set = 1;

  sourceName = GetSourceName("set");
  OpenSource(sourceName,makeFlag);

  // ORIGINAL SOURCE STARTS-----------------


  writeSource("      subroutine seti(it,num,n)");
  writeSource("      dimension it(n)");
  com();
  writeSource("      do 100 i=1,n");
  writeSource("        it(i) = num");
  writeSource(" 100  continue");
  writeSource("      return");
  writeSource("      end");
  writeSource("      subroutine setd(dt,dnum,n)");
  writeSource("      real*8 dt,dnum");
  writeSource("      dimension dt(n)");
  com();
  writeSource("      do 100 i=1,n");
  writeSource("        dt(i) = dnum");
  writeSource(" 100  continue");
  writeSource("      return");
  writeSource("      end");

  // ORIGINAL SOURCE END-------------------

  CloseSource();

  return;
}
