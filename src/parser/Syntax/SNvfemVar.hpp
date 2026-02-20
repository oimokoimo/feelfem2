/*
 *  feelvfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNvfemVar.hpp
 *  Date     : 2001/03/07
 *  Modified : 
 *  
 *  Purpose  : vfemVar class for parser  (reference aumc)
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

#ifndef FEM_SYNTAX_VFEMVAR
#define FEM_SYNTAX_VFEMVAR

#include "SNunit.hpp"
#include "SNidentifierlist.hpp"

class SNvfemVar : public SNunit {
public:
  SNvfemVar( const char *nm,  const char *bnm) 
    : SNunit("vfemVar",SN_VFEMVAR) {

    name        = nm ;
    elementName = bnm;

  }

  void print(std::ostream & ost) {
    ost << "vfem " << name << "[" << elementName << "]";
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
  

private:
  string  name;
  string  elementName;

};


#endif
