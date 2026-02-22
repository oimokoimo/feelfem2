/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : 
 *  Date     : 2002/03/19
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
#include "feelfuncs.hpp"
#include "RegionObject.hpp"
#include "PolygonalRegion.hpp"
#include "GeomObj.hpp"
#include "GeometryObject.hpp"


RegionObject::RegionObject(const char *nm) 
  :GeomObj(GOBJ_REGION,nm) 
{
  regionNo++;
  feelfemgeomobj.SetRegionObjects( regionNo );
  feelfemgeomobj.AddRegionObjectPtr( this );

  no  = regionNo;

  polygonalRegionPtr = 0;

  return;
}

RegionObject::RegionObject(PolygonalRegion *porPtr)
  : GeomObj(GOBJ_REGION,porPtr->GetName()) 
{
  regionNo++;
  feelfemgeomobj.SetRegionObjects( regionNo );
  feelfemgeomobj.AddRegionObjectPtr( this );

  no  = regionNo;

  polygonalRegionPtr = porPtr;
  name = porPtr->GetName();
  
  return;
}

RegionObject::~RegionObject() = default;

int RegionObject::GetPropertyNo(void)
{
  return(no);
}

void RegionObject::AddMaterialAttribute( string &nm )
{
  materialAttributeStrLst.addlast(nm);
  return;
}

int RegionObject::HasMaterialAttribute(string &nm )
{
  if(nm == name) return(YES);
  
  if(materialAttributeStrLst.includes(nm)) return(YES);

  return(NO);
}
