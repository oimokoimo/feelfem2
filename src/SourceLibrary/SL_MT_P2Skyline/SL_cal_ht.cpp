/*
 *  feelfem v1.0 NEC Corporation (C) 1999,2000,2001
 *                   Programmed  by  Hidehiro FUJIO
 *
 *  Filename : SL_cal_ht.cpp
 *  Date     : 2002/04/19 01:54
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
#include "SL_MT_P2Skyline.hpp"

static int come_yet_cal_ht = 0;


void SL_MT_P2Skyline::SL_cal_ht(int makeFlag)
{
  const char *sourceName;

  if(come_yet_cal_ht == 1)  return;
  else                  come_yet_cal_ht = 1;

  sourceName = GetSourceName("cal_ht");
  OpenSource(sourceName,makeFlag);

  // ORIGINAL SOURCE STARTS-----------------


  writeSource("      subroutine cal_ht_a(ielem,neelem,nenode,KHa,npmax)");
  writeSource("*---------------------------------------------------------------------");
  writeSource("*  FEEL P2 System Subroutine");
  writeSource("*---------------------------------------------------------------------");
  writeSource("*  Purpose: スカイライン行列の列の高さを計算する補助プログラム");
  writeSource("*           要素内の最小節点番号を探し出す");
  com();
  writeSource("*        KHaは、各節点における接続最小節点番号");
  com();
  writeSource("*  注意: KHaは、0クリアされているはず");
  com();
  writeSource("*---------------------------------------------------------------------");
  writeSource("      dimension ielem(nenode,neelem),KHa(*)");
  writeSource("*---");
  writeSource("      do 10 i=1,npmax");
  writeSource("         KHa(i) = npmax + 1");
  writeSource(" 10   continue");
  writeSource("*---");
  writeSource("      do 100 i=1,neelem");
  com();
  writeSource("         ip_min = ielem(1,i)");
  com();
  writeSource("*---  各要素内の最小節点番号を求める");
  writeSource("         do 120 j=2,nenode");
  writeSource("            if(ip_min .gt. ielem(j,i)) ip_min = ielem(j,i)");
  writeSource(" 120     continue");
  com();
  writeSource("         do 130 j=1,nenode");
  writeSource("            if(KHa(ielem(j,i)) .gt. ip_min) KHa(ielem(j,i)) = ip_min");
  writeSource(" 130     continue");
  com();
  writeSource(" 100  continue");
  com();
  writeSource("c      do 200 j=1,468");
  writeSource("c       write(*,*) 'KHa(',j,')= ',kha(j)");
  writeSource("c 200  continue");
  writeSource("*---");
  writeSource("      return");
  writeSource("      end");
  writeSource("      subroutine cal_ht(KHa,KH,IPF,IPD,npmax,neq)");
  writeSource("*---------------------------------------------------------------------");
  writeSource("*  FEEL P2 System Subroutine");
  writeSource("*---------------------------------------------------------------------");
  writeSource("*  Purpose: スカイライン行列の列の高さを計算するプログラム");
  com();
  writeSource("*  注意: 配列KHaの0は、未使用節点の意味");
  com();
  writeSource("*  変数: KHa(npmax)     各節点に関連する最小節点番号");
  writeSource("*        KH (neq)       スカイライン行列の列の高さ、対角のみの場合の0から始める");
  writeSource("*        IPF(npmax)     節点毎自由度");
  writeSource("*        IPD(npmax)     累積節点自由度");
  writeSource("*        npmax      入  総節点数");
  writeSource("*        neq        入  方程式の本数(連立一次方程式の連立の数)");
  writeSource("*---------------------------------------------------------------------");
  writeSource("      dimension KHa(npmax),KH(neq),IPF(npmax),IPD(npmax)");
  writeSource("*---");
  writeSource("      do 100 i=1,npmax");
  com();
  writeSource("         if(IPF(i) .eq. 0) goto 100");
  com();
  writeSource("* min_np は節点 i における最小 関連方程式番号");
  com();
  writeSource("         min_np  = IPD( KHa(i) )");
  writeSource("         ip_base = IPD( i )");
  writeSource("*---");
  writeSource("         do 200 j=1,IPF(i)");
  writeSource("            KH( ip_base + j - 1) = min_np");
  writeSource(" 200     continue");
  writeSource("*---");
  writeSource(" 100  continue");
  writeSource("*---");
  writeSource("      do 300 i=1,neq");
  writeSource("         KH(i) = i - KH(i)");
  writeSource("C         write(*,*) 'KH(',i,') = ',kh(i)");
  writeSource(" 300  continue");
  writeSource("      return");
  writeSource("      end");
  com();

  // ORIGINAL SOURCE END-------------------

  CloseSource();

  return;
}
