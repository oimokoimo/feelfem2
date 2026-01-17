/*
 *  feelfem v1.0 NEC Corporation (C) 1999,2000,2001
 *                   Programmed  by  Hidehiro FUJIO
 *
 *  Filename : SL_abortmodule.cpp
 *  Date     : 2002/09/12 17:25
 *  Purpose  : Library module generator
 *
 */
#include "SL_feelfem90.hpp"

static int come_yet_abortmodule = 0;


void SL_feelfem90::SL_abortmodule(int makeFlag)
{
  char *sourceName;

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
