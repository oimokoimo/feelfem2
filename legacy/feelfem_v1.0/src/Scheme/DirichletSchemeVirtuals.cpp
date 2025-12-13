/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : DirichletSchemeVirtuals.cpp
 *  Date     : 1999/12/23
 *  Modified : 1999/12/23
 *  
 *  Purpose  : Virtual fuction instance for DirichletScheme class
 *  
 */

#include "feelfuncs.hpp"
#include "DirichletScheme.hpp"


void DirichletScheme::DirichletRoutineInitialize  (Solve *solvePtr,
						   Dirichlet *dPtr)
{
  cerr << "Dirichlet Scheme Virtual " << "Dirichlet Routine Initialize "
       << "called\n";
  abortExit(1);
}

void DirichletScheme::DirichletRoutineTerminate   (void          )
{
  cerr << "Dirichlet Scheme Virtual " << "DirichletRoutineTerminate "
       << "called\n";
  abortExit(1);
}

void DirichletScheme::DirichletRoutineHeader   (Dirichlet *dPtr)
{
  cerr << "Dirichlet Scheme Virtual " << "DirichletRoutineHeader " 
       << "called\n";
  abortExit(1);
}

void DirichletScheme::DirichletParameters         (Dirichlet *dPtr)
{
  cerr << "Dirichlet Scheme Virtual " << "DirichletParameters "
       << "called\n";
  abortExit(1);
}

void DirichletScheme::DirichletVariableDefinitions(Dirichlet *dPtr)
{
  cerr << "Dirichlet Scheme Virtual " << "DirichletVariableDefinitions"
       << "called\n";
  abortExit(1);
}

void DirichletScheme::DirichletInitializer        (Dirichlet *dPtr)
{
  cerr << "Dirichlet Scheme Virtual " << "DirichletInitializer "
       << "called\n";
  abortExit(1);
}

void DirichletScheme::DirichletLoopStart          (Dirichlet *dPtr)
{
  cerr << "Dirichlet Scheme Virtual " << "DirichletLoopStart "
       << "called\n";
  abortExit(1);
}

void DirichletScheme::DirichletCalcBoundaryValue  (Dirichlet *dPtr)
{
  cerr << "Dirichlet Scheme Virtual " << "DirichletCalcBoundaryValue "
       << "called\n";
  abortExit(1);
}

void DirichletScheme::DirichletApplyMatrix        (Dirichlet *dPtr)
{
  cerr << "Dirichlet Scheme Virtual " << "DirichletApplyMatrix "
       << "called\n";
  abortExit(1);
}

void DirichletScheme::DirichletLoopEnd          (Dirichlet *dPtr)
{
  cerr << "Dirichlet Scheme Virtual " << "DirichletLoopEnd "
       << "called\n";
  abortExit(1);
}

void DirichletScheme::DirichletReturnSequence     (Dirichlet *dPtr)
{
  cerr << "Dirichlet Scheme Virtual " << "DirichletReturnSequence "
       << "called\n";
  abortExit(1);
}
