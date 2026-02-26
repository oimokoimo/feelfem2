/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SolveSchemeVirtuals.cpp
 *  Date     : 1999/11/15
 *  Modified : 1999/11/15
 *  
 *  Purpose  : Virtual function definitions
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

void SolveScheme::SolveRoutineInitialize   (Solve *)
{
  std::cout << "ERROR SolveScheme::SolveRoutineInitialize\n";
}

void SolveScheme::SolveRoutineTerminate    (Solve *)
{
  std::cout << "ERROR SolveScheme::SolveRoutineTerminate\n";
}

void SolveScheme::SolveRoutineHeader       (Solve *)
{
  std::cout << "ERROR SolveScheme::SolveRoutineHeader\n";
}

void SolveScheme::SolveParameters         (Solve *) 
{
  std::cout << "ERROR SolveScheme::SolveParameters\n";
}
void SolveScheme::SolveVariableDefinitions(Solve *) 
{
  std::cout << "ERROR SolveScheme::SolveVariableDefinitions\n";
}
void SolveScheme::SolveInitializer        (Solve *) 
{
  std::cout << "ERROR SolveScheme::SolveInitializer\n";
}
void SolveScheme::SolveDegreeOfFreedom    (Solve *) 
{
  std::cout << "ERROR SolveScheme::SolveDegreeOfFreedom\n";
}
void SolveScheme::SolveBoundaryDataPreparation    (Solve *) 
{
  std::cout << "ERROR SolveScheme::SolveBoundaryDataPreparation\n";
}
void SolveScheme::SolveMatrixAllocate     (Solve *)  
{
  std::cout << "ERROR SolveScheme::SolveMatrixAllocate\n";
}
void SolveScheme::SolveCallAssembleRoutine(Solve *) 
{
  std::cout << "ERROR SolveScheme::SolveCallAssembleRoutine\n";
}
void SolveScheme::SolveNeumannConditions  (Solve *)  
{
  std::cout << "ERROR SolveScheme::SolveNeumannConditions\n";
}
void SolveScheme::SolveDirichletConditions(Solve *)  
{
  std::cout << "ERROR SolveScheme::SolveDirichletConditions\n";
}
void SolveScheme::SolveCallSolverRoutine  (Solve *)  
{
  std::cout << "ERROR SolveScheme::SolveCallSolverRoutine\n";
}
void SolveScheme::SolvePostProcess        (Solve *)  
{
  std::cout << "ERROR SolveScheme::SolvePostProcess\n";
}
void SolveScheme::SolveTerminateSequence  (Solve *)  
{
  std::cout << "ERROR SolveScheme::SolveTerminateSequence\n";
}
void SolveScheme::SolveReturnSequence     (Solve *)  
{
  std::cout << "ERROR SolveScheme::SolveReturnSequence\n";
}

void SolveScheme::SolveNonlinearInitialize     (Solve *)  
{
  std::cout << "ERROR SolveScheme::SolveNonlinearInitialize\n";
}


void SolveScheme::SolveNonlinearPostProcess     (Solve *)  
{
  std::cout << "ERROR SolveScheme::SolveNonlinearPostProcess\n";
}

// Parallel version
void SolveScheme::SolveAssemblyPreparation      (Solve *)  
{
  std::cout << "ERROR SolveScheme::SolveNonlinearInitialize\n";
}
