/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : NeumannSchemeVirtuals.cpp
 *  Date     : 2000/01/19
 *  Modified : 2000/01/19
 *  
 *  Purpose  : NeumannScheme class virtual function declaration
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
#include "NeumannScheme.hpp"


void NeumannScheme::NeumannRoutineInitialize  (Solve *solvePtr,Neumann *nPtr)
{
  std::cerr << "Neumann Scheme Virtual " << "Neumann Routine Initialize "
       << "called\n";
  abortExit(1);
}

void NeumannScheme::NeumannRoutineTerminate   (void          )
{
  std::cerr << "Neumann Scheme Virtual " << "NeumannRoutineTerminate "
       << "called\n";
  abortExit(1);
}

void NeumannScheme::NeumannRoutineHeader   (Neumann *nPtr)
{
  std::cerr << "Neumann Scheme Virtual " << "NeumannRoutineHeader "
       << "called\n";
  abortExit(1);
}

void NeumannScheme::NeumannParameters         (Neumann *nPtr)
{
  std::cerr << "Neumann Scheme Virtual " << "NeumannParameters "
       << "called\n";
  abortExit(1);
}

void NeumannScheme::NeumannVariableDefinitions(Neumann *nPtr)
{
  std::cerr << "Neumann Scheme Virtual " << "NeumannVariableDefinitions"
       << "called\n";
  abortExit(1);
}

void NeumannScheme::NeumannInitializer        (Neumann *nPtr)
{
  std::cerr << "Neumann Scheme Virtual " << "NeumannInitializer "
       << "called\n";
  abortExit(1);
}

void NeumannScheme::NeumannBoundaryElementLoopStart(Neumann *nPtr)
{
  std::cerr << "Neumann Scheme Virtual " << "NeumannBoundaryElementLoopStart "
       << "called\n";
  abortExit(1);
}

void NeumannScheme::NeumannApplyMatrix        (Neumann *nPtr)
{
  std::cerr << "Neumann Scheme Virtual " << "NeumannApplyMatrix "
       << "called\n";
  abortExit(1);
}

void NeumannScheme::NeumannBoundaryElementLoopEnd(Neumann *nPtr)
{
  std::cerr << "Neumann Scheme Virtual " << "NeumannBoundaryElementLoopEnd "
       << "called\n";
  abortExit(1);
}

void NeumannScheme::NeumannReturnSequence     (Neumann *nPtr)
{
  std::cerr << "Neumann Scheme Virtual " << "NeumannReturnSequence "
       << "called\n";
  abortExit(1);
}

