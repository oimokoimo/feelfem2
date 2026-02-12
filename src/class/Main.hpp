/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : Main.hpp
 *  Date     : 2000/04/25
 *  Modified : 2001/05/22
 *  
 *  Purpose  : Main progam information for generating main routine
 *             This class is generated in the default constructor
 *             called from CodeGenerator/code.cpp from feelfemobj
 *             and feelfemproc.
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

#ifndef FEM_CLASS_MAIN
#define FEM_CLASS_MAIN

#include "list.hpp"
#include "orderedPtrList.hpp"
#include "Variable.hpp"

//class Expression;
//class Scheme;

class Main {
public:
  Main();
  ~Main();

  //  void AddScheme(Scheme *);

  int getProgramModelType(void) { return programModelType; }

  void AddVariablePtr( Variable *);

  orderedPtrList <Variable *>& GetVarPtrList(void) {
    return( mainVarPtrLst );
  }

private:
  
  int programModelType;

  orderedPtrList <Variable *> mainVarPtrLst;

  //  list <Scheme *> schemePtrLst;
  

};

#endif

