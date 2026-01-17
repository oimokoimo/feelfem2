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
 */

#include "feelfuncs.hpp"
#include "Geometry.hpp"
#include "GeometryObject.hpp"

void store_geometry_geometryObject()
{
  feelfemgeom.GenerateGeometryObject();// Geometry/Geometry_GeometryObject.cpp 
  
  return; 
}
