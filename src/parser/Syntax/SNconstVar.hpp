/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNconstVar.hpp
 *  Date     : 2001/03/07
 *  Modified : 
 *  
 *  Purpose  : constVar class for parser  (reference aumc)
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

#ifndef FEM_SYNTAX_CONSTVAR
#define FEM_SYNTAX_CONSTVAR

#include "SNunit.hpp"
#include "SNidentifierlist.hpp"
#include "../../class/Expression.hpp"

class Variable;

class SNconstVar : public SNunit {
public:
  SNconstVar(const char *nm,  Expression *ptr);
  //    : SNunit("constVar",SN_CONSTVAR) {
  //
  //    name           = nm ;
  //    initialExprPtr = ptr;
  //  }

  void print(std::ostream & ost) {
    ost << "const " << name << " = ";
    initialExprPtr->print(ost);
  }

  void errWrtName(std::ostream &ost ) {
    ost << name;
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

  // CHECK function
  int CheckInitialValue(void);   // if no error, set initial value
  
  // InfoGenerate
  Variable *CreateVariablePtr(void);

private:
  string      name;
  Expression *initialExprPtr;
  double      initialValue;

};


#endif
