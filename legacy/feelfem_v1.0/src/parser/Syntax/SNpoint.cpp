/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNpoint.cpp
 *  Date     : 2001/03/23
 *  Modified : 
 *  
 *  Purpose  :
 *  
 */
#include <assert.h>
#include "SNpoint.hpp"
#include "../../class/Point.hpp"

int SNpoint::evalCoordinate(ptrList<evalPair *> *pairLstPtr)
{
  int total_errors,errFlag;
  double val;

  char   buf[MAX_EXPRPRINT_BUF];

  total_errors = 0;

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
    abortExit("Illegal dimension in SNpoint.cpp");
    break;
  }
  return(total_errors);
}

Point *SNpoint::MakePointObj(void)
{
  Point *pPtr;
  switch(dimension) {
  case 1:
    pPtr = new Point(xval);
    break;
  case 2:
    pPtr = new Point(xval,yval);
    break;
  case 3:
    pPtr = new Point(xval,yval,zval);
    break;
  default:
    assert(1==0);
  }

  return(pPtr);
}

Point *SNpoint::MakePointObjWithName(void)
{
  Point *pPtr;
  switch(dimension) {
  case 1:
    pPtr = new Point(name,xval);
    break;
  case 2:
    pPtr = new Point(name,xval,yval);
    break;
  case 3:
    pPtr = new Point(name,xval,yval,zval);
    break;
  default:
    assert(1==0);
  }

  return(pPtr);
}
