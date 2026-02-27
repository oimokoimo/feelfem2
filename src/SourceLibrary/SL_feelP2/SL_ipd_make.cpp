/*
 *  feelfem v1.0 NEC Corporation (C) 1999,2000,2001
 *                   Programmed  by  Hidehiro FUJIO
 *
 *  Filename : SL_ipd_make.cpp
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

static int come_yet_ipd_make = 0;


void SL_feelP2::SL_ipd_make(int makeFlag)
{
  const char *sourceName;

  if(come_yet_ipd_make == 1)  return;
  else                  come_yet_ipd_make = 1;

  sourceName = GetSourceName("ipd_make");
  OpenSource(sourceName,makeFlag);

  // ORIGINAL SOURCE STARTS-----------------


  writeSource("      subroutine makeipd(ipf,ipd,npmax,neq)");
  writeSource("*-------------------------------------------------------------------");
  writeSource("*  FEEL P2 System Subroutine  MAKEIPD");
  writeSource("*-------------------------------------------------------------------");
  writeSource("*  Purpose: 節点自由度から、累積節点自由度配列を作成する");
  com();
  writeSource("*  Caution: IPF(*)は、節点毎自由度");
  com();
  writeSource("*           IPD(*)配列の意味は次の通り");
  writeSource("*           IPD(*)は各節点毎に値を持つ");
  writeSource("*           IPD(*) = 0 なる節点には 自由度が無い");
  writeSource("*           IPD(n) = K IPF(n) = 3 なら、節点番号 n には、");
  writeSource("*           方程式番号 K,K+1,K+2  の自由度が対応している");
  writeSource("*-------------------------------------------------------------------");
  writeSource("      dimension IPF(npmax),IPD(npmax)");
  com();
  writeSource("      neq = 0");
  com();
  writeSource("*     自由度がある最初の節点を探索");
  com();
  writeSource("      do 100 i=1,npmax");
  writeSource("       if(IPF(i) .ne. 0) then");
  writeSource("         istart = i");
  writeSource("         goto 200");
  writeSource("       endif");
  writeSource(" 100  continue");
  writeSource(" 150  stop 'makeipd error'");
  writeSource("*---");
  writeSource(" 200  continue");
  com();
  writeSource("      nowfree = IPF(istart)");
  writeSource("      IPD(istart) = 1");
  com();
  writeSource("      do 300 i=istart+1,npmax");
  writeSource("        if(IPF(i) .eq. 0) goto 300");
  com();
  writeSource("        IPD(i) = nowfree + 1");
  writeSource("        nowfree = nowfree + IPF(i)");
  writeSource(" 300  continue");
  com();
  writeSource("      neq = nowfree");
  com();
  writeSource("      return");
  writeSource("      end");

  // ORIGINAL SOURCE END-------------------

  CloseSource();

  return;
}
