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
 */

#include <iostream.h>

#include "SNsolveNeumann.hpp"

void SNsolveNeumannPairs::print(ostream &ost)
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

void SNsolveNeumann::print(ostream &ost) 
{
    ost << "Neumann ";
    nPairsPtr->print(ost);
    ost << " on ";
    nBoundaryLst->print(ost);
    return;
}
