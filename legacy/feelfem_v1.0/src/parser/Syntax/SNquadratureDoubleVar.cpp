/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNquadratureDoubleVar.cpp
 *  Date     : 2001/12/12  (copy of SNmeshDoubleVar.cpp)
 *  Modified : 
 *  
 *  Purpose  : Evaluation 
 *  
 */

#include "SNquadratureDoubleVar.hpp"
#include "../../check/check_funcs.hpp"

evalPair *SNquadratureDoubleVar::makeEvalPair(ptrList<evalPair *> *pairLstPtr)
{                    /* return NULL if error 
			initial value cannot be evaluated  */

  evalPair *np = new evalPair(name);

  if(pairLstPtr->includes(np)) {
    delete np;
    return(NULL);
  }

  return(np);
}

double SNquadratureDoubleVar::evalInitialValue(ptrList<evalPair *> *pairLstPtr,
					 int & errFlag)
{
  double val;

  char   buf[MAX_EXPRPRINT_BUF];
  buf[0] = '\0';

  initialExprPtr->exprPrint(buf,EXPRPRINT_REPLACE_EVALPAIR,
			    (void *)pairLstPtr,(void *)0);

  val = evaluateBufGinac(buf,pairLstPtr,errFlag);
  return(val);
}
