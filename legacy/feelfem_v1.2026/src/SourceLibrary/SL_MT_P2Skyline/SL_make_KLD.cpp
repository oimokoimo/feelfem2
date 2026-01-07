/*
 *  feelfem v1.0 NEC Corporation (C) 1999,2000,2001
 *                   Programmed  by  Hidehiro FUJIO
 *
 *  Filename : SL_make_KLD.cpp
 *  Date     : 2002/04/19 01:54
 *  Purpose  : Library module generator
 *
 */
#include "SL_MT_P2Skyline.hpp"

static int come_yet_make_KLD = 0;


void SL_MT_P2Skyline::SL_make_KLD(int makeFlag)
{
  char *sourceName;

  if(come_yet_make_KLD == 1)  return;
  else                  come_yet_make_KLD = 1;

  sourceName = GetSourceName("make_KLD");
  OpenSource(sourceName,makeFlag);

  // ORIGINAL SOURCE STARTS-----------------


  writeSource("      subroutine make_KLD(KH,KLD,neq,ncof)");
  writeSource("*-------------------------------------------------------------------");
  writeSource("*  FEEL P2 System Subroutine  make_KLD");
  writeSource("*-------------------------------------------------------------------");
  writeSource("*  Purpose: スカイラインの高さを持つ配列KHより格納情報配列KLDを作成");
  com();
  writeSource("*  Caution: book p.302 参照");
  com();
  writeSource("*  KH    列の高さ");
  writeSource("*  KLD   スカイライン情報配列");
  writeSource("*  neq   方程式の本数");
  writeSource("*  ncof  係数マトリックスの為の大きさ(上、下各三角形のもの)");
  writeSource("*-------------------------------------------------------------------");
  writeSource("      dimension KH(*),KLD(*)");
  writeSource("*---");
  writeSource("      KLD(1) = 1");
  writeSource("      KLD(2) = 1");
  writeSource("*---");
  writeSource("      do 100 i = 3,neq+1");
  writeSource("         KLD(i) = KLD(i-1) + KH(i-1)");
  writeSource(" 100  continue");
  writeSource("*---");
  writeSource("      ncof = KLD(neq + 1) - 1");
  writeSource("*---");
  writeSource("      return");
  writeSource("      end");

  // ORIGINAL SOURCE END-------------------

  CloseSource();

  return;
}
