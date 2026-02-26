/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : Assign_print.cpp
 *  Date     : 2002/04/15 (BCN)
 *  Modified : 
 *   
 *  Purpose  : check write routines for Assign
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

#include "Assign.hpp"

void Assign::print(std::ostream &ost)
{
  ost << "Assign No." << assignNo <<"  ";
  ost << leftVarPtr->GetName();
  ost << " = ( ";
  listIterator <Variable *>itr(varPtrLst);
  for(itr.init(); !itr ; ++itr) {
    ost << itr()->GetName() << " ";
  }
  ost << ")  [" << expr << "]" << std::endl;

  return;
}
