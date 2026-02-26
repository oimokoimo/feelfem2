/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SolveNormalNonlinearProblem.cpp
 *  Date     : 1999/11/17
 *  Modified : 1999/11/17
 *  
 *  Purpose  : Normal nonlinear problem Solve routine generator
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

void SolveScheme::NormalNonlinearProblem( Solve *solvePtr)
{

  ////////////////////////////////
  SolveRoutineInitialize   (solvePtr);

  SolveRoutineHeader       (solvePtr);
  
  SolveParameters          (solvePtr);

  SolveVariableDefinitions (solvePtr);

  SolveInitializer         (solvePtr);
  
  SolveDegreeOfFreedom     (solvePtr);

  SolveBoundaryDataPreparation(solvePtr);
  
  SolveMatrixAllocate      (solvePtr);

  SolveNonlinearInitialize (solvePtr);

  SolveDirichletConditions (solvePtr);

  SolveCallAssembleRoutine (solvePtr);

  SolveNeumannConditions   (solvePtr);

  SolveDirichletConditions (solvePtr);
  
  SolveCallSolverRoutine   (solvePtr);

  SolveNonlinearPostProcess(solvePtr);   // edev routine for nonlinear

  SolveTerminateSequence   (solvePtr);

  SolveReturnSequence      (solvePtr);   // Language dependent

  /////////////////////////////////
  SolveRoutineTerminate    (solvePtr);


  return;
}
