/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNexpr_CHECK.cpp
 *  Date     : 2002/11/22
 *  Modified : 
 *  
 *  Purpose  : check only global scalar variable appear
 *  
 */

#include "SNexpr.hpp"
#include "Expression.hpp"
#include "../../check/check_funcs.hpp"

int SNexpr::checkOnlyGlobalScalar(void)
{
  int ret,errors;

  errors = 0;
  
  ret = exprPtr->checkDefinedVariableSN(this);
  if(ret != 0) {
    errors = ret;
    return(ret);
  }

  ret = exprPtr->checkDefinedFunctionSN(this);
  if(ret != 0) {
    errors = ret;
    return(ret);
  }

  ret += exprPtr->checkNoFemSN(this);
  ret += exprPtr->checkNoCoordinateSN(this);
  ret += exprPtr->checkNoEwiseSN(this);
  ret += exprPtr->checkNoMaterialSN(this);
  ret += exprPtr->checkNoNormalSN(this);
  ret += exprPtr->checkNoDifferentialFuncSN(this);

  errors = ret;

  return(errors);
}

  
