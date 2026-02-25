/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SolveElement_print.cpp
 *  Date     : 2002/02/01
 *  Modified : 
 *  
 *  Purpose  : error check print
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

#include <iostream>

#include "SolveElement.hpp"
#include "ElementNodePattern.hpp"

void SolveElement::print(std::ostream &ost)
{
  ost << "-----------------------------------------------" << std::endl;
  ost << "[SolveElement]"<<std::endl;
  ost << "unknowns ";
  listIterator <Variable *> itr(unknownVarPtrLst);
  for(itr.init();!itr;++itr) {
    ost << "  ";
    itr()->print(ost);
  }
  ost << std::endl;
  
  listIterator <Variable *>itrV(varPtrLst);
  ost << "Used variables ";
  for(itrV.init(); !itrV ; ++itrV) {
    ost << " ";
    itrV()->print(ost);
  }
  ost << std::endl;
  

  ost << "ElementNodePattern (SolveElement)" << std::endl;
  seENPPtr->print(ost);

  ost << "-----------------------------------------------" << std::endl;

  return;
}
  
