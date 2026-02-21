/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : geom_materialRegion_check.cpp
 *  Date     : 2002/09/02
 *  Modified : 
 *  
 *  Purpose  : check material region 
 *             specified region is defined or not.
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

#include "GeometryObject.hpp"
#include "../parser/Syntax/SNunit.hpp"
#include "../parser/Syntax/SNgeomMaterialRegion.hpp"



int geom_materialRegion_check( list <SNunit *> &parseGeomLst)
{
  int errors;
  errors = 0;

  listIterator <SNunit *>itrGeom(parseGeomLst);

  // if not MaterialRegion
  for(itrGeom.init(); !itrGeom; ++itrGeom) {

    if(itrGeom()->GetType() != SN_GEOMMATERIALREGION) continue;

    // material region check
    
    errors += itrGeom()->Check();

  }
  return(errors);
}
