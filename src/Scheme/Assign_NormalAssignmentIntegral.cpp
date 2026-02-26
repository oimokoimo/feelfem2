/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : Assign_NormalAssignmentIntegral.cpp
 *  Date     : 2002/10/27 (Copied from Assig_NormalAssignmentEwiseQuad.cpp)
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

void AssignScheme::NormalAssignmentIntegral(Assign *asPtr)
{
  AssignRoutineInitialize   (asPtr);
  AssignRoutineHeader       (asPtr);
  AssignParametersEwQuad    (asPtr);
  AssignVariableDefinitions (asPtr);
  AssignVariableDefinitionsEwQuad (asPtr);
  AssignInitializeIntegral  (asPtr);
  AssignLoopStartEwQuad     (asPtr);         // ewise quad
  AssignAssignmentIntegral  (asPtr);
  AssignLoopEndIntegral     (asPtr);
  AssignReturnSequence      (asPtr);

  AssignRoutineTerminate    (asPtr);

  return;
}


void AssignScheme::NormalAssignmentIntegralCoroutine(Assign *asPtr)
{
  AssignCoRoutineInitialize       (asPtr);
  AssignCoRoutineHeaderIntegral   (asPtr);

  // USE EwQuad
  AssignCoRoutineParametersEwQuad          (asPtr);

  AssignCoRoutineVariableDefinitionsIntegral (asPtr);

  // USE EwQuad
  AssignCoRoutineQuadratureSettingsEwQuad  (asPtr);  // common and set common

  AssignCoRoutineStatementIntegral           (asPtr);         // ewise quad
  AssignCoRoutineReturnSequence   (asPtr);
  AssignCoRoutineTerminate        (asPtr);

  return;
}
