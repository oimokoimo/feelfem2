/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : Assign_NormalAssignmentEwiseQuad.cpp
 *  Date     : 2002/07/11
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

#include "AssignScheme.hpp"

void AssignScheme::NormalAssignmentEwiseQuad(Assign *asPtr)
{
  AssignRoutineInitialize   (asPtr);
  AssignRoutineHeader       (asPtr);
  AssignParametersEwQuad    (asPtr);
  AssignVariableDefinitions (asPtr);
  AssignVariableDefinitionsEwQuad (asPtr);
  AssignInitializeEwQuad    (asPtr);
  AssignLoopStartEwQuad     (asPtr);         // ewise quad
  AssignAssignmentEwQuad    (asPtr);
  AssignLoopEndEwQuad       (asPtr);
  AssignReturnSequence      (asPtr);

  AssignRoutineTerminate    (asPtr);

  return;
}


void AssignScheme::NormalAssignmentEwiseQuadCoroutine(Assign *asPtr)
{
  AssignCoRoutineInitialize       (asPtr);
  AssignCoRoutineHeaderEwQuad     (asPtr);
  AssignCoRoutineParametersEwQuad          (asPtr);
  AssignCoRoutineVariableDefinitionsEwQuad (asPtr);
  AssignCoRoutineQuadratureSettingsEwQuad  (asPtr);  // common and set common
  AssignCoRoutineStatementEwQuad           (asPtr);         // ewise quad
  AssignCoRoutineReturnSequence   (asPtr);
  AssignCoRoutineTerminate        (asPtr);

  return;
}
