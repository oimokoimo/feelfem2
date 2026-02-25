/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : TermConvert.cpp
 *  Date     : 2002/01/11
 *  Modified : 
 *  
 *  Purpose  : 
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

#include "TermConvert.hpp"

TermConvert::TermConvert(void)
{
  // initialization in constructor

  // list 
  numberOfItems = 0;

  // Element function related initialization
  elementTypes = 0;

  startingSblNo = 1;    // implementation place is moved from 
                        // Galerkin_discretize to TermConvert

  reverseTC    = 0;     // reverse converter

  smblNo       = 0;     // used for MetaPair group (020305)

  // Normal component for boundary integrand (020403)
  nxFlag = NO;
  nyFlag = NO;
  nzFlag = NO;

  return;
}

TermConvert::~TermConvert(void)
{
  // feelfemTEMP   delete StrStr memory.....
  if(reverseTC != 0) {
    reverseTC->~TermConvert();   // delete reverse pointer
  }

  ssPairPtrLst.deleteAllPointedValues();
  metaPairSblStrLst.deleteAllValues();

  // string strlst...
  return;
}

void TermConvert::storeConvertPair(const char *fromStr,const char *toStr)
{
  StrStrPair *sspPtr = new StrStrPair(fromStr,toStr);

  if(ssPairPtrLst.includes(sspPtr)) {
	  std::cerr << "Already defined... " << fromStr << "\n";
    assert(1==0);
  }

  ssPairPtrLst.add(sspPtr);

  //  cerr << "TC  " << fromStr << " ==> " << toStr << endl;
 
  return;
}

void TermConvert::replaceConvertPair(const char *fromStr,const char *toStr)

  // If exists replace the second.
  // If not exists create
{
  StrStrPair *sspPtr = new StrStrPair(fromStr,toStr);

  if(!ssPairPtrLst.includes(sspPtr)) {
    
    // if not exist, create
    ssPairPtrLst.add(sspPtr);
    return;
  }

  // if exist, replace
  int no = ssPairPtrLst.getPosition(sspPtr);
  sspPtr->~StrStrPair();  // delete

  sspPtr = ssPairPtrLst.getNthElement(no);

  sspPtr->SetSecond( toStr );

  return;
}


void TermConvert::StoreVariableList( Variable *vPtr)
{
  if(!varPtrLst.includes(vPtr)) {    // this is for making reverse term convert
    varPtrLst.addlast(vPtr);
    return;
  }

  std::cerr << "Duplicate StoreVariableList in TermConvert\n";
  assert(1==0);
}

