/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : EcalNormalElementStiffness.cpp
 *  Date     : 2002/02/19
 *  Modified : 
 *  
 *  Purpose  :
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

#include "EcalScheme.hpp"


void EcalScheme::NormalElementStiffness( Solve *solvePtr,SolveElement *sePtr)
{

  EcalRoutineInitialize(solvePtr,sePtr);
  ////////////////////////////////
  EcalRoutineHeader       ( sePtr );
  
  EcalParameters          ( sePtr );

  EcalVariableDefinitions ( sePtr );

  EcalInitializer         ( sePtr );

  EcalElementMatInitialize( sePtr );

  for(int i=0;i<sePtr->GetQuadratures();i++) {
    
    EcalQuadLoopStart     (i+1,sePtr);   // i+1 = quadNo
    EcalCalcJacobian      (i+1,sePtr);
    EcalSetValAtGaussP    (i+1,sePtr);
    EcalCalcElementMatRHS (i+1,sePtr);  // ea(n,n) and eb(n)
    EcalQuadLoopEnd       (i+1,sePtr);
  }

  EcalReturnSequence      ( sePtr );

  /////////////////////////////////
  EcalRoutineTerminate(sePtr);

  return;
}
