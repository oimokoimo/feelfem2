/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNewiseVar.cpp
 *  Date     : 2001/03/29
 *  Modified : 
 *  
 *  Purpose  : create Variable poewiseer
 *  
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

#include "Variable.hpp"
#include "SNewiseVar.hpp"

Variable * SNewiseVar::CreateVariablePtr(void)
{
  Variable *newVarPtr;
  if(isAttribute == YES) {
    newVarPtr = new Variable(name,VAR_EWISE_A);
    newVarPtr->SetFunctionName(attributeName);
    newVarPtr->SetParameters();
  }
  else {
    newVarPtr = new Variable(name,VAR_EWISE);
    newVarPtr->SetParameters();    
  }
  return( newVarPtr );

}

