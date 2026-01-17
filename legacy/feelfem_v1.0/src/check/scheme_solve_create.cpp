/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : scheme_solve_create.cpp
 *  Date     : 2002/01/10
 *  Modified : 
 *  
 *  Purpose  : Generate Solve class, etc.
 *  
 */

#include <iostream.h>

#include "feelfem.hpp"              // for command options
#include "check_funcs.hpp"          // for error messages

#include "parseExternals.hpp"       // for parser  trees

#include "../parser/Syntax/SNunit.hpp"
#include "../parser/Syntax/SNsolve.hpp"


int scheme_solve_create(list <void *>&parseSchemeLst)
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

      errors += snSolvePtr->InfoGenerate();
      break;

    default:
      break;
    }
  }
  return(errors);
}
