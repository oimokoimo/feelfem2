/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNsolve.cpp
 *  Date     : 2001/03/05
 *  Modified : 
 *  
 *  Purpose  : solve statement parser
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

#include "SNsolve.hpp"
#include "SNsolveSolver.hpp"
#include "SNsolveParametric.hpp"
#include "SNsolveQuadrature.hpp"
#include "SNsolveNonlinear.hpp"

SNsolve::SNsolve( SNidentifierlist *iptr,              // unknown function list
		  SNidentifierlist *itptr,             // test function list
		  stack <SNunit *>&parseSolveStack)
  : SNunit("solve",SN_SOLVE) 
{
  // initialization
  
  unknownIdentifierList      = iptr;
  testFunctionIdentifierList = itptr;

  numberOfUnknowns  = 0;

  nonlinearFlag     = NO;

  solverName        = DEFAULT_STRING;  // change at SNsolve.CheckInit();
  quadratureMethod  = DEFAULT_STRING;  // 
  parametricName    = DEFAULT_STRING;

  weakEquations     = 0;

  dirichletConditions = 0;

  neumannConditions   = 0;

  // InfoGenerate flag
  infoGeneratePossibleFlag = YES;


  while(!parseSolveStack.isEmpty()) {
    SNunit *unitPtr;

    unitPtr = parseSolveStack.pop();

    switch( unitPtr->GetType() ) {
    case SN_SOLVESOLVER:
      solverName = ((SNsolveSolver *)unitPtr)->getName();
      break;

    case SN_SOLVEPARAMETRIC:
      parametricName = ((SNsolveParametric *)unitPtr)->getName();
      break;
      
    case SN_SOLVEQUADRATURE:
      quadratureMethod = ((SNsolveQuadrature *)unitPtr)->getName();
      break;

    case SN_SOLVENONLINEAR:
      nonlinearFlag   = YES;
      nonlinearMethod = ((SNsolveNonlinear *)unitPtr)->getName();
      break;

    case SN_SOLVEWEQ:
      weqLst.add( (SNsolveWeq *)unitPtr);         // because of stack, use add
      weakEquations++;
      break;

    case SN_SOLVEDIRICHLET:
      dcondLst.add( (SNsolveDirichlet *)unitPtr); // because of stack, use add
      dirichletConditions++;
      break;

    case SN_SOLVENEUMANN:
      ncondLst.add( (SNsolveNeumann *)unitPtr);   // because of stack, use add
      neumannConditions++;
      break;
			 
    default:
      std::cerr << "UNKNOWN code in solve parser\n";
    }
  }
  return;
}

void SNsolve::print(std::ostream &ost) 
{
  ost << "solve\n";
  ost << "        Unknown : ";
  unknownIdentifierList->print(ost);   ost << "\n";

  ost << "  Test function : ";
  testFunctionIdentifierList->print(ost);   ost << "\n";
  
  if(quadratureMethod != "default") {
    ost << "     Quadrature : " << quadratureMethod << "\n";
  }
  else {
    ost << "     Quadrature : " << "default" << "\n";
  }

  ost <<   " Solver Library : " << solverName << "\n";

  if(nonlinearFlag == YES) {
    ost <<   "      Nonlinear : " << nonlinearMethod << "\n";
  }

  // print weak forms
  listIterator<SNsolveWeq *>itr(weqLst);
  for(itr.init();!itr;++itr) {
    ost << "weq: ";
    itr()->print(ost);
    ost << std::endl;
  }

  // print dirichlet conditions
  listIterator<SNsolveDirichlet *>itrD(dcondLst);
  for(itrD.init();!itrD;++itrD) {
    itrD()->print(ost);
  }

  // print neumann conditions
  listIterator<SNsolveNeumann *>itrN(ncondLst);
  for(itrN.init();!itrN;++itrN) {
    itrN()->print(ost);
  }

  return;
}
