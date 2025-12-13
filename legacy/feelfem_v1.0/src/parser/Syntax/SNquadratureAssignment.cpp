/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNquadratureAssignment.cpp
 *  Date     : 2001/12/12  (copy of SNmeshAssignment.cpp)
 *  Modified : 
 *  
 *  Purpose  :
 *  
 */
#include "SNquadratureAssignment.hpp"

double SNquadratureAssignment::evalValue(ptrList<evalPair *> *pairLstPtr,
					  int & errFlag)
{
  double val;

  char   buf[MAX_EXPRPRINT_BUF];
  buf[0] = '\0';

  exprPtr->exprPrint(buf,EXPRPRINT_REPLACE_EVALPAIR,
		     (void *)pairLstPtr,(void *)0);
  val = evaluateBufGinac(buf,pairLstPtr,errFlag);
  return(val);
}
