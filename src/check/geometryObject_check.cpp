/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : geometryObject_check.cpp
 *  Date     : 2002/03/18
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

#include "GeometryObject.hpp"
#include "../parser/Syntax/SNunit.hpp"

#include "../parser/Syntax/SNunit.hpp"
#include "../parser/Syntax/SNgeomDimension.hpp"
#include "../parser/Syntax/SNgeomMesher.hpp"
#include "../parser/Syntax/SNgeomProblem.hpp"
#include "../parser/Syntax/SNgeomSurface.hpp"
#include "../parser/Syntax/SNgeomEdge.hpp"
#include "../parser/Syntax/SNgeomPoint.hpp"
#include "../parser/Syntax/SNgeomRegion.hpp"


int geometryObject_check( list <SNunit *> &parseGeomLst)
{
  int errors;
  errors = 0;

  listIterator <SNunit *>itrGeom(parseGeomLst);

  // if not MaterialRegion
  for(itrGeom.init(); !itrGeom; ++itrGeom) {

    // check for geom material region has interaction with material var 

    if(itrGeom()->GetType() != SN_GEOMMATERIALREGION) {
      errors += itrGeom()->Check();
    }

  }
  return(errors);
}
