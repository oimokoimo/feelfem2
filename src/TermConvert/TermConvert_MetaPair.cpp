/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : TermConvert_MetaPair.cpp
 *  Date     : 2002/03/05
 *  Modified : 
 *  
 *  Purpose  : For eset type generator
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

#include <cassert>
#include <iostream>

#include "TermConvert.hpp"

void TermConvert::StoreMetaPair( const char *from, const char *to )
{
  char buf[38];
  
  string fromStr = from;
  
  assert(!metaPairSblStrLst.includes(fromStr));

  smblNo++;   // starts 1

  sprintf(buf,"_m%d",smblNo);
  
  storeConvertPair( from , buf );

  if(reverseTC == 0) {
    reverseTC = new TermConvert;
    assert(reverseTC != 0);
  }

  reverseTC->storeConvertPair(buf, to);

  return;
}
