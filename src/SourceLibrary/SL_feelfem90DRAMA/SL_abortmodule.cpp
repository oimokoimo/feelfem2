/*
 *  feelfem v1.0 NEC Corporation (C) 1999,2000,2001
 *                   Programmed  by  Hidehiro FUJIO
 *
 *  Filename : SL_abortmodule.cpp
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

static int come_yet_abortmodule = 0;


void SL_feelfem90DRAMA::SL_abortmodule(int makeFlag)
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
  writeSource("subroutine abortexit(mypeid)");
  writeSource("implicit none");
  writeSource("include 'mpif.h'");
  com();
  writeSource("integer, intent(in) :: mypeid");
  writeSource("integer             :: ierror");
  com();
  writeSource("write(*,*) 'Error occured in PE id.',mypeid");
  com();
  writeSource("call MPI_ABORT(MPI_COMM_WORLD,-1,ierror)");
  com();
  writeSource("end subroutine abortexit");
  com();
  writeSource("!--------------------");
  writeSource("end module abortmodule");

  // ORIGINAL SOURCE END-------------------

  CloseSource();

  return;
}
