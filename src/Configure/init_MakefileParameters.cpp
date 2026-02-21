/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : init_MakefileParameters.cpp
 *  Date     : 2002/03/07
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

#include "Configure.hpp"
#include "feeldef.hpp"

void Configure::init_MakefileParameters()
{
  additionalEnvironmentFlag = NO;

  f90_compiler      = DEFAULT_F90_COMPILER;
  f77_compiler      = DEFAULT_F77_COMPILER;
  cpp_compiler      = DEFAULT_CPP_COMPILER;
  c_compiler        = DEFAULT_C_COMPILER;
  
  feelfem_basic_pde = FEELFEM_PREDEFINED_PDE;

  return;
}
