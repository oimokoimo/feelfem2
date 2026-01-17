/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNdoubleVar.hpp
 *  Date     : 2001/03/07
 *  Modified : 
 *  
 *  Purpose  : doubleVar class for parser  (reference aumc)
 *  
 */

#ifndef FEM_SYNTAX_DOUBLEVAR
#define FEM_SYNTAX_DOUBLEVAR

#include "SNunit.hpp"
#include "../../class/string.hpp"
#include "../../class/Expression.hpp"


class Variable;

class SNdoubleVar : public SNunit {
public:
  SNdoubleVar( char *nm )                   // nur declaration
    : SNunit("doubleVar",SN_DOUBLEVAR) {

    name           = nm;
    initialExprPtr = 0;

  }
  
  SNdoubleVar( char *nm ,Expression *ptr)   // with initialization
    : SNunit("doubleVar",SN_DOUBLEVAR) {    // also used as avsdouble etc.
 
    name           =  nm;
    initialExprPtr = ptr;

  }

  void print(ostream & ost) {
    ost << "double " << name;
    
    if(initialExprPtr) {
      ost << " = ";
      initialExprPtr->print(ost);
      ost << " [initial value specified]";
    }
  }

  void errWrtName(ostream &ost ) {
    ost << name;
    return;
  }

  // check functions
  int isAlreadyUsedName( list <string> &strLst) {
    if(strLst.includes(name)) {
      return(YES);
    }
    else {
      strLst.addlast(name);
      return(NO);
    }
  }

  int isDefined(void) {   return YES; }     // no dependency



  Variable *CreateVariablePtr(void);

  // CHECK function
  int CheckInitialValue(void);   // if no error, set initial value

private:
  string      name;
  Expression *initialExprPtr;
  double      initialValue;

};

#endif
