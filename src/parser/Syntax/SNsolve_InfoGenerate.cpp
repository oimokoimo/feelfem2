/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNsolve_InfoGenerate.cpp
 *  Date     : 2001/09/07
 *  Modified : 
 *  
 *  Purpose  : Solve class generation from SNsolve class
 *  
 *             Called from info/scheme_info_generate.cpp
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

#include "SNsolve.hpp"
#include "SNname.hpp"

#include "Object.hpp"
#include "Configure.hpp"
#include "feelfuncs.hpp"

#include "Solve.hpp"
#include "Variable.hpp"

int SNsolve::InfoGenerate(void)
{
  if(infoGeneratePossibleFlag == NO) return(0);


  solvePtr = new Solve;   // solveNo is assigned in Constructor

  feelfemobj.StoreSolve(solvePtr);

  solvePtr->SetSpaceDim( feelfemobj.GetSpaceDimension() );

  solvePtr->
    SetLibraryType
    (feelfemconf.GetSolverLibraryCodeFromName(programModelNameCopy,
					      solverName));

  solvePtr->
    SetProgramModelType
    (feelfemconf.GetProgramModelCodeFromName(programModelNameCopy));

  MakeSolveElement(solvePtr,solvePtr->GetSolveNo(), 1 );   // SUBSOLVE
  MakeDirichletDataPtr(solvePtr,solvePtr->GetSolveNo());   
  MakeNeumannDataPtr(solvePtr,solvePtr->GetSolveNo());     // spacedim is used

  solvePtr->MakeVariablePtrLst();

  solvePtr->MakeNodeInformation();  // maxnodes, etc.

  return(0);
}

