/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : feelfem.cpp
 *  Date     : 1999/10/26
 *  Modified : 2001/03/08
 *  
 *  Purpose  : main routine feelfem
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

#include <iostream>
#include "feelfem.hpp"

void check(void);        // check function
//void info(void);         // information generate
void discretize(void);   // discretization
void mesh(void);         // mesh generation

void code(void);         // code generation
void makefile(void);     // make makefile
void web(void);          // web post process

void feelfem(void)
{

  NOTE("GOTO check() in feelfem.cpp");
  check();

//  NOTE("GOTO info() in feelfem.cpp");
//  info();        // generate classes for each scheme/element/quadrature object

  NOTE("GOTO discretize() in feelfem.cpp");
  discretize();  // in Discretization/discretize.cpp

  //  make_datafile();
  NOTE("GOTO mesh() in feelfem.cpp");
  mesh();        // in Mesh/mesh.cpp

  NOTE("GOTO code() in feelfem.cpp");
  code();        // in CodeGenerator/CodeGeneratorMain.cpp

  NOTE("GOTO makefile() in feelfem.cpp");
  makefile();    // in MakeMakefile/makefile.cpp

  NOTE("GOTO web() in feelfem.cpp");
  web();

  return;
}

