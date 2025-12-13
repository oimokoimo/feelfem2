/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : scheme_solve_geom_create.cpp
 *  Date     : 2002/03/21
 *  Modified : 
 *  
 *  Purpose  : solve geometry create
 *             generate bounary geometry
 *  
 */

// main routine scheme_solve_geom_create() is at the bottom.

#include <iostream.h>
#include "feelfem.hpp"              // for command options
#include "check_funcs.hpp"          // for error messages

#include "parseExternals.hpp"       // for parser  treesn


#include "../parser/Syntax/SNunit.hpp"
#include "../parser/Syntax/SNsolve.hpp"

int scheme_solve_geom_create(list <void *>&parseSchemeLst)
{
  int ret,errors;

  errors = 0;

  listIterator <void *>itr(parseSchemeLst);
  for(itr.init(); !itr ; ++itr) {

    SNunit *uPtr =(SNunit *)itr();

    SNsolve *snSolvePtr;

    switch(uPtr->GetType()) {
    case SN_SOLVE:

      snSolvePtr = (SNsolve *)itr();
      // errors += snSolvePtr->RegionGeometryCreate();  // not yet.
      errors += snSolvePtr->BoundaryGeometryCreate();

      break;

    default:
      break;
    }
  }
  return(errors);
}
