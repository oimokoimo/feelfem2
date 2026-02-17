/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNoption.hpp
 *  Date     : 2002/01/18
 *  Modified : 
 *  
 *  Purpose  : option parser
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

#ifndef FEM_SYNTAX_OPTION
#define FEM_SYNTAX_OPTION

#include "feeldef.hpp"

#include "SNunit.hpp"
#include "string.hpp"
#include "Expression.hpp"

class SNmaterialVar;

class SNoption : public SNunit {
public:
  SNoption( const char *nm, Expression *ptr);    // with expression
  SNoption( const char *nm, char       *opt);    // with string

  // check print routine
  void print(std::ostream & ost);

  friend class SNmaterialVar;

  string &GetOptionName(void) { return optionIdentifier; }
  void    GetValueAsString(string &);

  Expression *GetExprPtr(void);

private:
  string  optionIdentifier;
  string  optionString;

  Expression *exprPtr;

};


#endif
