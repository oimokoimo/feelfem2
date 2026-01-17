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
 */

#include <iostream.h>
#include "Neumann.hpp"
#include "Variable.hpp"
#include "Expression.hpp"

void Neumann::print(ostream &ost)
{

  ost << "=====================";
  ost <<endl;

  ost << "Neumann CHECK solve No." <<solveNo << "  ncond No." <<ncondNo 
       << "  nbedtNo."<<nbedtNo <<endl;

  ost << "spaceDim="<<spaceDim << endl;

  ost << "NPG ="<<NPG << "  NDF="<<NDF << endl;

  ost << " x->"<<qxFlag<<"  y->"<<qyFlag << "  z->"<<qzFlag<<endl;
  ost << "nx->"<<nxFlag<<" ny->"<<nyFlag << " nz->"<<nzFlag<<endl;

  ost << " tangentialFlag =" << tangentialFlag << endl;

  ost << " unknowns=" << unknowns << "   ";
  listIterator <Variable *>itrU(unknownVarPtrLst);
  for(itrU.init();!itrU;++itrU) {
    ost << " " << itrU()->GetName() ;
  }
  ost << endl;


  ost << " test func lst : ";
  listIterator <string>itrT(testfuncSymbolLst);
  for(itrT.init(); !itrT ;++itrT ) {
    ost << " " << itrT() ;
  }
  ost << endl;


  ost << "Variables : ";
  listIterator<Variable *>itrV(varPtrLst);
  for(itrV.init(); !itrV; ++itrV) {
    ost << itrV()->GetName() << " ";
  }
  ost <<endl;

  ost << "=====================";
  ost <<endl;

  return;
}

    
