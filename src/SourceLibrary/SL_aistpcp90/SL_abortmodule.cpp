/*
 *  feelfem v1.0 NEC Corporation (C) 1999,2000,2001
 *                   Programmed  by  Hidehiro FUJIO
 *
 *  Filename : SL_abortmodule.cpp
 *  Date     : 2002/09/30 16:32
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
#include "SL_aistpcp90.hpp"

static int come_yet_abortmodule = 0;


void SL_aistpcp90::SL_abortmodule(int makeFlag)
{
  const char *sourceName;

  if(come_yet_abortmodule == 1)  return;
  else                  come_yet_abortmodule = 1;

  sourceName = GetSourceName("abortmodule");
  OpenSource(sourceName,makeFlag);

  // ORIGINAL SOURCE STARTS-----------------


  writeSource("module abortmodule");
  com();
  writeSource("contains");
  com();
  writeSource("subroutine abortexit(cha)");
  writeSource("implicit none");
  com();
  writeSource("character(len=*)   :: cha");
  com();
  writeSource("write(*,*) cha");
  com();
  writeSource("stop");
  com();
  writeSource("end subroutine abortexit");
  com();
  writeSource("!--------------------");
  writeSource("end module abortmodule");

  // ORIGINAL SOURCE END-------------------

  CloseSource();

  return;
}
