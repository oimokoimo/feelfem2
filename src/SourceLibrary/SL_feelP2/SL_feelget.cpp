/*
 *  feelfem v1.0 NEC Corporation (C) 1999,2000,2001
 *                   Programmed  by  Hidehiro FUJIO
 *
 *  Filename : SL_feelget.cpp
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

static int come_yet_feelget = 0;


void SL_feelP2::SL_feelget(int makeFlag)
{
  const char *sourceName;

  if(come_yet_feelget == 1)  return;
  else                  come_yet_feelget = 1;

  sourceName = GetSourceName("feelget");
  OpenSource(sourceName,makeFlag);

  // ORIGINAL SOURCE STARTS-----------------


  writeSource("      function i_feelget(idat,n)");
  writeSource("      dimension idat(*)");
  writeSource("      i_feelget=idat(n)");
  writeSource("      return");
  writeSource("      end");
  writeSource("      function inp_feelget(feel,np,n)");
  writeSource("      integer*4 feel(*)");
  writeSource("      inp_feelget=feel(np+n-1)");
  writeSource("      return");
  writeSource("      end");
  writeSource("      real *8 function d_feelget(ddat,n)");
  writeSource("      real*8 ddat(*)");
  writeSource("      d_feelget=ddat(n)");
  writeSource("      return");
  writeSource("      end");
  writeSource("      subroutine feelset_npi(feel,np,i,num)");
  writeSource("      integer*4 feel(*)");
  writeSource("      feel(np+i-1) = num");
  writeSource("      return");
  writeSource("      end");
  writeSource("      subroutine feelset_npd(feel,np,i,dat)");
  writeSource("      real*8 dat");
  writeSource("      real*4 feel(*)");
  writeSource("      call subfeelset_npd(feel(np),i,dat)");
  writeSource("      return");
  writeSource("      end");
  writeSource("      subroutine subfeelset_npd(dbuf,i,dat)");
  writeSource("      real*8 dbuf(*),dat");
  writeSource("      dbuf(i) = dat");
  writeSource("      return");
  writeSource("      end");
  com();

  // ORIGINAL SOURCE END-------------------

  CloseSource();

  return;
}
