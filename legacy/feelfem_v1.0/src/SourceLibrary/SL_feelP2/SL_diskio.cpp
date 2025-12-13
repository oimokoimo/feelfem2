/*
 *  feelfem v1.0 NEC Corporation (C) 1999,2000,2001
 *                   Programmed  by  Hidehiro FUJIO
 *
 *  Filename : SL_diskio.cpp
 *  Date     : 2002/04/19 01:54
 *  Purpose  : Library module generator
 *
 */
#include "SL_feelP2.hpp"

static int come_yet_diskio = 0;


void SL_feelP2::SL_diskio(int makeFlag)
{
  char *sourceName;

  if(come_yet_diskio == 1)  return;
  else                  come_yet_diskio = 1;

  sourceName = GetSourceName("diskio");
  OpenSource(sourceName,makeFlag);

  // ORIGINAL SOURCE STARTS-----------------


  writeSource("      subroutine diskwrti(iunit,num,idat)");
  writeSource("*-------------------------------------------------------------------");
  writeSource("*  FEEL P2 System Subroutine");
  writeSource("*-------------------------------------------------------------------");
  writeSource("*  Purpose: 整数配列をファイルに書く");
  writeSource("*-------------------------------------------------------------------");
  writeSource("      dimension idat(num)");
  com();
  writeSource("      write(iunit) (idat(i),i=1,num)");
  writeSource("      return");
  writeSource("      end");
  writeSource("      subroutine diskwrtd(iunit,num,dat)");
  writeSource("*-------------------------------------------------------------------");
  writeSource("*  FEEL P2 System Subroutine");
  writeSource("*-------------------------------------------------------------------");
  writeSource("*  Purpose: 実数配列をファイルに書く");
  writeSource("*-------------------------------------------------------------------");
  writeSource("      implicit real*8 (a-h,o-z)");
  writeSource("      dimension dat(num)");
  com();
  writeSource("      write(iunit) (dat(i),i=1,num)");
  writeSource("      return");
  writeSource("      end");
  writeSource("      subroutine diskrdi(iunit,num,idat)");
  writeSource("*-------------------------------------------------------------------");
  writeSource("*  FEEL P2 System Subroutine");
  writeSource("*-------------------------------------------------------------------");
  writeSource("*  Purpose: 整数配列をファイルから読む");
  writeSource("*-------------------------------------------------------------------");
  writeSource("      dimension idat(num)");
  com();
  writeSource("      read(iunit) (idat(i),i=1,num)");
  writeSource("      return");
  writeSource("      end");
  writeSource("      subroutine diskrdd(iunit,num,dat)");
  writeSource("*-------------------------------------------------------------------");
  writeSource("*  FEEL P2 System Subroutine");
  writeSource("*-------------------------------------------------------------------");
  writeSource("*  Purpose: 実数配列をファイルから読む");
  writeSource("*-------------------------------------------------------------------");
  writeSource("      implicit real*8 (a-h,o-z)");
  writeSource("      dimension dat(num)");
  com();
  writeSource("      read(iunit) (dat(i),i=1,num)");
  writeSource("      return");
  writeSource("      end");

  // ORIGINAL SOURCE END-------------------

  CloseSource();

  return;
}
