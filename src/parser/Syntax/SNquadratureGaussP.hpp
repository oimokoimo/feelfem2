/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNquadratureGaussP.hpp
 *  Date     : 2001/02/23
 *  Modified : 2001/03/25
 *  
 *  Purpose  : quadratureGaussP class for parser  (reference aumc)
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

#ifndef FEM_SYNTAX_QUADRATUREGAUSSP
#define FEM_SYNTAX_QUADRATUREGAUSSP

#include "SNunit.hpp"
#include "SNexprlist.hpp"
#include "../../class/string.hpp"
#include "../../class/Expression.hpp"

class SNquadratureGaussP : public SNunit {
public:
  SNquadratureGaussP( SNunit *exlstPtr, Expression *ptr) 
    : SNunit("quadratureGaussP",SN_QUADRATUREGAUSSP) {

    SNexprlist *asExprlistPtr;
    asExprlistPtr = (SNexprlist *)exlstPtr;

    exprlistPtr = asExprlistPtr;         // coordinate
    weightExprPtr     = ptr;                   // weight 

    dimension = asExprlistPtr->howManyElements();

    xval = 911.0;
    yval = 911.0;
    zval = 911.0;

    weight = 911.0;


    // set coordinate expression ptr
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
      abortExit("Illegal dimension in SNquadratureGaussP");
      break;
    }

    ret+= weightExprPtr ->howManyNotDefinedVariable(flag,ptr1,ptr2);

    
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
      abortExit("Illegal dimension in SNquadratureGaussP");
      break;
    }

    ret+=  weightExprPtr->howManyNotDefinedFunction(flag,ptr1,ptr2);

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
      abortExit("Illegal dimension in SNquadratureGaussP");
      break;
    }

    ret += weightExprPtr->howManyNotAssignedVariable(flag,ptr1,ptr2);
    return(ret);

    
  }

  //  int evalCoordinate(ptrList <evalPair*>*);      // return 0 if success
  //  int evalWeight(ptrList <evalPair*>*);          // return 0 if success

  void print(std::ostream & ost) {
    exprlistPtr->print(ost);
    ost << "[" << dimension << "]:" ;
    weightExprPtr->print(ost);
  }

  void testWrtCoor(std::ostream &ost) {

    switch(dimension) {
    case 1:
      ost << "quadratureGaussP ";
      ost << "(" << xval <<")\n";
      break;
    case 2:
      ost << "quadratureGaussP ";
      ost << "(" << xval <<","<<yval<<")\n";
      break;
    case 3:
      ost << "quadratureGaussP ";
      ost << "(" << xval <<","<<yval<<","<<zval<<")\n";
      break;
    default:
      break;
    }
    return;
  }

  // evaluation with ginac
  int evalCoordinateAndWeight(ptrList <evalPair*>*);  // return 0 if success

  void getCoordinate( double &xx                        ) 
  { xx = xval;  return;}
  void getCoordinate( double &xx ,double &yy            )
  { xx = xval;  yy = yval; return;}
  void getCoordinate( double &xx ,double &yy, double &zz)
  { xx = xval;  yy = yval;  zz = zval; return;}

  double getWeight(void) { return weight; }


  void getExprPrintX( char *buf,int flag,void *ptr1,void *ptr2 ) 
  {
    x->exprPrint(buf,flag,ptr1,ptr2);
    return;
  }


private:
  int     dimension;
  SNexprlist *exprlistPtr;

  Expression *x,*y,*z;
  double  xval,yval,zval;

  Expression *weightExprPtr;
  double  weight;

};

#endif
