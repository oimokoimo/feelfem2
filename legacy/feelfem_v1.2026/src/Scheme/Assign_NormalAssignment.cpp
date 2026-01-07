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
