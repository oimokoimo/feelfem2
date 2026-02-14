/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNelementIntp.hpp
 *  Date     : 2001/02/23
 *  Modified : 2001/03/25
 *             2002/01/08 Node class related implementation
 *  
 *  Purpose  : elementIntp class for parser  (reference aumc)
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

#ifndef FEM_SYNTAX_ELEMENTINTP
#define FEM_SYNTAX_ELEMENTINTP

#include "SNunit.hpp"
#include "SNexprlist.hpp"

#include "string.hpp"
#include "Expression.hpp"

#include "Node.hpp"

class Node;
class Interpolation;

class SNelementIntp : public SNunit {
public:

  // nodal Interpolation (the constructor with typeName follows this)
  SNelementIntp( SNunit *exlstPtr, Expression *ptr);

  // constructor with type specifier
  SNelementIntp( SNunit *exlstPtr, char *typnm ,Expression *ptr) ;

  // set etype
  void setEtype(int e) {   // set etype (called from SNelement_CHECK.cpp)
    etype = e;
    return;
  }

  // Inquire functions
  int getSpaceDimension(void) {
    return(dimension);
  }

  int howManyNotDefinedVariable (int flag, void *ptr1, void *ptr2);
  int howManyNotDefinedFunction (int flag, void *ptr1, void *ptr2);
  int howManyNotAssignedVariable(int flag, void *ptr1, void *ptr2);

  // CHECK functions
  int evalCoordinate(ptrList <evalPair*>*);      // return 0 if success
  int checkTypeAttribute(void);                  // check "nodal, etc.

  // InfoGenerate (in SNelement_InfoGenerate.cpp)
  Interpolation *GenerateInterpolationDat();
  

  void errWrtName(std::ostream &ost ) {
    ost << typeName;
    return;
  }  

  // debug functions
  void print(std::ostream & ost) {
    exprlistPtr->print(ost);
    ost << "[" << dimension << "(" << type << ")" << "]:" ;
    exprPtr->print(ost);
  }
  
  void printEvaluatedCoor(void) {
	  std::cerr << "(";
    switch(dimension) {
    case 1:
      std::cerr << xval << ")\n";
      break;
    case 2:
      std::cerr << xval << "," << yval <<")\n";
      break;
      
    case 3:
      std::cerr << xval << "," << yval << "," << zval <<")\n";
      break;
    }
    return;
  }

  Node *generateNodeClass(void);


  void testWrtCoor(std::ostream &ost) {

    switch(dimension) {
    case 1:
      ost << "elementIntp ";
      ost << "(" << xval <<")\n";
      break;
    case 2:
      ost << "elementIntp ";
      ost << "(" << xval <<","<<yval<<")\n";
      break;
    case 3:
      ost << "elementIntp ";
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

private:
  int         dimension;
  int         etype;          // element type (set in SNelement_CHECK.cpp)
  int         type;           // for Hermite element, vector element, face ele
  string      typeName;
  SNexprlist *exprlistPtr;

  Expression *x,*y,*z;        // node coordinate in reference element
  double  xval,yval,zval;

  Expression *exprPtr;        // interpolation function

};

#endif
