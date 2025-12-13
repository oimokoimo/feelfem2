/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : 
 *  Date     : 2001/04/03
 *  Modified : 
 *  
 *  Purpose  :
 *  
 */

#include <math.h>

#include "feelfuncs.hpp"

#include "Geometry.hpp"
#include "Point.hpp"
#include "Edge.hpp"
#include "PolygonalRegion.hpp"

Geometry feelfemgeom;          // extern is declared in feelfuncs.hpp

Geometry::Geometry()
{
  dimension = 0;    // initialize
  vertices  = 0;    // initialize

  points  = 0;
  edges   = 0;
  faces   = 0;
  volumes = 0;
  regions = 0;
  domains = 0;

  return;
}

Geometry::~Geometry()
{
  // do nothing now
  return;
}

void Geometry::AddPointPtr(Point *pPtr)
{
  points++;
  pPtr->SetRefNo(points);
  pointPtrLst.addlast(pPtr);

  if(points == 1) {
    if(dimension == 0) {
      dimension = pPtr->getDimension();
    }
    switch(dimension) {
    case 3:
      zmin = pPtr->getZ();
      zmax = pPtr->getZ();

    case 2:
      ymin = pPtr->getY();
      ymax = pPtr->getY();

    case 1:
      xmin = pPtr->getX();
      xmax = pPtr->getX();
      break;

    default:
      assert(dimension == 2);
    }
  }
  else {
    switch(dimension) {
    case 3:
      if(zmin > pPtr->getZ()) zmin = pPtr->getZ();
      if(zmax < pPtr->getZ()) zmax = pPtr->getZ();

    case 2:
      if(ymin > pPtr->getY()) ymin = pPtr->getY();
      if(ymax < pPtr->getY()) ymax = pPtr->getY();

    case 1:
      if(xmin > pPtr->getX()) xmin = pPtr->getX();
      if(xmax < pPtr->getX()) xmax = pPtr->getX();
      break;

    default:
      assert(dimension == 2);
    }
  }
  return;
}

void Geometry::AddEdgePtr(Edge *ePtr)
{
  edges++;
  ePtr->SetRefNo(edges);
  edgePtrLst.addlast(ePtr);
  return;
}

void Geometry::AddPolygonalRegionPtr(PolygonalRegion *prPtr)
{
  regions++;
  prPtr->SetRefNo(regions);
  polygonalRegionPtrLst.addlast(prPtr);
  return;
}


Point *Geometry::GetPointPtrByName( const char * nm )
{
  listIterator <Point *>itr(pointPtrLst);

  for(itr.init(); !itr ; ++itr) {
    if(itr()->isNameIs(nm)) {
      return(itr());
    }
  }
  return(0);
}

Edge *Geometry::GetEdgePtrByName( const char * nm )
{
  listIterator <Edge *>itr(edgePtrLst);

  for(itr.init(); !itr ; ++itr) {
    if(itr()->isNameIs(nm)) {
      return(itr());
    }
  }
  return(0);
}

double Geometry::getApproximateH2D(void)   // return approximate mesh size
{
  double areaApp = getMaximumArea2D();
  assert(areaApp  > 0);
  assert(vertices > 0);
  double dnodes  = (double)vertices;
  double dn      = sqrt(dnodes);
  double da      = areaApp/(dn-1.0)/(dn-1.0)/2.0;
  double h       = sqrt(da * 4.0 / 1.7320508);
  return(h);
}
