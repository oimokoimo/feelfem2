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
 */
#include "feelfuncs.hpp"
#include "NeumannScheme.hpp"


void NeumannScheme::NeumannRoutineInitialize  (Solve *solvePtr,Neumann *nPtr)
{
  cerr << "Neumann Scheme Virtual " << "Neumann Routine Initialize "
       << "called\n";
  abortExit(1);
}

void NeumannScheme::NeumannRoutineTerminate   (void          )
{
  cerr << "Neumann Scheme Virtual " << "NeumannRoutineTerminate "
       << "called\n";
  abortExit(1);
}

void NeumannScheme::NeumannRoutineHeader   (Neumann *nPtr)
{
  cerr << "Neumann Scheme Virtual " << "NeumannRoutineHeader "
       << "called\n";
  abortExit(1);
}

void NeumannScheme::NeumannParameters         (Neumann *nPtr)
{
  cerr << "Neumann Scheme Virtual " << "NeumannParameters "
       << "called\n";
  abortExit(1);
}

void NeumannScheme::NeumannVariableDefinitions(Neumann *nPtr)
{
  cerr << "Neumann Scheme Virtual " << "NeumannVariableDefinitions"
       << "called\n";
  abortExit(1);
}

void NeumannScheme::NeumannInitializer        (Neumann *nPtr)
{
  cerr << "Neumann Scheme Virtual " << "NeumannInitializer "
       << "called\n";
  abortExit(1);
}

void NeumannScheme::NeumannBoundaryElementLoopStart(Neumann *nPtr)
{
  cerr << "Neumann Scheme Virtual " << "NeumannBoundaryElementLoopStart "
       << "called\n";
  abortExit(1);
}

void NeumannScheme::NeumannApplyMatrix        (Neumann *nPtr)
{
  cerr << "Neumann Scheme Virtual " << "NeumannApplyMatrix "
       << "called\n";
  abortExit(1);
}

void NeumannScheme::NeumannBoundaryElementLoopEnd(Neumann *nPtr)
{
  cerr << "Neumann Scheme Virtual " << "NeumannBoundaryElementLoopEnd "
       << "called\n";
  abortExit(1);
}

void NeumannScheme::NeumannReturnSequence     (Neumann *nPtr)
{
  cerr << "Neumann Scheme Virtual " << "NeumannReturnSequence "
       << "called\n";
  abortExit(1);
}

