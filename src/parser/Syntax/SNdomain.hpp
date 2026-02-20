/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNdomain.hpp
 *  Date     : 2001/02/27
 *  Modified : 
 *  
 *  Purpose  : domain class for parser  (reference aumc)
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

#ifndef FEM_SYNTAX_DOMAIN
#define FEM_SYNTAX_DOMAIN

#include "SNunit.hpp"
#include "../../class/string.hpp"

class SNdomain : public SNunit {
public:
  SNdomain(const char *nm, SNunit *rptr) 
    : name(nm),regionLst(rptr),SNunit("domain",SN_DOMAIN) {
    return;
  }

  void print(std::ostream & ost) {
    ost << "domain ";
    ost <<  name;
    regionLst->print(ost);
    return;
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
  SNunit *regionLst;

};


#endif
