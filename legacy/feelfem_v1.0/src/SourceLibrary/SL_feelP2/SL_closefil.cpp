/*
 *  feelfem v1.0 NEC Corporation (C) 1999,2000,2001
 *                   Programmed  by  Hidehiro FUJIO
 *
 *  Filename : SL_closefil.cpp
 *  Date     : 2002/04/19 01:54
 *  Purpose  : Library module generator
 *
 */
#include "SL_feelP2.hpp"

static int come_yet_closefil = 0;


void SL_feelP2::SL_closefil(int makeFlag)
{
  char *sourceName;

  if(come_yet_closefil == 1)  return;
  else                  come_yet_closefil = 1;

  sourceName = GetSourceName("closefil");
  OpenSource(sourceName,makeFlag);

  // ORIGINAL SOURCE STARTS-----------------


  writeSource("      subroutine closefil(no)");
  writeSource("      parameter(MAX=100)");
  writeSource("      dimension iunits(MAX)");
  writeSource("      common /feel_dbg/ip,iunits");
  writeSource("      if(no .EQ. 0) then");
  writeSource("       ip = 0");
  writeSource("       return");
  writeSource("      endif");
  writeSource("      if(no .LT. 0) then");
  writeSource("      do 100 i=1,ip");
  writeSource("       close(unit=iunits(i))");
  writeSource("100   continue");
  writeSource("      return");
  writeSource("      endif");
  com();
  writeSource("      if(ip.EQ.MAX) stop 'too many close file to store'");
  writeSource("      ip=ip+1");
  writeSource("      iunits(ip) = no");
  writeSource("      return");
  writeSource("      end");
  writeSource("      subroutine doclosefil(no)");
  writeSource("      parameter(MAX=100)");
  writeSource("      dimension iunits(MAX)");
  writeSource("      common /feel_dbg/ip,iunits");
  writeSource("      do 100 i=1,ip");
  writeSource("       close(unit=iunits(i))");
  writeSource("100   continue");
  writeSource("      ip = 0");
  writeSource("      return");
  writeSource("      end");

  // ORIGINAL SOURCE END-------------------

  CloseSource();

  return;
}
