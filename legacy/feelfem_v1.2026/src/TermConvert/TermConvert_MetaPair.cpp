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
 */

#include <assert.h>
#include <iostream.h>

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


 
