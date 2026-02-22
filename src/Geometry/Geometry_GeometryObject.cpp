/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : Geometry_GeometryObject.cpp
 *  Date     : 2002/03/19
 *  Modified : 
 *  
 *  Purpose  : Store Geometry data into GeometryObject
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
#include "feelfuncs.hpp"

#include "Geometry.hpp"
#include "GeometryObject.hpp"

#include "Point.hpp"
#include "PointObject.hpp"

#include "Edge.hpp"
#include "EdgeObject.hpp"

#include "PolygonalRegion.hpp"
#include "RegionObject.hpp"

void Geometry::GenerateGeometryObject()
{

  // point
  listIterator <Point *>itrP(pointPtrLst);
  for(itrP.init(); !itrP ; ++itrP){
    if(itrP()->getType() == TYPE_POINT_NORMAL) {  // normal point
      PointObject *poPtr = new PointObject(itrP());

      string name = itrP()->GetName();
      feelfemgeomobj.AddUsedNameLst( name );   // used for defined geometryObj
      feelfemgeomobj.AddGeomObj(poPtr);
      
    }
  }

  // edge
  listIterator <Edge *>itrE(edgePtrLst);
  for(itrE.init(); !itrE ; ++itrE ){
    EdgeObject *eoPtr = new EdgeObject(itrE());

    string name = itrE()->GetName();
    feelfemgeomobj.AddUsedNameLst( name );   // used for defined geometryObj

    feelfemgeomobj.AddGeomObj(eoPtr);
  }

  // surface
  // no surface for 2d

  // region
  listIterator <PolygonalRegion *>itrR(polygonalRegionPtrLst);
  for(itrR.init(); !itrR ; ++itrR) {

    string name = itrR()->GetName();
    feelfemgeomobj.AddUsedNameLst( name );   // used for defined geometryObj

    RegionObject *roPtr = new RegionObject(itrR());
    feelfemgeomobj.AddGeomObj(roPtr);
  }

  return;
}
