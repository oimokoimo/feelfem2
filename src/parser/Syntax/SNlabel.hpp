/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNlabel.hpp
 *  Date     : 2001/08/23
 *  Modified : 
 *  
 *  Purpose  : label class for parser  (reference aumc)
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
 *  
 */

#ifndef FEM_SYNTAX_LABEL
#define FEM_SYNTAX_LABEL

#include "SNunit.hpp"

#include "list.hpp"
#include "string.hpp"

#include "Label.hpp"

class Main;

class SNlabel : public SNunit {
public:
  SNlabel(char *name) : SNunit("label",SN_LABEL) 
  { val = name; }

  void print(std::ostream & ost) { ost <<  "LABEL ["<< val << "]"; }

  // check functions
  int duplicate_check(list <string> &);
  
  // Information generator
  int InfoGenerate(void);

  //  void CodeGenerate(void);
  void CodeGenerate(void);
  void CodeGenerateMain(void *,Main *);

private:
  string val;
  Label  *labelPtr;

};


#endif
