/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNintVar.hpp
 *  Date     : 2001/03/07
 *  Modified : 
 *  
 *  Purpose  : intVar class for parser  (reference aumc)
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

#ifndef FEM_SYNTAX_INTVAR
#define FEM_SYNTAX_INTVAR

#include "SNunit.hpp"
#include "../../class/string.hpp"
#include "../../class/Expression.hpp"

class Variable;

class SNintVar : public SNunit {
public:
  SNintVar( char *nm )                   // nur declaration
    : SNunit("intVar",SN_INTVAR) {

    name           = nm;
    initialExprPtr = 0;

  }
  
  SNintVar( char *nm ,Expression *ptr)   // with initialization
    : SNunit("intVar",SN_INTVAR) {    // also used as avsint etc.
 
    name           =  nm;
    initialExprPtr = ptr;

  }

  void print(std::ostream & ost) {
    ost << "int " << name;
    
    if(initialExprPtr) {
      ost << " = ";
      initialExprPtr->print(ost);
      ost << " [initial value specified]";
    }
  }
  
  void errWrtName(std::ostream &ost ) {
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

  int isDefined() {   return YES; }     // no dependency

  Variable *CreateVariablePtr(void);

  // CHECK function
  int CheckInitialValue(void);          // if no error, set initial value

private:
  string      name;
  Expression *initialExprPtr;
  int         initialValue;

};

#endif
