/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : var_check_defined.cpp
 *  Date     : 2001/11/05
 *  Modified : 
 *  
 *  Purpose  : check fem, vfem and ewise variable definition
 *            (specified name is really defined or not)
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

#include <iostream>
#include <cassert>

#include "list.hpp"
#include "string.hpp"
#include "feelfuncs.hpp"

#include "check_funcs.hpp"

#include "../parser/Syntax/SNunit.hpp"
#include "../parser/Syntax/SNfemVar.hpp"
#include "../parser/Syntax/SNewiseVar.hpp"


int var_check_defined( list <void *>&parseVarLst )
{
  listIterator <void *>itrVar(parseVarLst);

  int errors;

  errors    = 0;
  
  for(itrVar.init(); !itrVar; ++itrVar) {

    switch(((SNunit *)itrVar())->GetType()) {

    case SN_DOUBLEVAR:
    case SN_INTVAR:
    case SN_CONSTVAR:
      break;   

    case SN_FEMVAR:
      if( ((SNfemVar *)itrVar()) ->IsDefinedElement() == NO) {
	SystemErrorANameADataA((SNunit*)itrVar(),"fem variable ",
			       " ,specified ",
			       ", is not an element name.");
	errors++;
      }
      break;

    case SN_EWISEVAR:
      if( ((SNewiseVar *)itrVar()) ->IsValidAttribute() == NO) {
	SystemErrorANameADataA((SNunit*)itrVar(),
			       "In ewise variable definition  ",
			       " ,specified ",
			       " is not valid name.");
	errors++;
      }
      break;

    case SN_FUNCTIONDEF:
      break;

    case SN_MATERIALVAR:
      break;      // check for material vars are in var_check_material.cpp

    default:
      std::cerr << "****************************************************\n";
      std::cerr << "This is default case branch in var_check_defined.cpp\n";
      std::cerr << "****************************************************\n";
      assert(1==0);

    }
  }
  return(errors);
}
