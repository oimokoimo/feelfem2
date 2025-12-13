/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNquadratureAssignment.hpp
 *  Date     : 2001/03/27
 *  Modified : 
 *  
 *  Purpose  : quadratureAssignment class for parser  (reference aumc)
 *  
 */

#ifndef FEM_SYNTAX_QUADRATUREASSIGNMENT
#define FEM_SYNTAX_QUADRATUREASSIGNMENT

#include "SNunit.hpp"
#include "../../class/string.hpp"
#include "../../class/feeldef.hpp"
#include "../../class/Expression.hpp"

class quadratureEvalGinac;

class SNquadratureAssignment : public SNunit {
public:

  friend quadratureEvalGinac;   // to access leftVarName


  SNquadratureAssignment( char *nm, Expression *ptr) 
    :SNunit("quadratureAssignment",SN_QUADRATUREASSIGNMENT) 
  { 
    leftVarName = nm; 
    exprPtr        = ptr;

    return;
  }

  int howManyNotDefinedVariable(int flag, void *ptr1, void *ptr2) {
    return(exprPtr->howManyNotDefinedVariable(flag,ptr1,ptr2));
  }

  int howManyNotDefinedFunction(int flag, void *ptr1, void *ptr2) {
    return(exprPtr->howManyNotDefinedFunction(flag,ptr1,ptr2));
  }

  int howManyNotAssignedVariable(int flag, void *ptr1, void *ptr2) {
    return(exprPtr->howManyNotAssignedVariable(flag,ptr1,ptr2));
  }

  // CHECK
  double  evalValue(ptrList <evalPair*>*, int &);  


  void errWrtName(ostream & ost ) {
    ost << leftVarName;
    return;
  }

  void print(ostream & ost) { 
    ost << leftVarName << " = ";
    exprPtr->print(ost);
  }
  

private:
  string  leftVarName;
  Expression *exprPtr;
};

#endif
