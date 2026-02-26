/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : discretizeSolve.cpp
 *  Date     : 2001/07/27
 *  Modified : 2002/03/28  (Add boundary part)
 *  
 *  Purpose  : Make mathematical components for Solve families
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

#include "feelfuncs.hpp"

#include "list.hpp"
#include "parseExternals.hpp"

#include "../parser/Syntax/SNunit.hpp"
#include "../parser/Syntax/SNsolve.hpp"
//#include "../parser/Syntax/SNprogramModel.hpp"

#include "Solve.hpp"
#include "SolveElement.hpp"
#include "Neumann.hpp"


void discretizeSolve(SNsolve *snSolvePtr)
{
  // make solve   (in SolveElement_discretize.cpp)
  Solve *solvePtr     = snSolvePtr->GetSolvePtr();



  //  cerr << "discretizeSolve check write\n";
  //  solvePtr->print(cerr);
  //  sePtr->print(cerr);

  // for Regional
  SolveElement *sePtr = solvePtr->GetIthSolveElementPtr(0);
  sePtr->ApplyGalerkinMethod();  //
  sePtr->GenerateEcalInfo();     //
  sePtr->GenerateEsetInfo();     //

  // for Boundary (SolveElement_discretize.cpp)
  for(int i=0; i<solvePtr->GetNconds(); i++) {
    Neumann *nPtr = solvePtr->GetIthNeumannDataPtr(i);
    
    nPtr->ApplyGalerkinMethod();

    nPtr->GenerateEcalInfo();       // Neumann_discretize.cpp
    nPtr->GenerateEsetInfo();

    nPtr->discretizeInfoGenerate();  // in Neumann_InfoGenerate.cpp
  }
  return;
}
