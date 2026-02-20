/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNwrite.hpp
 *  Date     : 2002/11/21
 *  Modified : 
 *  
 *  Purpose  : parse for write
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

#ifndef FEM_SYNTAX_WRITE
#define FEM_SYNTAX_WRITE

#include "stack.hpp"         // use stack (list)
#include "string.hpp"

#include "SNunit.hpp"
#include "SNexprlist.hpp"
#include "SNidentifierlist.hpp"

#include "Write.hpp"

class SNoption;
class Main;

class SNwrite : public SNunit {
public:
  SNwrite(stack <SNunit *> &) ;
  void print(std::ostream & ) ;

  // check functions
  int checkItems(void);

  // InfoGenerate
  int InfoGenerate();

  // CodeGenerator
  void CodeGenerateMain(void *,Main *);
  void CodeGenerate(void);

private:

  int items;
  list <SNunit *>writeSNunitPtrLst;

  Write *writePtr;

};

#endif
