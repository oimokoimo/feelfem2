/*
 *  feelfem v1.0 NEC Corporation (C) 1999,2000,2001
 *                   Programmed  by  Hidehiro FUJIO
 *
 *  Filename : SL_ipd_nonode.cpp
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

static int come_yet_ipd_nonode = 0;


void SL_feelP2::SL_ipd_nonode(int makeFlag)
{
  const char *sourceName;

  if(come_yet_ipd_nonode == 1)  return;
  else                  come_yet_ipd_nonode = 1;

  sourceName = GetSourceName("ipd_nonode");
  OpenSource(sourceName,makeFlag);

  // ORIGINAL SOURCE STARTS-----------------


  writeSource("      subroutine ipd_nonode(iarg1,iarg2,iarg3,farg1,farg2)");
  writeSource("*-------------------------------------------------------------------");
  writeSource("*  FEEL P2 System Subroutine");
  writeSource("*-------------------------------------------------------------------");
  writeSource("*  Purpose: nodeless freedom");
  writeSource("*-------------------------------------------------------------------");
  writeSource("      stop 'Future Function(ipd_nonode)'");
  writeSource("      end");

  // ORIGINAL SOURCE END-------------------

  CloseSource();

  return;
}
