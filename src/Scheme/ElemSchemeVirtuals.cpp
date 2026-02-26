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
#include "ElemScheme.hpp"

void ElemScheme::ElemRoutineInitialize  (Solve *,SolveElement *)
{
  std::cerr << "ElemScheme virtual  argument sequence \n";
}

void ElemScheme::ElemRoutineTerminate   (void)
{
  std::cerr << "ElemScheme virtual  argument sequence \n";
}


void ElemScheme::ElemRoutineHeader   (SolveElement *)
{
  std::cerr << "ElemScheme virtual  routine header \n";
}
void ElemScheme::ElemParameters         (SolveElement *)
{
  std::cerr << "ElemScheme virtual elem parameters  \n";
}
void ElemScheme::ElemVariableDefinitions(SolveElement *)
{
  std::cerr << "ElemScheme virtual elem variable definitions  \n";
}
void ElemScheme::ElemInitializer        (SolveElement *)
{
  std::cerr << "ElemScheme virtual  elem initializer \n";
}

void ElemScheme::ElemElementLoopStart   (SolveElement *, int )
{
  std::cerr << "ElemScheme virtual  elem loop start \n";
}



void ElemScheme::ElemCallEcalRoutine    (SolveElement *, int)
{
  std::cerr << "ElemScheme virtual  elem call ecal routine \n";
}
void ElemScheme::ElemAssembleMatrix     (SolveElement *,int )
{
  std::cerr << "ElemScheme virtual  elem assemble matrix \n";
}
void ElemScheme::ElemElementLoopEnd     (SolveElement *, int)
{
  std::cerr << "ElemScheme virtual elem element loop end  \n";
}

void ElemScheme::ElemReturnSequence     (SolveElement *)
{
  std::cerr << "ElemScheme virtual  elem return sequence \n";
}

// for vector processing 2001/11/29
void ElemScheme::ElemQuadratureLoopStart (SolveElement *, int )
{
  std::cerr << "ElemScheme virtual  elem loop start for vector\n";
}

void ElemScheme::ElemQuadratureLoopEnd   (SolveElement *, int)
{
  std::cerr << "ElemScheme virtual elem element loop end for vector \n";
}

void ElemScheme::ElemQuadLoopPreparation   (SolveElement *, int)
{
  std::cerr << "ElemScheme virtual elem element loop end for vector \n";
}

void ElemScheme::ElemQuadLoopMakeAllElement (SolveElement *, int)
{
  std::cerr << "ElemScheme virtual elem element loop end for vector \n";
}
