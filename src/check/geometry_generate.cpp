/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : geometry_generate.cpp
 *  Date     : 2001/04/03
 *  Modified : 
 *  
 *  Purpose  : Make geometry object
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

#include "Geometry.hpp"
#include "Object.hpp"
#include "PolygonalRegion.hpp"

#include <iostream>
#include "list.hpp"
#include "string.hpp"

#include "check_funcs.hpp"

// for parametric edge
#include "meshEvalGinac.hpp"

#include "../parser/Syntax/SNunit.hpp"
#include "../parser/Syntax/SNpoint.hpp"
#include "../parser/Syntax/SNedge.hpp"
#include "../parser/Syntax/SNpedge.hpp"
#include "../parser/Syntax/SNregion.hpp"
#include "../parser/Syntax/SNvertices.hpp"
#include "../parser/Syntax/SNdimension.hpp"

#include "feelfuncs.hpp"                 // feelfemgeom

int geometry_generate( list <void *>&parseMeshLst )
{
  listIterator <void *>itrMesh(parseMeshLst);

  int errors;
  errors    = 0;

  // Initialize (General)
  feelfemgeom.setVertices(DEFAULT_VERTICES);   // default vertices
  for(itrMesh.init(); !itrMesh; ++itrMesh) {
    switch(((SNunit *)itrMesh())->GetType())
      {

      case SN_VERTICES:
	feelfemgeom.setVertices(((SNvertices *)itrMesh())->getVertices());
	break;

      case SN_DIMENSION:
	feelfemgeom.SetDimension(((SNdimension *)itrMesh())->
				 getSpaceDimension());
	break;

      case SN_MESHDOUBLEVAR:
      case SN_MESHASSIGNMENT:
      case SN_PEDGE:
      case SN_EDGE:
      case SN_REGION:
      case SN_DOMAIN:
      case SN_POINT:
	break;


      default:
	assert(1==0);
	break;
      }
  }



  // Stage 1 Make Point  
  for(itrMesh.init(); !itrMesh; ++itrMesh) {
    switch(((SNunit *)itrMesh())->GetType())
      {
      case SN_DIMENSION:
      case SN_MESHDOUBLEVAR:
      case SN_MESHASSIGNMENT:
      case SN_PEDGE:
      case SN_EDGE:
      case SN_REGION:
      case SN_DOMAIN:
      case SN_VERTICES:
	break;

      case SN_POINT:
	{
	  SNpoint *snpPtr;
	  Point *pPtr;
	  snpPtr = (SNpoint*)itrMesh();
	  pPtr = snpPtr->MakePointObjWithName();
	  feelfemgeom.AddPointPtr(pPtr);          // enumerate point here
                                          	  // minimum,maximum is set
	}
	break;
      default:
	assert(1==0);
	break;
      }
  }

  // Stage 2-a Make Edge (PEdge is at Stage 2-a)
  for(itrMesh.init(); !itrMesh; ++itrMesh) {
    switch(((SNunit *)itrMesh())->GetType())
      {
      case SN_POINT:
      case SN_DIMENSION:
      case SN_MESHDOUBLEVAR:
      case SN_MESHASSIGNMENT:
      case SN_PEDGE:
      case SN_REGION:
      case SN_DOMAIN:
      case SN_VERTICES:
	break;

      case SN_EDGE:
	{
	  SNedge *snePtr;
	  Edge   *ePtr;
	  snePtr = (SNedge*)itrMesh();
	  ePtr   = snePtr->MakeEdgeObj();
	  feelfemgeom.AddEdgePtr(ePtr);          // enumerate edge No. here
	}
	break;
      default:
	assert(1==0);
	break;
      }
  }


  // Stage 2-bb Make Parametric Edge 
  // first, evaluate xmin,xmax,ymin,ymax for points on PEDGE
  // and make evaluator
  meshEvalGinac evaluator;
  for(itrMesh.init(); !itrMesh; ++itrMesh) {
    int ret;
    switch(((SNunit *)itrMesh())->GetType())
      {
      case SN_MESHDOUBLEVAR:
	ret = evaluator.meshDoubleVar((SNmeshDoubleVar *)itrMesh());
	assert(ret == 0);
	break;
	
      case SN_MESHASSIGNMENT:
	ret = evaluator.meshAssignment((SNmeshAssignment *)itrMesh());
	assert(ret == 0);
	break;

      case SN_POINT:
      case SN_DIMENSION:
      case SN_EDGE:
      case SN_REGION:
      case SN_DOMAIN:
      case SN_VERTICES:
	break;

      case SN_PEDGE:
	{
	  // Evaluate the maximum, minimum points on pedge
	  //
	  // if the outer boundary is pure pedge boundary, it is necessary...
	  SNpedge *snpePtr;
	  snpePtr = (SNpedge*)itrMesh();
	  snpePtr->EvaluateXYMinMax(evaluator);
	}
	break;
      default:
	assert(1==0);
	break;
      }
  }

  // Generate pedge
  for(itrMesh.init(); !itrMesh; ++itrMesh) {
    switch(((SNunit *)itrMesh())->GetType())
      {
      case SN_MESHDOUBLEVAR:
      case SN_MESHASSIGNMENT:
      case SN_POINT:
      case SN_DIMENSION:
      case SN_EDGE:
      case SN_REGION:
      case SN_DOMAIN:
      case SN_VERTICES:
	break;

      case SN_PEDGE:
	{
	  SNpedge *snpePtr;
	  Edge   *ePtr;
	  snpePtr = (SNpedge*)itrMesh();
	  ePtr   = snpePtr->MakeEdgeObj(evaluator);
	  feelfemgeom.AddEdgePtr(ePtr);          // enumerate edge No. here
	}
	break;
      default:
	assert(1==0);
	break;
      }
  }


  // Stage 3 Make Region
  for(itrMesh.init(); !itrMesh; ++itrMesh) {
    switch(((SNunit *)itrMesh())->GetType())
      {
      case SN_POINT:
      case SN_DIMENSION:
      case SN_MESHDOUBLEVAR:
      case SN_MESHASSIGNMENT:
      case SN_PEDGE:
      case SN_EDGE:
      case SN_DOMAIN:
      case SN_VERTICES:
	break;

      case SN_REGION:
	{
	  SNregion *snrPtr;
	  PolygonalRegion *prPtr;
	  snrPtr = (SNregion *)itrMesh();
	  prPtr  = snrPtr->MakePolygonalRegionObj();
	  
	  prPtr->setArea();

	  feelfemgeom.AddPolygonalRegionPtr(prPtr);  // enumerate edge No. here
	}
	break;
      default:
	assert(1==0);
	break;
      }
  }

  return(errors);
}

