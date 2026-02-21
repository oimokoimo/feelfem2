/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : scheme_userfunc_arg_check.cpp
 *  Date     : 2002/09/17
 *  Modified : 
 *  
 *  Purpose  : Check number of arguments is valid for user 
 *             defined functions
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

#include "check_funcs.hpp"

#include "Object.hpp"
#include "feelfuncs.hpp"

#include "../parser/Syntax/SNfunction.hpp"
#include "Function.hpp"

int scheme_userfunc_arg_check(void)
{
  int errors = 0;

  listIterator <SNfunction *>itrsnf(feelfemobj.GetSNUserFunctionList());

  for(itrsnf.init(); !itrsnf; ++itrsnf) {
    int arguments   = itrsnf()->HowManyArguments();
    string funcname = itrsnf()->GetName();
    
    if(! feelfemobj.IsUsedUserFunctionName( funcname ) ) {
      // this should be error.(not defined function)
      continue;
    }
    
    // check arguments
    Function *funcPtr = feelfemobj.GetFunctionPtrByName( funcname );

    if(arguments != funcPtr->GetArguments()) {
      SystemErrorAStrA((SNunit *)(itrsnf()),
		       "number of arguments for ",funcname," is wrong.");
      errors++;
    }
  }
  return(errors);
}
