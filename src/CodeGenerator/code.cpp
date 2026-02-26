/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : code.cpp
 *  Date     : 2001/05/07
 *  Modified : 
 *  
 *  Purpose  : code generation section main routine
 *             called from main/feelfem.cpp
 *
 *
 *  feelfem2 (modernized/ported)
 *  Copyright (C) 2025-2026 Hidehiro Fujio and contributors
 *  SPDX-License-Identifier: BSD-3-Clause
 *  Repository: https://github.com/oimokoimo/feelfem2
 *
 *
 *  Notes:
 */

#include "feelfem.hpp"
#include "Main.hpp"

void codeGenerateMain(Main *);
void codeGenerateSubroutines(void);

void code(void)
{
  Main *mainPtr = new Main();  // class Main will be generated from
                               // Object *feelfemobj and Procedure *feelfemproc
                               // in the default constructor

  // Generate main routine
  NOTE("code.cpp codeGenerateMain");
  codeGenerateMain(mainPtr);

  // Generate subroutines
  NOTE("code.cpp codeGenerateSubroutine");
  codeGenerateSubroutines();

  return;
}  
