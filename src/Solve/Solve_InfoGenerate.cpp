/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : Solve_InfoGenerate.cpp
 *  Date     : 2002/02/06
 *  Modified : 
 *  
 *  Purpose  : InfoGenerate for Solve class
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

#include "Dirichlet.hpp"
#include "Neumann.hpp"
#include "Solve.hpp"

void Solve::MakeNodeInformation()
{
  maxnodes = 0;
  listIterator <SolveElement *>itr(solveSolveElementPtrLst);
  for(itr.init(); !itr ; ++itr ) {
    int node = itr()->GetNode();
    if(node > maxnodes) maxnodes = node;
  }

  return;
}

void Solve::MakeVariablePtrLst(void)   // now called from SolveGenerator
{

  assert(makeVariablePtrLstComeyetFlag == 0);
  makeVariablePtrLstComeyetFlag = 1;

  listIterator <SolveElement *>itr(solveSolveElementPtrLst);
  for(itr.init(); !itr; ++itr) {

    /* Known and Unknown(in case of nonlinear) Varaibles */
    orderedPtrList <Variable *> varPtrLst = itr()->GetVariablePtrLst();
    listIterator <Variable *>itr2(varPtrLst);
    for(itr2.init(); !itr2; ++itr2) {
      AddVariablePtr( itr2() );
    }

    /* Unknown Variables */
    list <Variable *> unknownVarPtrLst 
      = itr()->GetUnknownVariablePtrLst();
    listIterator <Variable *>itr3(unknownVarPtrLst);
    for(itr3.init(); !itr3; ++itr3) {
      AddVariablePtr( itr3() );
    }
  }

  /* Dirichlet Data Variables */
  listIterator <Dirichlet *>ditr(solveDirichletPtrLst);
  for(ditr.init(); !ditr; ++ditr) {
    orderedPtrList <Variable *> varPtrLst = ditr()->GetVariablePtrLst();

    listIterator <Variable *>itr2(varPtrLst);
    for(itr2.init(); !itr2; ++itr2) {
      AddVariablePtr( itr2() );
    }
  }

  /* Neumann Data Variables */
  listIterator <Neumann *>nitr(solveNeumannPtrLst);
  for(nitr.init(); !nitr; ++nitr) {

    orderedPtrList <Variable *> varPtrLst = nitr()->GetVariablePtrLst();
    listIterator <Variable *>itr2(varPtrLst);
    for(itr2.init(); !itr2; ++itr2) {
      AddVariablePtr( itr2() );
    }
  }

  return;
}
