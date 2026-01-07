/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : scheme_solve_check.cpp
 *  Date     : 2001/09/04
 *  Modified : 
 *  
 *  Purpose  : scheme info generate
 *            (Generate a corresponding class for each syntax object)
 *  
 */

// main routine scheme_solve_check() is at the bottom.

#include <iostream.h>

#include "feelfem.hpp"              // for command options

#include "parseExternals.hpp"       // for parser  trees


#include "../parser/Syntax/SNunit.hpp"
#include "../parser/Syntax/SNsolve.hpp"

int scheme_info_generate(list <void *>&parseSchemeLst)
{
  int ret,errors;

  errors = 0;

  NOTE("scheme_info_generate starts...");

  listIterator <void *>itr(parseSchemeLst);
  for(itr.init(); !itr ; ++itr) {

    SNunit *uPtr =(SNunit *)itr();

    switch(uPtr->GetType()) {
    case SN_SOLVE:
      ret = ((SNsolve*)uPtr)->InfoGenerate();
      errors += ret;

      break;

    default:

      break;
    }

  }

  return(errors);
}
