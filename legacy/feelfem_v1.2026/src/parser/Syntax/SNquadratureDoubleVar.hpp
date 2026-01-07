/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNquadratureDoubleVar.hpp
 *  Date     : 2001/03/27
 *  Modified : 
 *  
 *  Purpose  : quadratureDoubleVar class for parser  (reference aumc)
 *  
 */

#ifndef FEM_SYNTAX_QUADRATUREDOUBLEVAR
#define FEM_SYNTAX_QUADRATUREDOUBLEVAR

#include "SNunit.hpp"
#include "../../class/string.hpp"
#include "../../class/Expression.hpp"
#include "../../class/ptrList.hpp"

#include "evalPair.hpp"

class SNquadratureDoubleVar : public SNunit {
public:
  SNquadratureDoubleVar( char *nm )                    // without initial value
    : SNunit("quadratureDoubleVar",SN_QUADRATUREDOUBLEVAR) {

    name           = nm;
    initialExprPtr =  0;
  }

  SNquadratureDoubleVar( char *nm ,Expression *ptr)    // without initial value
    : SNunit("quadratureDoubleVar",SN_QUADRATUREDOUBLEVAR) {

    name           =  nm;
    initialExprPtr = ptr;
  }

  int hasInitial(void)
  {
    if(initialExprPtr) {
      return(1);
    }
    else {
      return(0);
    }
  }

  int howManyNotDefinedVariable(int flag, void *ptr1, void *ptr2) {
    return(initialExprPtr->howManyNotDefinedVariable(flag,ptr1,ptr2));
  }

  int howManyNotDefinedFunction(int flag, void *ptr1, void *ptr2) {
    return(initialExprPtr->howManyNotDefinedFunction(flag,ptr1,ptr2));
  }

  int howManyNotAssignedVariable(int flag, void *ptr1, void *ptr2) {
    return(initialExprPtr->howManyNotAssignedVariable(flag,ptr1,ptr2));
  }

  int is_includes(list <string> &varLIST) {
    return(varLIST.includes(name));
  }

  void add_strlist( list <string> &varLIST) {
    varLIST.add(name);
  }

  void errWrtName(ostream & ost ) {
    ost << name;
    return;
  }

  void print(ostream & ost) {
    ost << "quadratureDouble " << name;
    if(initialExprPtr) {
      ost << "=" ;
      initialExprPtr->print(ost);
    }
  }


  //CHECK 
  evalPair *makeEvalPair(ptrList<evalPair *> *pairLstPtr);
  double    evalInitialValue(ptrList <evalPair*>*, int &);

  int isInitialValue(void)
  {
    if(initialExprPtr) {
      return(YES);
    }
    else {
      return(NO);
    }
  }
      
  void getExprPrintInitialExpr( char *buf,int flag,void *ptr1,void *ptr2)
  {
    initialExprPtr->exprPrint(buf,flag,ptr1,ptr2);
    return;
  }

private:
  string      name;
  Expression *initialExprPtr;

};


#endif
