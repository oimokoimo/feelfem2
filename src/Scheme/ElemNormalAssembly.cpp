/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : ElemNormalAssembly.cpp
 *  Date     : 1999/12/10
 *  Modified : 1999/12/10
 *  
 *  Purpose  : Normal assemble scheme 
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

#include "ElemScheme.hpp"

void ElemScheme::NormalAssembly( Solve *solvePtr,SolveElement *sePtr)
{

  ElemRoutineInitialize(solvePtr,sePtr);
  ////////////////////////////////
  ElemRoutineHeader       ( sePtr );
  
  ElemParameters          ( sePtr );

  ElemVariableDefinitions ( sePtr );

  ElemInitializer         ( sePtr );
  
  ElemElementLoopStart    ( sePtr ,MY_ELEMENT);

  ElemCallEcalRoutine     ( sePtr ,MY_ELEMENT);
  
  ElemAssembleMatrix      ( sePtr ,MY_ELEMENT);

  ElemElementLoopEnd      ( sePtr ,MY_ELEMENT);

  ElemReturnSequence      ( sePtr);   // Language dependent

  /////////////////////////////////
  ElemRoutineTerminate();

  return;
}


