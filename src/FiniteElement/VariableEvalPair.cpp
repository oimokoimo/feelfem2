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
#include <cassert>

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

VariableEvalPair::~VariableEvalPair() = default;


Variable *VariableEvalPair::GetVariablePtr(void)
{
  return variablePtr;
}

Element *VariableEvalPair::GetElementPtr(void)
{
  assert(variablePtr->IsElementPtrReady());
  
  return(variablePtr->GetElementPtr());
}

