/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNassignment.hpp
 *  Date     : 2001/03/06
 *  Modified : 
 *  
 *  Purpose  : assignment class for parser  (reference aumc)
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

#ifndef FEM_SYNTAX_ASSIGNMENT
#define FEM_SYNTAX_ASSIGNMENT

#include <iostream>

#include "SNunit.hpp"
#include "SNidentifierlist.hpp"
#include "../../class/string.hpp"
#include "../../class/feeldef.hpp"
#include "../../class/Expression.hpp"

class Assign;

class SNassignment : public SNunit {
public:

  // normal one
  SNassignment( char *nm, Expression *ptr);

  // only for integral, and bintegral
  SNassignment( char *nm, Expression *ptr, int);

  // with integration method
  SNassignment( char *nm, char *quad,Expression *ptr, int);

  // for at,on,in specification
  SNassignment( char *nm, Expression *ptr,int place,SNidentifierlist *lstPtr);



  // for Where condition
  SNassignment( char *nm, Expression *ptr, int place, Expression *whereCond);

  // check print routine
  void print(std::ostream & ost);

  // CHECK family
  void errWrtName(std::ostream &ost) {
    ost << leftVarName;
    return;
  }
  int checkExprWellDefined(void); // all identifiers, function are defined?
  int checkGeometryIsValid(void); // if geometry is specified, check validity

  int checkValidExpr(void);       // is valid assignment combination?
  int checkValidQuadrature(void); // is valid quadrature integral and bintegral
                                  
  // InfoGenerate
  virtual int InfoGenerate();     //called from check/scheme_assign_create.cpp

  // Code generator
  void CodeGenerate(void);                // Code generator
  void CodeGenerateMain(void *,Main *);   // code generator for main routine

  Assign *GetAssignPtr(void) {
    return asPtr;
  }

private:
  string  leftVarName;
  string  integrationMethod;
  Expression *exprPtr;

  int integralType;             // ASSIGNMENT_TYPE_ORIGINAL
                                // ASSIGNMENT_TYPE_INTEGRAL
                                // ASSIGNMENT_TYPE_BINTEGRAL

  int refEtypeIntegral;
  int refEtypeBintegral;

  // check valid privates
  int checkValidExpr_FEM(void);
  int checkValidExpr_EWISE(void);
  int checkValidExpr_EWISE_A(void);
  int checkValidExpr_DOUBLE(void);
  int checkValidExpr_INT(void);

  // integral,bintegral
  int checkValidExpr_INTEGRAL(void);

  int     placeFlag;             // SN_ASSIGNMENT_NORMAL
                                 // SN_ASSIGNMENT_AT
                                 // SN_ASSIGNMENT_ON
                                 // SN_ASSIGNMENT_IN
                                 // SN_ASSIGNMENT_WHERE
  SNidentifierlist *placeLst;
  Expression *condExprPtr;

  Assign *asPtr;                 // made in SNassignment_InfoGenerate.cpp

};

#endif
