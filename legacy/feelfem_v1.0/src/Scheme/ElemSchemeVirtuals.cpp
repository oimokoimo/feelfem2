/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : ElemSchemeVirtuals.cpp
 *  Date     : 1999/12/10
 *  Modified : 1999/12/10
 *  
 *  Purpose  : Virtual function definitionsn
 *  
 */
#include <iostream.h>
#include "ElemScheme.hpp"

void ElemScheme::ElemRoutineInitialize  (Solve *,SolveElement *)
{
  cerr << "ElemScheme virtual  argument sequence \n";
}

void ElemScheme::ElemRoutineTerminate   (void)
{
  cerr << "ElemScheme virtual  argument sequence \n";
}


void ElemScheme::ElemRoutineHeader   (SolveElement *)
{
  cerr << "ElemScheme virtual  routine header \n";
}
void ElemScheme::ElemParameters         (SolveElement *)
{
  cerr << "ElemScheme virtual elem parameters  \n";
}
void ElemScheme::ElemVariableDefinitions(SolveElement *)
{
  cerr << "ElemScheme virtual elem variable definitions  \n";
}
void ElemScheme::ElemInitializer        (SolveElement *)
{
  cerr << "ElemScheme virtual  elem initializer \n";
}

void ElemScheme::ElemElementLoopStart   (SolveElement *, int )
{
  cerr << "ElemScheme virtual  elem loop start \n";
}



void ElemScheme::ElemCallEcalRoutine    (SolveElement *, int)
{
  cerr << "ElemScheme virtual  elem call ecal routine \n";
}
void ElemScheme::ElemAssembleMatrix     (SolveElement *,int )
{
  cerr << "ElemScheme virtual  elem assemble matrix \n";
}
void ElemScheme::ElemElementLoopEnd     (SolveElement *, int)
{
  cerr << "ElemScheme virtual elem element loop end  \n";
}

void ElemScheme::ElemReturnSequence     (SolveElement *)
{
  cerr << "ElemScheme virtual  elem return sequence \n";
}

// for vector processing 2001/11/29
void ElemScheme::ElemQuadratureLoopStart (SolveElement *, int )
{
  cerr << "ElemScheme virtual  elem loop start for vector\n";
}

void ElemScheme::ElemQuadratureLoopEnd   (SolveElement *, int)
{
  cerr << "ElemScheme virtual elem element loop end for vector \n";
}

void ElemScheme::ElemQuadLoopPreparation   (SolveElement *, int)
{
  cerr << "ElemScheme virtual elem element loop end for vector \n";
}

void ElemScheme::ElemQuadLoopMakeAllElement (SolveElement *, int)
{
  cerr << "ElemScheme virtual elem element loop end for vector \n";
}
