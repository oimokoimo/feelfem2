/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNquadratureGAussP.cpp
 *  Date     : 2001/12/12
 *  Modified : 
 *  
 *  Purpose  : Evaluate (xi,eta,zeta) and weight
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

#include <iostream>
#include <cassert>

#include "evalPair.hpp"
#include "SNquadratureGaussP.hpp"


int SNquadratureGaussP::evalCoordinateAndWeight(ptrList<evalPair *>*pairLstPtr)
{
  int total_errors,errFlag;
  double val;

  char   buf[MAX_EXPRPRINT_BUF];

  total_errors = 0;


  // Evaluate weight expression
  buf[0] = '\0';
  weightExprPtr->exprPrint(buf,EXPRPRINT_REPLACE_EVALPAIR,
			   (void *)pairLstPtr,(void *)0);
  weight = evaluateBufGinac(buf,pairLstPtr,errFlag);
  total_errors = total_errors + errFlag;

  // Evaluate coordinate expression
  switch(dimension) {
  case 3:
    buf[0] = '\0';
    z->exprPrint(buf,EXPRPRINT_REPLACE_EVALPAIR,
		 (void *)pairLstPtr,(void *)0);
    zval = evaluateBufGinac(buf,pairLstPtr,errFlag);
    total_errors = total_errors + errFlag;

  case 2:
    buf[0] = '\0';
    y->exprPrint(buf,EXPRPRINT_REPLACE_EVALPAIR,
		 (void *)pairLstPtr,(void *)0);
    yval = evaluateBufGinac(buf,pairLstPtr,errFlag);
    total_errors = total_errors + errFlag;

  case 1:
    buf[0] = '\0';
    x->exprPrint(buf,EXPRPRINT_REPLACE_EVALPAIR,
		 (void *)pairLstPtr,(void *)0);
    xval = evaluateBufGinac(buf,pairLstPtr,errFlag);
    total_errors = total_errors + errFlag;
    break;

  default:
    assert(1==0);
    break;
  }

  return(total_errors);
}
