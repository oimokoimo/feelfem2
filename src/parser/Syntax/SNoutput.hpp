/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNoutput.hpp
 *  Date     : 2002/01/18
 *  Modified : 
 *  
 *  Purpose  : parse data for output
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

#ifndef FEM_SYNTAX_OUTPUT
#define FEM_SYNTAX_OUTPUT

#include "stack.hpp"         // use stack (list)
#include "string.hpp"

#include "SNunit.hpp"
#include "SNexprlist.hpp"
#include "SNidentifierlist.hpp"

#include "Output.hpp"

class SNoption;
class Main;

class SNoutput : public SNunit {
public:
  SNoutput(SNidentifierlist *) ;
  SNoutput(SNidentifierlist *,stack <SNunit *> &) ;

  void print(std::ostream & ) ;

  // check functions
  int checkIdentifierWellDefined(void);
  int checkValidExpr(void);
  int checkOptions(void);

  // InfoGenerate
  int InfoGenerate();

  // CodeGenerator
  void CodeGenerateMain(void *,Main *);
  void CodeGenerate(void);

private:

  SNidentifierlist  *snIdentifierlistPtr;
  int                options;
  list <SNoption *>  optionLst;

  int                components;
  list <string>      identifierStrLst;

  Output            *outputPtr;

};

#endif
