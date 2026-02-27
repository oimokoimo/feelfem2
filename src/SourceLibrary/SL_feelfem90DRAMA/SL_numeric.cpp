/*
 *  feelfem v1.0 NEC Corporation (C) 1999,2000,2001
 *                   Programmed  by  Hidehiro FUJIO
 *
 *  Filename : SL_numeric.cpp
 *  Date     : 2003/03/02 20:50
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
#include "SL_feelfem90DRAMA.hpp"

static int come_yet_numeric = 0;


void SL_feelfem90DRAMA::SL_numeric(int makeFlag)
{
  const char *sourceName;

  if(come_yet_numeric == 1)  return;
  else                  come_yet_numeric = 1;

  sourceName = GetSourceName("numeric");
  OpenSource(sourceName,makeFlag);

  // ORIGINAL SOURCE STARTS-----------------


  writeSource("module numeric");
  com();
  writeSource("integer, parameter :: INT4          = selected_int_kind(9)  ! INTEGER*4");
  writeSource("integer, parameter :: REAL8         = kind(1.0d0)           ! REAL   *8");
  writeSource("integer, parameter :: Oui           = 1");
  writeSource("integer, parameter :: Non           = 0");
  writeSource("integer, parameter :: NodeError     = -1");
  writeSource("integer, parameter :: already       = 1");
  writeSource("integer, parameter :: notYet        = 0");
  writeSource("integer, parameter :: Nur_One_Etype = -999            ! for enptr(2,*)");
  writeSource("integer, parameter :: EndOfEnptr    = -9999           ! for enptr(2,nelem+1)");
  com();
  writeSource("end module numeric");

  // ORIGINAL SOURCE END-------------------

  CloseSource();

  return;
}
