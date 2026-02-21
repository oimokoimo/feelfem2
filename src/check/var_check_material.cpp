/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : var_check_material.cpp
 *  Date     : 2002/08/30
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

#include <cassert>

#include "list.hpp"
#include "string.hpp"
#include "feelfuncs.hpp"

#include "check_funcs.hpp"

#include "../parser/Syntax/SNunit.hpp"
#include "../parser/Syntax/SNmaterialVar.hpp"


int var_check_material( list <void *>&parseVarLst,
		        list <SNunit *>&parseGeomLst )
{
  int errors,ret;

  errors    = 0;
  
  listIterator <void *>itrVar(parseVarLst);
  for(itrVar.init(); !itrVar; ++itrVar) {

    switch(((SNunit *)itrVar())->GetType()) {

    case SN_FEMVAR:
    case SN_EWISEVAR:
    case SN_INTVAR:
    case SN_DOUBLEVAR:
    case SN_CONSTVAR:

    case SN_FUNCTIONDEF:
      break;   

    case SN_MATERIALVAR:
      {
	SNmaterialVar *snmvPtr = (SNmaterialVar *)itrVar();
	ret = snmvPtr->CheckPairs(); // check pairs
	if(ret) {
	  errors++;
	}

	ret = snmvPtr->CheckRegions(); // check region consistency
	if(ret) {
	  errors++;
	}

      }
      break;

    default:
      assert(1==0);
      break;
    }
  }
  return(errors);
}
