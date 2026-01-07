/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNmeshDoubleVar.cpp
 *  Date     : 2001/03/19
 *  Modified : 
 *  
 *  Purpose  :
 *  
 */

#include "SNmeshDoubleVar.hpp"
#include "../../check/check_funcs.hpp"

evalPair *SNmeshDoubleVar::makeEvalPair(ptrList<evalPair *> *pairLstPtr)
{                    /* return NULL if error 
			initial value cannot be evaluated  */

  evalPair *np = new evalPair(name);

  if(pairLstPtr->includes(np)) {
    delete np;
    return(NULL);
  }

  return(np);
}

double SNmeshDoubleVar::evalInitialValue(ptrList<evalPair *> *pairLstPtr,
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
