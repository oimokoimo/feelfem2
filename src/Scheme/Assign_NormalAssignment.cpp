/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : Assign_NormalAssignment.cpp
 *  Date     : 2002/04/16 (BCN)
 *  Modified : 
 *  
 *  Purpose  : assign scheme representation
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

void AssignScheme::NormalAssignment(Assign *asPtr)
{
  AssignRoutineInitialize   (asPtr);
  
  // Basic subroutine procedures
  AssignRoutineHeader       (asPtr);

  AssignParameters          (asPtr);

  AssignVariableDefinitions (asPtr);
  
  AssignStatement           (asPtr);
  
  AssignReturnSequence      (asPtr);

  AssignRoutineTerminate    (asPtr);

  return;
}
