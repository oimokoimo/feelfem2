/*
 *  feelfem v1.0 NEC Corporation (C) 1999,2000,2001
 *                   Programmed  by  Hidehiro FUJIO
 *
 *  Filename : SL_ipf_nfree.cpp
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

static int come_yet_ipf_nfree = 0;


void SL_feelP2::SL_ipf_nfree(int makeFlag)
{
  const char *sourceName;

  if(come_yet_ipf_nfree == 1)  return;
  else                  come_yet_ipf_nfree = 1;

  sourceName = GetSourceName("ipf_nfree");
  OpenSource(sourceName,makeFlag);

  // ORIGINAL SOURCE STARTS-----------------


  writeSource("      subroutine ipf_nfree(neelem,nenode,IPF,ielem,nenfre)");
  writeSource("*-------------------------------------------------------------------");
  writeSource("*  FEEL P2 System Subroutine");
  writeSource("*-------------------------------------------------------------------");
  writeSource("*   Purpose: 配列IPFに節点毎自由度を設定する。");
  writeSource("*            IPF(*)は0クリアされていること");
  com();
  writeSource("* Variables: neelem  要素数");
  writeSource("*            nenode  要素内節点数");
  writeSource("*            IPF     節点毎自由度配列");
  writeSource("*            ielem   要素節点対応配列");
  writeSource("*            nenfre  要素局所節点毎自由度");
  com();
  writeSource("*-------------------------------------------------------------------");
  writeSource("      dimension IPF(*),ielem(nenode,neelem),nenfre(*)");
  writeSource("*---");
  writeSource("      do 100 i=1,neelem");
  writeSource("         do 200 j=1,nenode");
  com();
  writeSource("            IPF(ielem(j,i)) = nenfre(j)");
  com();
  writeSource(" 200     continue");
  writeSource(" 100  continue");
  writeSource("*---");
  writeSource("      return");
  writeSource("*---");
  writeSource("      end");
  com();

  // ORIGINAL SOURCE END-------------------

  CloseSource();

  return;
}
