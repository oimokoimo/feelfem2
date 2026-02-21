/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : mesh_check_conflict.cpp
 *  Date     : 2001/03/26
 *  Modified : 
 *  
 *  Purpose  : name conflict check
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

#include "list.hpp"
#include "string.hpp"
#include "feelfuncs.hpp"

#include "check_funcs.hpp"

#include "../parser/Syntax/SNunit.hpp"
#include "../parser/Syntax/SNpoint.hpp"
#include "../parser/Syntax/SNdimension.hpp"


int mesh_check_conflict( list <void *>&parseMeshLst )
{
  listIterator <void *>itrMesh(parseMeshLst);
  list <string> checkConflict;

  int errors;

  errors    = 0;
  
  for(itrMesh.init(); !itrMesh; ++itrMesh) {

    switch(((SNunit *)itrMesh())->GetType()) {

    case SN_POINT:
    case SN_EDGE:
    case SN_PEDGE:
    case SN_REGION:
    case SN_DOMAIN:
      if(((SNunit *)itrMesh())->isAlreadyUsedName(checkConflict)) {
	SystemErrorANameA((SNunit*)itrMesh(),"Name "," is already used.");
	errors++;
      }

    default:
      break;
    }
  }
  checkConflict.deleteAllValues();
  
  return(errors);
}
