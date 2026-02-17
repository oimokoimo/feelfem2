/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNmaterialVar.hpp
 *  Date     : 2002/08/29   (copy from SNewiseVar.hpp)
 *  Modified : 
 *  
 *  Purpose  : materialVar class for parser  (reference aumc)
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

#ifndef FEM_SYNTAX_MATERIALVAR
#define FEM_SYNTAX_MATERIALVAR

#include <iostream>
#include "stack.hpp"
#include "string.hpp"

#include "SNunit.hpp"


class SNoption;
class Variable;
class SNunit;

class SNmaterialVar : public SNunit {
public:
  SNmaterialVar(const char *   ,stack <SNunit *> &) ;

  void print(std::ostream & ost);
  
  void errWrtName(std::ostream &ost ) {
    ost << name;
    return;
  }

  void errWrtData(std::ostream &ost ) {
    return;
  }

  // check routines
  int isAlreadyUsedName( list <string> &strLst) {
    if(strLst.includes(name)) {
      return(YES);
    }
    else {
      strLst.addlast(name);
      return(NO);
    }
  }

  int IsValidAttribute(void);
  int CheckPairs(void);
  int CheckRegions(void);

  Variable *CreateVariablePtr(void);

private:
  string  name;
  int               options;
  list <SNoption *> optionLst;

  int               pairs;
  double           *values;   // allocate and set at SNmaterialVar_CHECK.cpp

};


#endif
