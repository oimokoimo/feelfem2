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
