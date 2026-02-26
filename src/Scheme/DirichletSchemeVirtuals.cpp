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

#include "feelfuncs.hpp"
#include "DirichletScheme.hpp"


void DirichletScheme::DirichletRoutineInitialize  (Solve *solvePtr,
						   Dirichlet *dPtr)
{
	std::cerr << "Dirichlet Scheme Virtual " << "Dirichlet Routine Initialize "
       << "called\n";
  abortExit(1);
}

void DirichletScheme::DirichletRoutineTerminate   (void          )
{
  std::cerr << "Dirichlet Scheme Virtual " << "DirichletRoutineTerminate "
       << "called\n";
  abortExit(1);
}

void DirichletScheme::DirichletRoutineHeader   (Dirichlet *dPtr)
{
  std::cerr << "Dirichlet Scheme Virtual " << "DirichletRoutineHeader " 
       << "called\n";
  abortExit(1);
}

void DirichletScheme::DirichletParameters         (Dirichlet *dPtr)
{
  std::cerr << "Dirichlet Scheme Virtual " << "DirichletParameters "
       << "called\n";
  abortExit(1);
}

void DirichletScheme::DirichletVariableDefinitions(Dirichlet *dPtr)
{
  std::cerr << "Dirichlet Scheme Virtual " << "DirichletVariableDefinitions"
       << "called\n";
  abortExit(1);
}

void DirichletScheme::DirichletInitializer        (Dirichlet *dPtr)
{
  std::cerr << "Dirichlet Scheme Virtual " << "DirichletInitializer "
       << "called\n";
  abortExit(1);
}

void DirichletScheme::DirichletLoopStart          (Dirichlet *dPtr)
{
  std::cerr << "Dirichlet Scheme Virtual " << "DirichletLoopStart "
       << "called\n";
  abortExit(1);
}

void DirichletScheme::DirichletCalcBoundaryValue  (Dirichlet *dPtr)
{
  std::cerr << "Dirichlet Scheme Virtual " << "DirichletCalcBoundaryValue "
       << "called\n";
  abortExit(1);
}

void DirichletScheme::DirichletApplyMatrix        (Dirichlet *dPtr)
{
  std::cerr << "Dirichlet Scheme Virtual " << "DirichletApplyMatrix "
       << "called\n";
  abortExit(1);
}

void DirichletScheme::DirichletLoopEnd          (Dirichlet *dPtr)
{
  std::cerr << "Dirichlet Scheme Virtual " << "DirichletLoopEnd "
       << "called\n";
  abortExit(1);
}

void DirichletScheme::DirichletReturnSequence     (Dirichlet *dPtr)
{
  std::cerr << "Dirichlet Scheme Virtual " << "DirichletReturnSequence "
       << "called\n";
  abortExit(1);
}
