/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : Neumann_print.cpp
 *  Date     : 2002/04/02
 *  Modified : 
 *  
 *  Purpose  : check out routine for Neumann
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
#include "Neumann.hpp"
#include "Variable.hpp"
#include "Expression.hpp"

void Neumann::print(std::ostream &ost)
{

  ost << "=====================";
  ost <<std::endl;

  ost << "Neumann CHECK solve No." <<solveNo << "  ncond No." <<ncondNo 
       << "  nbedtNo."<<nbedtNo <<std::endl;

  ost << "spaceDim="<<spaceDim << std::endl;

  ost << "NPG ="<<NPG << "  NDF="<<NDF << std::endl;

  ost << " x->"<<qxFlag<<"  y->"<<qyFlag << "  z->"<<qzFlag<<std::endl;
  ost << "nx->"<<nxFlag<<" ny->"<<nyFlag << " nz->"<<nzFlag<<std::endl;

  ost << " tangentialFlag =" << tangentialFlag << std::endl;

  ost << " unknowns=" << unknowns << "   ";
  listIterator <Variable *>itrU(unknownVarPtrLst);
  for(itrU.init();!itrU;++itrU) {
    ost << " " << itrU()->GetName() ;
  }
  ost << std::endl;


  ost << " test func lst : ";
  listIterator <string>itrT(testfuncSymbolLst);
  for(itrT.init(); !itrT ;++itrT ) {
    ost << " " << itrT() ;
  }
  ost << std::endl;


  ost << "Variables : ";
  listIterator<Variable *>itrV(varPtrLst);
  for(itrV.init(); !itrV; ++itrV) {
    ost << itrV()->GetName() << " ";
  }
  ost <<std::endl;

  ost << "=====================";
  ost <<std::endl;

  return;
}

    
