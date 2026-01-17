/*
 *  feelfem v1.0 NEC Corporation (C) 1999,2000,2001
 *                   Programmed  by  Hidehiro FUJIO
 *
 *  Filename : SL_zero.cpp
 *  Date     : 2002/04/19 01:54
 *  Purpose  : Library module generator
 *
 */
#include "SL_feelP2.hpp"

static int come_yet_zero = 0;


void SL_feelP2::SL_zero(int makeFlag)
{
  char *sourceName;

  if(come_yet_zero == 1)  return;
  else                  come_yet_zero = 1;

  sourceName = GetSourceName("zero");
  OpenSource(sourceName,makeFlag);

  // ORIGINAL SOURCE STARTS-----------------


  writeSource("      subroutine zeroi(it,n)");
  writeSource("      dimension it(n)");
  writeSource("      do 100 i=1,n");
  writeSource(" 100  it(i) = 0");
  writeSource("      return");
  writeSource("      end");
  writeSource("      subroutine zerod(dt,n)");
  writeSource("      real * 8   dt");
  writeSource("      dimension dt(n)");
  writeSource("      do 100 i=1,n");
  writeSource(" 100  dt(i) = 0.0d0");
  writeSource("      return");
  writeSource("      end");

  // ORIGINAL SOURCE END-------------------

  CloseSource();

  return;
}
