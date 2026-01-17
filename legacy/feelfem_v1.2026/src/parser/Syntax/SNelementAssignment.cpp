/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNelementAssignment.cpp
 *  Date     : 2001/12/30              (Copy of SNquadratureAssignment.cpp)
 *  Modified : 
 *  
 *  Purpose  :
 *  
 */
#include "SNelementAssignment.hpp"

double SNelementAssignment::evalValue(ptrList<evalPair *> *pairLstPtr,
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
