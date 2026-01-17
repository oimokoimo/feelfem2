/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNmeshAssignment.hpp
 *  Date     : 2001/03/06
 *  Modified : 
 *  
 *  Purpose  : meshAssignment class for parser  (reference aumc)
 *  
 */

#ifndef FEM_SYNTAX_MESHASSIGNMENT
#define FEM_SYNTAX_MESHASSIGNMENT

#include "SNunit.hpp"
#include "../../class/string.hpp"
#include "../../class/feeldef.hpp"
#include "../../class/Expression.hpp"

class SNmeshAssignment : public SNunit {
public:
  SNmeshAssignment( char *nm, Expression *ptr) 
    :SNunit("meshAssignment",SN_MESHASSIGNMENT) 
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

  double  evalValue(ptrList <evalPair*>*, int &);  


  void errWrtName(ostream & ost ) {
    ost << leftVarName;
    return;
  }

  void print(ostream & ost) { 
    ost << leftVarName << " = ";
    exprPtr->print(ost);
  }
  friend class meshEvalGinac;
  


private:
  string  leftVarName;
  Expression *exprPtr;
};

#endif
