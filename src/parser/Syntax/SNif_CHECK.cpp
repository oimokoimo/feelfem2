/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNif_CHECK.cpp
 *  Date     : 2002/07/18
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

#include "../../check/check_funcs.hpp"
#include "SNif.hpp"

int SNif::labelDefined_check(list <string>&strLst)
{
  if( strLst.includes(gotoLabel)) return(0);

  SystemErrorAStrA(this,"Label ",gotoLabel," is not defiened.");

  return(1);
}

int SNif::checkValidExpr()
{
  int ret = 0;

  SNunit *suPtr = this;

  ret+= exprPtr->checkDefinedVariableSN(suPtr);
  ret+= exprPtr->checkDefinedVariableSN(suPtr);

  if(ret != 0) return(ret);
  
  ret += exprPtr->checkNoEwiseSN(this);
  ret += exprPtr->checkNoDifferentialFuncSN(this);
  ret += exprPtr->checkNoNormalSN(this);
  ret += exprPtr->checkNoFemSN(this);

  return(ret);
}
