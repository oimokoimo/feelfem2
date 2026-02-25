/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : Solve_print.cpp
 *  Date     : 2002/02/05
 *  Modified : 
 *  
 *  Purpose  : check write routine
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

#include "Solve.hpp"

void Solve::print(std::ostream &ost)
{
  ost << "---------------------------------------" << std::endl;
  ost << "solve no = " << solveNo << std::endl;
  ost << "dconds   = " << dirichletConditions << std::endl;
  ost << "nconds   = " << neumannConditions << std::endl;

  ost << std::endl;


  ost << "VARS ";
  listIterator <Variable *>itr(solveVariablePtrLst);
  for(itr.init(); !itr ; ++itr) {
    ost <<" ";
    itr()->print(ost);
  }
  ost << "---------------------------------------" << std::endl;
  return;
}

