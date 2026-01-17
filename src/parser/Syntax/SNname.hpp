/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999,2000
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SyntaxName.hpp
 *  Date     : 2000/11/28
 *  Modified : 2000/11/28
 *  
 *  Purpose  :
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

#ifndef FEM_SYNTAX_NAME
#define FEM_SYNTAX_NAME

#include "../../class/string.hpp"

class SNname  {

public:
  SNname( char * );
  ~SNname();

  int LineNumber() { return lineNumber; }
  void LineNumber(int n) { lineNumber = n; }

  void print(std::ostream &ost) { ost << name ; }

  const char *GetName() { return(name); }
  operator const char *() const ;


private:
  int lineNumber;
  string name;
};

#endif
