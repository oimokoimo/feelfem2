/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : ElementNodePattern_print.cpp
 *  Date     : 2002/02/01
 *  Modified : 
 *  
 *  Purpose  : debug routine for ElementNodePattern
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
#include <cassert>

#include "ElementNodePattern.hpp"

void ElementNodePattern::print(std::ostream &ost)
{
  ost << "Element node pattern" << std::endl;
  ost << "FEM variable   " << numberOfFEMVariables << std::endl;
  ost << "VFEM variable  " << numberOfVFEMVariables << std::endl;
  ost << "EWISE variable " << numberOfEWISEVariables << std::endl;
  ost << "nodes = " << nodes << std::endl;
  ost << "totalFreedom = "<< totalFreedom << std::endl;
  ost << "ewiseFreedom = "<< ewiseFreedom << std::endl;
  
  ost << std::endl;


  listIterator <Node *>itr(nodeOrderedPtrLst);
  int no=0;
  for(itr.init(); !itr; ++itr ) {
    no++;
    ost << "[" << no << "] ";
    itr()->print(ost);
    ost << std::endl;
  }
  ost << "******\n";

  assert(ienp != 0 && iedp != 0);

  ost << "IENP ";
  for(int i=0;i<totalFreedom;i++) {
    if(i!=0) ost << ",";
    ost << *(ienp+i);
  }
  ost << std::endl;

  ost << "IEDP ";
  for(int i=0;i<totalFreedom;i++) {
    if(i!=0) ost << ",";
    ost << *(iedp+i);
  }
  ost << std::endl;
  
  ost << "--------------------------------------------------\n";
  
  return;
}
    

