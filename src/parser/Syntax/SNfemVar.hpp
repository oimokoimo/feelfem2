/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNfemVar.hpp
 *  Date     : 2001/03/07
 *  Modified : 
 *  
 *  Purpose  : femVar class for parser  (reference aumc)
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

#ifndef FEM_SYNTAX_FEMVAR
#define FEM_SYNTAX_FEMVAR

#include "SNunit.hpp"
#include "SNidentifierlist.hpp"

class Variable;

class SNfemVar : public SNunit {
public:
  SNfemVar( const char *nm, const char *bnm) 
    : SNunit("femVar",SN_FEMVAR) {

    name        = nm ;
    elementName = bnm;

  }

  void print(std::ostream & ost) {
    ost << "fem " << name << "[" << elementName << "]";
  }

  
  void errWrtName(std::ostream &ost ) {
    ost << name;
    return;
  }
  
  void errWrtData(std::ostream &ost ) {
    ost << elementName;
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

  Variable *CreateVariablePtr(void);  

  int IsDefinedElement();

private:
  string  name;
  string  elementName;

};


#endif
