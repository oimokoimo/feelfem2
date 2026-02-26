/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : ElemNormalVectorAssembly.cpp
 *  Date     : 2001/11/29 (original 1999/12/10)
 *  Modified :  
 *  
 *  Purpose  : Normal vector processing assemble scheme 
 *  
 *             Normal means there is only one type of element.
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

void ElemScheme::NormalVectorAssembly( Solve *solvePtr,SolveElement *sePtr)
{

  ElemRoutineInitialize(solvePtr,sePtr);
  ////////////////////////////////
  ElemRoutineHeader       ( sePtr );
  
  ElemParameters          ( sePtr );

  ElemVariableDefinitions ( sePtr );

  ElemInitializer         ( sePtr );    // call eset family, etc.

  for(int i=0;i<sePtr->GetQuadratures();i++) {

    ElemQuadratureLoopStart ( sePtr ,i);  // This is numerical integration loop

    ElemQuadLoopPreparation ( sePtr ,i);    // Jacobian, Inverse, Determinant
  
    ElemQuadLoopMakeAllElement ( sePtr ,i); // All siffness element ...

    ElemQuadratureLoopEnd   ( sePtr ,i);
  }

  ElemAssembleMatrix      ( sePtr, 0 );  // Very special..... for vector 

  ElemReturnSequence      (sePtr );   // Language dependent

  /////////////////////////////////
  ElemRoutineTerminate();

  return;
}


