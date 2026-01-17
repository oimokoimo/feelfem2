/*
 *  feelfem v1.0 NEC Corporation (C) 1999,2000,2001
 *                   Programmed  by  Hidehiro FUJIO
 *
 *  Filename : SL_get_inset.cpp
 *  Date     : 2002/04/19 01:54
 *  Purpose  : Library module generator
 *
 */
#include "SL_feelP2.hpp"

static int come_yet_get_inset = 0;


void SL_feelP2::SL_get_inset(int makeFlag)
{
  char *sourceName;

  if(come_yet_get_inset == 1)  return;
  else                  come_yet_get_inset = 1;

  sourceName = GetSourceName("get_inset");
  OpenSource(sourceName,makeFlag);

  // ORIGINAL SOURCE STARTS-----------------


  writeSource("      subroutine get_inset(iunit,inset,nodes,np)");
  writeSource("*-------------------------------------------------------------------");
  writeSource("*  FEEL P2 System Subroutine");
  writeSource("*-------------------------------------------------------------------");
  writeSource("*  Purpose: read insetrm  array");
  com();
  writeSource("*  Caution:");
  com();
  writeSource("*-------------------------------------------------------------------");
  writeSource("      dimension inset(np,nodes)");
  com();
  writeSource("      rewind(iunit)");
  com();
  writeSource("      read(iunit) n1,n2");
  com();
  writeSource("      if(n1 .ne. nodes .or. n2 .ne. np) stop 'get_inset mismatch'");
  com();
  writeSource("      read(iunit) ((inset(i,j),i=1,np),j=1,nodes)");
  com();
  writeSource("      return");
  writeSource("      end");
  com();

  // ORIGINAL SOURCE END-------------------

  CloseSource();

  return;
}
