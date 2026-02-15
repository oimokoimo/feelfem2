/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNmaterialVar.hpp
 *  Date     : 2002/09/12
 *  Modified : 
 *  
 *  Purpose  : function definition
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

#ifndef FEM_SYNTAX_FUNCTIONDEF
#define FEM_SYNTAX_FUNCTIONDEF

#include "stack.hpp"
#include "string.hpp"

#include "SNunit.hpp"
#include "SNidentifierlist.hpp"


class SNfunctionDef : public SNunit {
public:
  SNfunctionDef( const char *nm , SNidentifierlist *ptr) ;


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

  int GetNumberOfArgs();

  // check routines
  virtual int Check(void);

  // InfoGenerate/*
  virtual int InfoGenerate(void);

private:
  string                name;
  SNidentifierlist     *identifierLst;
  int                   arguments;
};


#endif
