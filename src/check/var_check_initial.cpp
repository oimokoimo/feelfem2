/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : var_check_initial.cpp
 *  Date     : 2002/04/18 (BCN)
 *  Modified : 
 *  
 *  Purpose  : check initial value is numeric
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

#include <cassert>

#include "list.hpp"
#include "string.hpp"
#include "feelfuncs.hpp"

#include "check_funcs.hpp"

#include "../parser/Syntax/SNunit.hpp"
#include "../parser/Syntax/SNintVar.hpp"
#include "../parser/Syntax/SNdoubleVar.hpp"
#include "../parser/Syntax/SNconstVar.hpp"


int var_check_initial( list <void *>&parseVarLst )
{
  int errors,ret;

  errors    = 0;
  
  listIterator <void *>itrVar(parseVarLst);
  for(itrVar.init(); !itrVar; ++itrVar) {

    switch(((SNunit *)itrVar())->GetType()) {


    case SN_FEMVAR:
    case SN_EWISEVAR:
    case SN_MATERIALVAR:
      break;   

    case SN_INTVAR:
      {
	SNintVar *snivPtr = (SNintVar *)itrVar();
	ret = snivPtr->CheckInitialValue(); // set value
	if(ret) {
	  SystemErrorANameA(snivPtr,"Initial value of "," is not numeric.");
	  errors++;
	}
      }
      break;

    case SN_DOUBLEVAR:
      {
	SNdoubleVar *sndvPtr = (SNdoubleVar *)itrVar();
	ret = sndvPtr->CheckInitialValue(); // set value
	if(ret) {
	  SystemErrorANameA(sndvPtr,"Initial value of "," is not numeric.");
	  errors++;
	}
      }
      break;

    case SN_CONSTVAR:
      {
	SNconstVar *sncvPtr = (SNconstVar *)itrVar();
	ret = sncvPtr->CheckInitialValue(); // set value
	if(ret) {
	  SystemErrorANameA(sncvPtr,"Initial value of "," is not numeric.");
	  errors++;
	}
      }
      break;

    case SN_FUNCTIONDEF:
      break;

    default:
      assert(1==0);
      break;

    }
  }
  return(errors);
}
