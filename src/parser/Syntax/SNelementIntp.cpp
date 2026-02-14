/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNelementIntp.cpp
 *  Date     : 2001/12/25
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
 *  
 */

#include "SNelementIntp.hpp"


SNelementIntp::SNelementIntp( SNunit *exlstPtr, Expression *ptr) 
  : SNunit("elementIntp",SN_ELEMENTINTP) {

  SNexprlist *asExprlistPtr;
  asExprlistPtr = (SNexprlist *)exlstPtr;
  typeName      = INTERP_NAME_NODAL;
  type          = INTERP_TYPE_NODAL;

  etype         = 0;                    // initialize to null

  exprlistPtr = asExprlistPtr;
  exprPtr   = ptr;

  dimension = asExprlistPtr->howManyElements();

  xval = 911.0;
  yval = 911.0;
  zval = 911.0;

  switch(dimension) {
  case 1:
    x = new Expression(asExprlistPtr->getIth(0));   // ugly code
    y = 0;
    z = 0;
    break;

  case 2:
    x = new Expression(asExprlistPtr->getIth(0));   // ugly code
    y = new Expression(asExprlistPtr->getIth(1));   // ugly code
    z = 0;
    break;

  case 3:
    x = new Expression(asExprlistPtr->getIth(0));   // ugly code
    y = new Expression(asExprlistPtr->getIth(1));   // ugly code
    z = new Expression(asExprlistPtr->getIth(2));   // ugly code
    break;

  default:
    break;

  }
  return;
}

SNelementIntp::SNelementIntp( SNunit *exlstPtr, char *typnm ,Expression *ptr) 
  : SNunit("elementIntp",SN_ELEMENTINTP) {

  SNexprlist *asExprlistPtr;
  asExprlistPtr = (SNexprlist *)exlstPtr;
  typeName = typnm;
  type     = 0;

  exprlistPtr = asExprlistPtr;
  exprPtr   = ptr;

  dimension = asExprlistPtr->howManyElements();

  xval = 911.0;
  yval = 911.0;
  zval = 911.0;

  switch(dimension) {
  case 1:
    x = new Expression(asExprlistPtr->getIth(0));   // ugly code
    y = 0;
    z = 0;
    break;

  case 2:
    x = new Expression(asExprlistPtr->getIth(0));   // ugly code
    y = new Expression(asExprlistPtr->getIth(1));   // ugly code
    z = 0;
    break;

  case 3:
    x = new Expression(asExprlistPtr->getIth(0));   // ugly code
    y = new Expression(asExprlistPtr->getIth(1));   // ugly code
    z = new Expression(asExprlistPtr->getIth(2));   // ugly code
    break;

  default:
    break;
  }

  return;
}


int SNelementIntp::howManyNotDefinedVariable(int flag, void *ptr1, void *ptr2) {
  int ret;
  ret = 0;
    
  switch(dimension){
  case 1:
    ret = x->howManyNotDefinedVariable(flag,ptr1,ptr2);
    break;

  case 2:
    ret  = x->howManyNotDefinedVariable(flag,ptr1,ptr2);
    ret += y->howManyNotDefinedVariable(flag,ptr1,ptr2);
    break;
      
  case 3:
    ret  = x->howManyNotDefinedVariable(flag,ptr1,ptr2);
    ret += y->howManyNotDefinedVariable(flag,ptr1,ptr2);
    ret += z->howManyNotDefinedVariable(flag,ptr1,ptr2);
    break;

  default:
    abortExit("Illegal dimension in SNelementIntp");
    break;
  }
  return(ret);
}

int SNelementIntp::howManyNotDefinedFunction(int flag, void *ptr1, void *ptr2) {
  int ret;
  ret = 0;
    
  switch(dimension){
  case 1:
    ret = x->howManyNotDefinedFunction(flag,ptr1,ptr2);
    break;

  case 2:
    ret  = x->howManyNotDefinedFunction(flag,ptr1,ptr2);
    ret += y->howManyNotDefinedFunction(flag,ptr1,ptr2);
    break;
      
  case 3:
    ret  = x->howManyNotDefinedFunction(flag,ptr1,ptr2);
    ret += y->howManyNotDefinedFunction(flag,ptr1,ptr2);
    ret += z->howManyNotDefinedFunction(flag,ptr1,ptr2);
    break;

  default:
    abortExit("Illegal dimension in SNelementIntp");
    break;
  }
  return(ret);
}


int SNelementIntp::howManyNotAssignedVariable(int flag,void *ptr1, void *ptr2)
{
  int ret;
  ret = 0;
    
  switch(dimension){
  case 1:
    ret = x->howManyNotAssignedVariable(flag,ptr1,ptr2);
    break;

  case 2:
    ret  = x->howManyNotAssignedVariable(flag,ptr1,ptr2);
    ret += y->howManyNotAssignedVariable(flag,ptr1,ptr2);
    break;
      
  case 3:
    ret  = x->howManyNotAssignedVariable(flag,ptr1,ptr2);
    ret += y->howManyNotAssignedVariable(flag,ptr1,ptr2);
    ret += z->howManyNotAssignedVariable(flag,ptr1,ptr2);
    break;

  default:
    abortExit("Illegal dimension in SNelementIntp");
    break;
  }
  return(ret);
}

//int SNelementIntp::evalCoordinate(ptrList <evalPair*>*);  is in _CHECK.cpp


Node *SNelementIntp::generateNodeClass(void)
{
  Node *nPtr;

  nPtr = 0;   // set null pointer

  switch(dimension) {
  case 0:
    assert(1==0);  // never happen
    break;

  case 1:
    nPtr = new Node(etype,xval);
    break;

  case 2:
    nPtr = new Node(etype,xval,yval);
    break;

  case 3:
    nPtr = new Node(etype,xval,yval,zval);
    break;

  default:
    assert(1==0);
  }

  return(nPtr);
}
