/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNsolveNeumann.cpp
 *  Date     : 2001/07/25
 *  Modified : 
 *  
 *  Purpose  : print functions ( for debug purpose )
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
 *  
 */

#include <iostream>

#include "SNsolveNeumann.hpp"

void SNsolveNeumannPairs::print(std::ostream &ost)
{
  listIterator <string> itrV(neumannArgumentLst);
  listIterator <Expression *> itrE(neumannExpressionLst);

  itrE.init();

  for(itrV.init();!itrV; ++itrV) {
    ost << itrV();
    ost << "=";
    itrE()->print(ost);
    
    ++itrE;
    if(!itrE) {
      ost << ",";
    }
  }

  return;
}

void SNsolveNeumann::print(std::ostream &ost) 
{
    ost << "Neumann ";
    nPairsPtr->print(ost);
    ost << " on ";
    nBoundaryLst->print(ost);
    return;
}
