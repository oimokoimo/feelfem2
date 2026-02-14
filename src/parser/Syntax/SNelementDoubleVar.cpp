/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNelementDoubleVar.cpp
 *  Date     : 2001/12/25
 *  Modified : 2001/12/30
 *  
 *  Purpose  : 
 *  
 *  
 *             makeEvalPair(ptrList<evalPair*>*)  2001/12/30 (copy of quad)
 *             evalInitialValue(...)              2001/12/30
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

#include "evalPair.hpp"
#include "SNelementDoubleVar.hpp"

int SNelementDoubleVar::howManyNotDefinedVariable
(int flag, void *ptr1, void *ptr2)
{
  return(initialExprPtr->howManyNotDefinedVariable(flag,ptr1,ptr2));
}

int SNelementDoubleVar::howManyNotDefinedFunction
(int flag, void *ptr1, void *ptr2) 
{
  return(initialExprPtr->howManyNotDefinedFunction(flag,ptr1,ptr2));
}

int SNelementDoubleVar::howManyNotAssignedVariable
(int flag, void *ptr1, void *ptr2) 
{
  return(initialExprPtr->howManyNotAssignedVariable(flag,ptr1,ptr2));
}


// CHECK routine

evalPair *SNelementDoubleVar::makeEvalPair(ptrList<evalPair *> *pairLstPtr)
{                    /* return NULL if error 
			initial value cannot be evaluated  */

  evalPair *np = new evalPair(name);

  if(pairLstPtr->includes(np)) {
    delete np;
    return(NULL);
  }

  return(np);
}

double SNelementDoubleVar::evalInitialValue(ptrList<evalPair *> *pairLstPtr,
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
