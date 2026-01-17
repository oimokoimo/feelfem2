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
