/*
 *  feelfem v1.0 NEC Corporation (C) 1999,2000,2001
 *                   Programmed  by  Hidehiro FUJIO
 *
 *  Filename : SL_wrtcrsfil.cpp
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
#include "SL_LIB_feelP2Achim.hpp"

static int come_yet_wrtcrsfil = 0;


void SL_LIB_feelP2Achim::SL_wrtcrsfil(int makeFlag)
{
  const char *sourceName;

  if(come_yet_wrtcrsfil == 1)  return;
  else                  come_yet_wrtcrsfil = 1;

  sourceName = GetSourceName("wrtcrsfil");
  OpenSource(sourceName,makeFlag);

  // ORIGINAL SOURCE STARTS-----------------


  writeSource("      subroutine wrtCRSfil(no,neq,ncof,maxnzpr,");
  writeSource("     $                     valmat,indrow,iptrcol,vfg,v)");
  writeSource("*----------------------------------------------------------------------");
  writeSource("*    no            : solve number");
  writeSource("*    neq           : total number of equations");
  writeSource("*    ncof          : total number of nonzero cofficient in matrix array");
  writeSource("*    maxnzpr       : maximum number of nonzero per row");
  writeSource("*    valmat(ncof)  : matrix");
  writeSource("*    indrow(ncof)  : column pointer");
  writeSource("*    iptrcol(neq+1): row starting pointer");
  writeSource("*    vfg           : right hand vector");
  writeSource("*    v             : initial guess and solution");
  writeSource("*----------------------------------------------------------------------");
  writeSource("      implicit real*8 (a-h,o-z)");
  com();
  writeSource("      dimension valmat(*)");
  writeSource("      dimension indrow(*)");
  writeSource("      dimension iptrcol(*)");
  writeSource("      dimension vfg(*)");
  writeSource("      dimension v(*)");
  com();
  writeSource("      character filname*11");
  com();
  writeSource("      write(filname,10) no");
  writeSource(" 10   format('solve',i1,'.crs')");
  com();
  writeSource("      call binopen(filname,10)");
  writeSource("*                       12345678901234567890");
  writeSource("      call binwritestr('crs matrix feelfem  ',20)");
  writeSource("      call binwriteint(neq)");
  writeSource("      call binwriteint(maxnzpr)");
  writeSource("      call binwriteints(iptrcol,neq+1)");
  writeSource("      call binwritedbls(valmat ,ncof )");
  writeSource("      call binwriteints(indrow ,ncof )");
  writeSource("      call binwritedbls(vfg    ,neq  )");
  writeSource("      call binwritedbls(v      ,neq  )");
  com();
  writeSource("      call binclose");
  com();
  writeSource("      return");
  writeSource("      end");
  com();
  com();
  com();

  // ORIGINAL SOURCE END-------------------

  CloseSource();

  return;
}
