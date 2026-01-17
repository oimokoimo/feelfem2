/*
 *  feelfem v1.0 NEC Corporation (C) 1999,2000,2001
 *                   Programmed  by  Hidehiro FUJIO
 *
 *  Filename : SL_get_ielem.cpp
 *  Date     : 2002/04/19 01:54
 *  Purpose  : Library module generator
 *
 */
#include "SL_feelP2.hpp"

static int come_yet_get_ielem = 0;


void SL_feelP2::SL_get_ielem(int makeFlag)
{
  char *sourceName;

  if(come_yet_get_ielem == 1)  return;
  else                  come_yet_get_ielem = 1;

  sourceName = GetSourceName("get_ielem");
  OpenSource(sourceName,makeFlag);

  // ORIGINAL SOURCE STARTS-----------------


  writeSource("      subroutine get_ielem(iunit,ielem,matno,neelem,nenode)");
  writeSource("*-------------------------------------------------------------------");
  writeSource("*  FEEL P2 System Subroutine");
  writeSource("*-------------------------------------------------------------------");
  writeSource("*  Purpose: read ielem,matno array");
  com();
  writeSource("*  Caution:");
  com();
  writeSource("*-------------------------------------------------------------------");
  writeSource("      dimension ielem(nenode,neelem)");
  writeSource("      dimension matno(neelem)");
  com();
  writeSource("      rewind(iunit)");
  com();
  writeSource("      read(iunit) ne,np");
  com();
  writeSource("      if(ne .ne. neelem .or. np.ne. nenode) stop 'get_ielem mismatch'");
  com();
  writeSource("      read(iunit) ((ielem(i,j),i=1,nenode),j=1,neelem)");
  writeSource("      read(iunit) (matno(i),i=1,neelem)");
  com();
  writeSource("      return");
  writeSource("      end");
  com();

  // ORIGINAL SOURCE END-------------------

  CloseSource();

  return;
}
