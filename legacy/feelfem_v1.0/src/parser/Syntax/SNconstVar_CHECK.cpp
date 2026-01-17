/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNconstVar_CHECK.cpp
 *  Date     : 2002/04/18 (BCN)
 *  Modified : 
 *  
 *  Purpose  : (note) _CHECK.cpp is used after long development period...
 *  
 */

#include "SNconstVar.hpp"
#include "Expression.hpp"
#include "ginac_funcs.hpp"

int SNconstVar::CheckInitialValue(void)
{
  if(initialExprPtr == 0) return(0);

  if(initialExprPtr->howManyIdentifiers() != 0) {
    return(1);  // error, in initial value only numeric is allowed
  }

  if(initialExprPtr->howManyNotIntrinsicFunctions() != 0) {
    return(1);
  }

  
  char exprbuf[MAX_EXPRPRINT_BUF];
  exprbuf[0] = '\0';
  initialExprPtr->exprPrint(exprbuf,EXPRPRINT_NORMAL,0,0);

  setExprGinacEvaluate( exprbuf );

  if(!isExprGinacNumeric()) {   // ginac told it is not numeric
    return(1); 
  }

  initialValue = getDoubleExprGinac();

  return(0);
}


