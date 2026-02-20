/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNsolve_CodeGenerate.cpp
 *  Date     : 2001/08/22
 *  Modified : 
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

#include "feeldef.hpp"

#include "SNsolve.hpp"
#include "../../class/Solve.hpp"
#include "../../class/feelfuncs.hpp"

#include "CodeGenerators.hpp"   // declaration of cg_Normal...

void SNsolve::CodeGenerate(void)
{

  if(solvePtr->GetNonlinearFlag() == YES) {
    cg_NormalNonlinearProblem( solvePtr );
  }
  else {
    cg_NormalLinearProblem( solvePtr );
  }
  return;
}
