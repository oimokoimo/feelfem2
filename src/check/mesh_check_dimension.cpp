/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : mesh_check_vars.cpp
 *  Date     : 2001/03/14
 *  Modified : 
 *  
 *  Purpose  : dimension check     SET dimension into feelfemobj
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

#include "feelfuncs.hpp"                 // feelfemobj
#include "Object.hpp"                    // feelfemobj

#include "check_funcs.hpp"

#include "../parser/Syntax/SNunit.hpp"
#include "../parser/Syntax/SNpoint.hpp"
#include "../parser/Syntax/SNdimension.hpp"


int mesh_check_dimension( list <void *>&parseMeshLst )
{
  listIterator <void *>itrMesh(parseMeshLst);

  int errors;

  int dimension;

  errors    = 0;
  dimension = 0;
  
  for(itrMesh.init(); !itrMesh; ++itrMesh) {

    switch(((SNunit *)itrMesh())->GetType()) {
    case SN_DIMENSION:
      if(dimension != 0) {
	SystemErrorA(((SNunit *)itrMesh()),"Multiple dimension sentences.");
	errors++;
      }

      dimension = ((SNdimension *)itrMesh())->getSpaceDimension();

      if(dimension < 1 || dimension >3) {
	SystemErrorA(((SNunit *)itrMesh()),"Illegal dimension.");
	errors++;
	dimension = DEFAULT_DIMENSION;
      }
      break;

    default:
      break;
    }
  }

  if(dimension == 0) {
    dimension = DEFAULT_DIMENSION;
  }


  for(itrMesh.init(); !itrMesh; ++itrMesh) {

    switch(((SNunit *)itrMesh())->GetType()) {

    case SN_POINT:
      if(dimension !=  ((SNpoint *)itrMesh())->getSpaceDimension()) {
	SystemErrorANameA(((SNunit *)itrMesh())," point ",
			  " has illegal dimension.");
	errors++;
      }
      break;

    default:
      break;
    }
  }


  // set dimension into feelfemobj
  feelfemobj.SetSpaceDimension( dimension );
  
  return(errors);
}
