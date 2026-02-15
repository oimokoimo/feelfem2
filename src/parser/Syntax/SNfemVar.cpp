/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNfemVar.cpp
 *  Date     : 2001/03/29
 *  Modified : 
 *  
 *  Purpose  : create Variable pofemer
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

#include "../../class/Variable.hpp"
#include "SNfemVar.hpp"

Variable * SNfemVar::CreateVariablePtr(void)
{
  Variable *newVarPtr = new Variable(name,VAR_FEM);
  newVarPtr->SetFunctionName(elementName);
  newVarPtr->SetParameters();

  return( newVarPtr );
}

