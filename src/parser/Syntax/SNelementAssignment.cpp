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
