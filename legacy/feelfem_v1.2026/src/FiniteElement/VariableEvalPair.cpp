/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : VariableEvalPair.cpp
 *  Date     : 2002/09/10
 *  Modified : 
 *  
 *  Purpose  : Variable eval pair for ewise quad assignment
 *  
 */
#include <assert.h>

#include "Variable.hpp"
#include "VariableEvalPair.hpp"
#include "Element.hpp"


VariableEvalPair::VariableEvalPair(Variable *vPtr,int dtype)
{
  variablePtr = vPtr;
  diffType    = dtype;

  if(variablePtr->IsElementPtrReady()) {
    elementPtr  = vPtr->GetElementPtr();
    isElement   = YES;
  }
  else {
    elementPtr  = 0;
    isElement   = NO;
  }
  return;
}

VariableEvalPair::~VariableEvalPair()
{
  // do nothing
}

Variable *VariableEvalPair::GetVariablePtr(void)
{
  return variablePtr;
}

Element *VariableEvalPair::GetElementPtr(void)
{
  assert(variablePtr->IsElementPtrReady());
  
  return(variablePtr->GetElementPtr());
}

