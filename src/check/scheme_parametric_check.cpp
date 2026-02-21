/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : scheme_parametric_check.cpp
 *  Date     : 2002/07/11
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

#include "feelfem.hpp"              // for command options
#include "feelfuncs.hpp"
#include "check_funcs.hpp"          // for error messages

#include "parseExternals.hpp"       // for parser  trees


#include "../parser/Syntax/SNunit.hpp"
#include "../parser/Syntax/SNparametric.hpp"



static int check_parametric(SNparametric *snParametricPtr)
{
  if(snParametricPtr->IsValidParametricName()) {
    //    snParametricPtr->set_feelfemobj();    // this is also included
    return( 0 );  // name is defined, no error
  }
  else {
    // error messages are out in check routine

    return( 1 );  // name is undefined, error
  }
  
}


int scheme_parametric_check(list <void *>&parseSchemeLst)
{
  int ret,errors;

  errors = 0;

  listIterator <void *>itr(parseSchemeLst);
  for(itr.init(); !itr ; ++itr) {

    SNunit *uPtr =(SNunit *)itr();

    switch(uPtr->GetType()) {
    case SN_PARAMETRIC:
      ret = check_parametric( (SNparametric *)(itr()) );  // in the top
      errors += ret;

      break;

    default:
      break;
    }
  }
  return(errors);
}

