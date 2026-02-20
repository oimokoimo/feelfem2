/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNpoint.hpp
 *  Date     : 2001/02/23
 *  Modified : 2001/03/25
 *  
 *  Purpose  : point class for parser  (reference aumc)
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

#ifndef FEM_SYNTAX_POINT
#define FEM_SYNTAX_POINT

#include "SNunit.hpp"
#include "SNexprlist.hpp"
#include "../../class/string.hpp"
#include "../../class/Expression.hpp"
#include "../../class/feeldef.hpp"

class Point;


class SNpoint : public SNunit {
public:
  SNpoint( const char *nm, SNunit *ptr) : name(nm),SNunit("point",SN_POINT) {


    SNexprlist *asExprlistPtr;
    exprLst   = ptr;
    asExprlistPtr = (SNexprlist *)exprLst;
    dimension = asExprlistPtr->howManyElements();

    xval = UNDEFINED_DOUBLE;
    yval = UNDEFINED_DOUBLE;
    zval = UNDEFINED_DOUBLE;

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
      abortExit("Illegal dimension in SNpoint");
      break;

    }
    return;
  }

  // 
  int getSpaceDimension(void) {
    return(dimension);
  }

  int howManyNotDefinedVariable(int flag, void *ptr1, void *ptr2) {
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
      abortExit("Illegal dimension in SNpoint");
      break;
    }
    return(ret);
  }

  int howManyNotDefinedFunction(int flag, void *ptr1, void *ptr2) {
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
      abortExit("Illegal dimension in SNpoint");
      break;
    }
    return(ret);
  }

  int howManyNotAssignedVariable(int flag, void *ptr1, void *ptr2) {
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
      abortExit("Illegal dimension in SNpoint");
      break;
    }
    return(ret);
  }

  // CHECK functions 
  int evalCoordinate(ptrList <evalPair*>*);      // return 0 if success

                                                 // from mesh_point_enumerate
  void errWrtName(std::ostream &ost ) {
    ost << name;
    return;
  }

  void print(std::ostream & ost) {
    ost << "point ";
    ost <<  name;
    exprLst->print(ost);
  }

  void testWrtCoor(std::ostream &ost) {

    switch(dimension) {
    case 1:
      ost << "point ";
      ost <<  name;
      ost << "(" << xval <<")\n";
      break;
    case 2:
      ost << "point ";
      ost <<  name;
      ost << "(" << xval <<","<<yval<<")\n";
      break;
    case 3:
      ost << "point ";
      ost <<  name;
      ost << "(" << xval <<","<<yval<<","<<zval<<")\n";
      break;
    default:
      break;
    }
    return;
  }

  void getExprPrintX( char *buf,int flag,void *ptr1,void *ptr2 ) 
  {
    x->exprPrint(buf,flag,ptr1,ptr2);
    return;
  }

  int isAlreadyUsedName( list <string> &strLst) {
    if(strLst.includes(name)) {
      return(YES);
    }
    else {
      strLst.addlast(name);
      return(NO);
    }
  }

  // used in mesh_point_conflict
  void nameAddLastToStringLst( list <string> &strLst) {  
    strLst.addlast(name);
    return;
  }

  Point *MakePointObj(void);
  Point *MakePointObjWithName(void);

  
private:
  string  name;
  int     dimension;
  SNunit *exprLst;
  Expression *x,*y,*z;
  double  xval,yval,zval;

};


#endif
