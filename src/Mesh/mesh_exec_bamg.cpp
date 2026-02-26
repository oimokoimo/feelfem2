/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : 
 *  Date     : 2001/04/06
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
#include "feeldef.hpp"

#include "Object.hpp"
#include "GeometryObject.hpp"

#include "Geometry.hpp"
#include "Point.hpp"
#include "Edge.hpp"
#include "PolygonalRegion.hpp"

#include "Bamg.hpp"
#include "../Xplot++/xplotfuncs.hpp"

void mesh_exec_bamg(void)
{
  Bamg *bamgPtr = new Bamg;
  feelfemobj.PutBamgPtr(bamgPtr);

  feelfemgeomobj.SetMesherPtr( bamgPtr );

  // Point set
  feelfemgeom.BamgGeomSet(bamgPtr);
  
  bamgPtr->makeBamgGeom( BAMG_GEOMETRY_FILENAME );
  
  bamgPtr->execBamg(BAMG_GEOMETRY_FILENAME,BAMG_MESH_FILENAME);

  bamgPtr->readBamgMesh( BAMG_MESH_FILENAME);

  //  bamgPtr->DebugPrintBamgMesh();

  bamgPtr->DebugDrawMesh();

  return;
}
