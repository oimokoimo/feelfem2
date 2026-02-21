/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : geometry_scheme_elementEtype_check.cpp
 *  Date     : 2002/11/06
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


#include "feeldef.hpp"
#include "feelfem.hpp"              // for command options
#include "feelfuncs.hpp"
#include "check_funcs.hpp"          // for error messages

#include "parseExternals.hpp"       // for parser  trees


#include "../parser/Syntax/SNunit.hpp"
#include "../parser/Syntax/SNelementType.hpp"



int scheme_elementType_check(list <void *>&parseSchemeLst)
{
  int ret,errors;

  errors = 0;

  listIterator <void *>itr(parseSchemeLst);
  for(itr.init(); !itr ; ++itr) {

    SNunit *uPtr =(SNunit *)itr();

    switch(uPtr->GetType()) {
    case SN_ELEMENTTYPE:
      ret = ((SNelementType *)uPtr)->IsValidElementTypeName();
      errors += ret;

      break;

    default:
      break;
    }
  }
  return(errors);
}
