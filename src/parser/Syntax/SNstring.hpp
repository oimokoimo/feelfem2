/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999,2000
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNstring.hpp    
 *  Date     : 2002/11/21
 *  Modified : 2002/11/21
 *  
 *  Purpose  : for Write sentences
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

#ifndef FEM_SYNTAX_STRING
#define FEM_SYNTAX_STRING

#include "SNunit.hpp"

#include "../../class/string.hpp"

class SNstring :public SNunit {

public:
  SNstring( const char * );
  ~SNstring();

  int LineNumber() { return lineNumber; }
  void LineNumber(int n) { lineNumber = n; }

  void print(std::ostream &ost) { ost << (const char *)str ; }

  const char *GetString() { return(str); }
  operator const char *() const ;


private:
  int lineNumber;
  string str;
};

#endif
