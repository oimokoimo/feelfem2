/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNsolve_Infogenerate_Dirichlet.cpp
 *  Date     : 2002/02/05
 *  Modified : 
 *  
 *  Purpose  :
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
#include "SNname.hpp"

#include "Object.hpp"
#include "feelfuncs.hpp"

#include "Solve.hpp"
#include "Variable.hpp"
#include "Dirichlet.hpp"

void SNsolve::MakeDirichletDataPtr(Solve *solvePtr,int sno)
{
  int dcond_no;

  dcond_no = 0;

  listIterator <SNsolveDirichlet *>itrD(dcondLst);
  for(itrD.init(); !itrD ; ++itrD ) {
    Dirichlet *dPtr;

    dPtr = new Dirichlet;
    solvePtr -> AddDirichletDataPtr( dPtr );
    
    // set numbers
    dPtr -> SetSolveNo( sno );

    dcond_no++;
    dPtr -> SetDcondNo( dcond_no );

    // dirichlet variable
    dPtr -> SetDirichletVarPtr(itrD()->GetDirichletVariablePtr());

    // Add Variables in Dirichlet data
    itrD()-> AddVariablePtr_Dirichlet(dPtr);

    // set expression in Dirichlet class
    itrD()-> SetDataExprStr(dPtr);
    itrD()-> SetDataSimpleExprStr(dPtr);  // for Gid CND file
  }
  return;
}


