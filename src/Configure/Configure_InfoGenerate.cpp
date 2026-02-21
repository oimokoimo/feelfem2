/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : Configure_InfoGenerate.cpp
 *  Date     : 2002/02/06
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

#include "feeldef.hpp"
#include "pairClass.hpp"
#include "Configure.hpp"


int Configure::GetSolverLibraryCodeFromName(string &pm,string &lib)
{
  StrStrIntPair *ssiPtr= new StrStrIntPair( pm, lib, DUMMY_CODE);

  //  cerr << "CHECK(PM_LIB) " << pmName << " VS " << libName << endl;

  int no;
  no = pglibPairLst.getPosition(ssiPtr);

  assert(no>0);

  StrStrIntPair *ssiPairPtr = pglibPairLst.getNthElement(no);

  return(ssiPairPtr->GetCode());
}

