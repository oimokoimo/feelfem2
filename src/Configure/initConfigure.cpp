/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : initConfigure.cpp
 *  Date     : 2001/08/20
 *  Modified : 
 *  
 *  Purpose  : allocate feelfemconf object
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

Configure feelfemconf;          // extern declaration in feelfuncs.hpp

Configure::Configure()          // constructor
{

  // Store Program Model Names
  init_StoreProgramModels();

  // Store Solver Libraries
  init_StoreSolverLibraries();


  /*=============================================*/
  /* Store default solver for each program model */
  /*=============================================*/
  init_DefaultSolveParameters();

  
  // compilers
  init_MakefileParameters();

  // geom obj
  init_StoreGeomObj();


  read_ResourceFile();

  return;
}
