/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SolveNormalLinearProblem.cpp
 *  Date     : 1999/11/09
 *  Modified : 1999/11/09
 *  
 *  Purpose  : Normal linear problem Solve routine generator
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

#include "SolveScheme.hpp"

void SolveScheme::NormalLinearProblem( Solve *solvePtr )
{

  ////////////////////////////////

  SolveRoutineInitialize   (solvePtr);

  SolveRoutineHeader       (solvePtr);   // Language dependent routine header
                                      // Complete calling sequence from main

  SolveParameters          (solvePtr);   // Problem dependent static parameters

  SolveVariableDefinitions (solvePtr);   // Solve Auto variables

  SolveInitializer         (solvePtr);   // Data statements, parameter initializer
  
  SolveDegreeOfFreedom     (solvePtr);

  SolveAssemblyPreparation  (solvePtr);  // includes exchanges the local NEQ
                                     // so it should be after degree of freedom

  SolveBoundaryDataPreparation(solvePtr);
  
  SolveMatrixAllocate      (solvePtr);   // Matrix model dependent

  SolveCallAssembleRoutine (solvePtr);

  SolveNeumannConditions   (solvePtr);

  SolveDirichletConditions (solvePtr);
  
  SolveCallSolverRoutine   (solvePtr);

  SolvePostProcess         (solvePtr);   // edev routine

  SolveTerminateSequence   (solvePtr);

  SolveReturnSequence      (solvePtr);   // Language dependent

  /////////////////////////////////
  SolveRoutineTerminate    (solvePtr);


  return;
}




