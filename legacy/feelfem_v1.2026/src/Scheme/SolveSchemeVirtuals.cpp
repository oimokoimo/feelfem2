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
 */

#include "SolveScheme.hpp"

void SolveScheme::SolveRoutineInitialize   (Solve *)
{
  cout << "ERROR SolveScheme::SolveRoutineInitialize\n";
}

void SolveScheme::SolveRoutineTerminate    (Solve *)
{
  cout << "ERROR SolveScheme::SolveRoutineTerminate\n";
}

void SolveScheme::SolveRoutineHeader       (Solve *)
{
  cout << "ERROR SolveScheme::SolveRoutineHeader\n";
}

void SolveScheme::SolveParameters         (Solve *) 
{
  cout << "ERROR SolveScheme::SolveParameters\n";
}
void SolveScheme::SolveVariableDefinitions(Solve *) 
{
  cout << "ERROR SolveScheme::SolveVariableDefinitions\n";
}
void SolveScheme::SolveInitializer        (Solve *) 
{
  cout << "ERROR SolveScheme::SolveInitializer\n";
}
void SolveScheme::SolveDegreeOfFreedom    (Solve *) 
{
  cout << "ERROR SolveScheme::SolveDegreeOfFreedom\n";
}
void SolveScheme::SolveBoundaryDataPreparation    (Solve *) 
{
  cout << "ERROR SolveScheme::SolveBoundaryDataPreparation\n";
}
void SolveScheme::SolveMatrixAllocate     (Solve *)  
{
  cout << "ERROR SolveScheme::SolveMatrixAllocate\n";
}
void SolveScheme::SolveCallAssembleRoutine(Solve *) 
{
  cout << "ERROR SolveScheme::SolveCallAssembleRoutine\n";
}
void SolveScheme::SolveNeumannConditions  (Solve *)  
{
  cout << "ERROR SolveScheme::SolveNeumannConditions\n";
}
void SolveScheme::SolveDirichletConditions(Solve *)  
{
  cout << "ERROR SolveScheme::SolveDirichletConditions\n";
}
void SolveScheme::SolveCallSolverRoutine  (Solve *)  
{
  cout << "ERROR SolveScheme::SolveCallSolverRoutine\n";
}
void SolveScheme::SolvePostProcess        (Solve *)  
{
  cout << "ERROR SolveScheme::SolvePostProcess\n";
}
void SolveScheme::SolveTerminateSequence  (Solve *)  
{
  cout << "ERROR SolveScheme::SolveTerminateSequence\n";
}
void SolveScheme::SolveReturnSequence     (Solve *)  
{
  cout << "ERROR SolveScheme::SolveReturnSequence\n";
}

void SolveScheme::SolveNonlinearInitialize     (Solve *)  
{
  cout << "ERROR SolveScheme::SolveNonlinearInitialize\n";
}


void SolveScheme::SolveNonlinearPostProcess     (Solve *)  
{
  cout << "ERROR SolveScheme::SolveNonlinearPostProcess\n";
}

// Parallel version
void SolveScheme::SolveAssemblyPreparation      (Solve *)  
{
  cout << "ERROR SolveScheme::SolveNonlinearInitialize\n";
}
