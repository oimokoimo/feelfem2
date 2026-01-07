/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNelementDoubleVar.hpp
 *  Date     : 2001/03/26
 *  Modified : 
 *  
 *  Purpose  : elementDoubleVar class for parser  (reference aumc)
 *  
 */

#ifndef FEM_SYNTAX_ELEMENTDOUBLEVAR
#define FEM_SYNTAX_ELEMENTDOUBLEVAR

#include "SNunit.hpp"
#include "../../class/string.hpp"
#include "../../class/Expression.hpp"
#include "../../class/ptrList.hpp"

class SNelementDoubleVar : public SNunit {
public:
  SNelementDoubleVar( char *nm )                    // without initial value
    : SNunit("elementDoubleVar",SN_ELEMENTDOUBLEVAR) {

    name           = nm;
    initialExprPtr =  0;
  }

  SNelementDoubleVar( char *nm ,Expression *ptr)    // without initial value
    : SNunit("elementDoubleVar",SN_ELEMENTDOUBLEVAR) {

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

  // expression check
  int howManyNotDefinedVariable(int flag, void *ptr1, void *ptr2);
  int howManyNotDefinedFunction(int flag, void *ptr1, void *ptr2);
  int howManyNotAssignedVariable(int flag, void *ptr1, void *ptr2);

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
    ost << "elementDouble " << name;
    if(initialExprPtr) {
      ost << "=" ;
      initialExprPtr->print(ost);
    }
  }

  // CHECK
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

  // check routine 
  int CheckSystemVariables( int etype );  // element type


private:
  string      name;
  Expression *initialExprPtr;

};

#endif
