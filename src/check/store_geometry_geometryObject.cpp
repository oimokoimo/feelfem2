/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : store_geometry_geometryObject.cpp
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

#include "feelfuncs.hpp"
#include "Geometry.hpp"
#include "GeometryObject.hpp"

void store_geometry_geometryObject()
{
  feelfemgeom.GenerateGeometryObject();// Geometry/Geometry_GeometryObject.cpp 
  
  return; 
}
