/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNelementIntp_CHECK.cpp
 *  Date     : 2001/12/29
 *  Modified : 
 *  
 *  Purpose  : evaluate node coordinates
 *  
 */

#include <iostream.h>
#include <assert.h>

#include "evalPair.hpp"
#include "SNelementIntp.hpp"


int SNelementIntp::evalCoordinate(ptrList<evalPair *>*pairLstPtr)
{
  int total_errors,errFlag,ret;
  double val;

  char   buf[MAX_EXPRPRINT_BUF];

  total_errors = 0;

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

int SNelementIntp::checkTypeAttribute(void)
{
  if(typeName == INTERP_NAME_NODAL) {
    type = INTERP_TYPE_NODAL;
    return(0);
  }

  if(typeName == INTERP_NAME_DX) {
    type = INTERP_TYPE_DX;
    return(0);
  }

  if(typeName == INTERP_NAME_DY) {
    type = INTERP_TYPE_DY;
    return(0);
  }

  if(typeName == INTERP_NAME_DZ) {
    type = INTERP_TYPE_DZ;
    return(0);
  }

  if(typeName == INTERP_NAME_DN) {
    type = INTERP_TYPE_DN;
    return(0);
  }

  return(1);   // undefined symbol specified
}
