/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNassignment_CodeGenerator.cpp
 *  Date     : 2001/08/23
 *  Modified : 
 *  
 *  Purpose  : Code generator for assignment family
 *  
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

#include <iostream>
#include "SNassignment.hpp"

#include "Assign.hpp"
#include "Main.hpp"

#include "CodeGenerators.hpp"

void SNassignment::CodeGenerate(void)
{
  // temporary implementation


  switch(asPtr->GetLeftVarAssignType()) {
  case AS_VAR_TYPE_SCALAR:
    //  case AS_VAR_TYPE_INTEGER:
    //  case AS_VAR_TYPE_DOUBLE:
  case AS_VAR_TYPE_FEM_NODE:
  case AS_VAR_TYPE_EWISE_M:
    cg_AssignmentScalar( asPtr );
    break;

  case AS_VAR_TYPE_EWISE_G:
    cg_AssignmentEwiseQuad( asPtr );
    break;

  case AS_VAR_TYPE_DOUBLE_INTEGRAL:
    cg_AssignmentIntegral( asPtr );
    break;

  default:
    std::cerr <<"NOT SUPPORT for AS_VAR_TYPE " << asPtr->GetLeftVarAssignType()
	 <<" SNassignment_CodeGenerator.cpp" << std::endl;
    assert(1==0);
  }

  return;
}

