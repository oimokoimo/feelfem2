/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : GeomBamgInterface.cpp
 *  Date     : 2001/04/06
 *  Modified : 
 *  
 *  Purpose  :
 *  
 */

#include "feelfuncs.hpp"
#include "feeldef.hpp"

#include "Bamg.hpp"
#include "Geometry.hpp"

#include "Point.hpp"
#include "Edge.hpp"
#include "PolygonalRegion.hpp"


void Geometry::BamgGeomSet( Bamg *bamgPtr )
{
  BamgPointSet( bamgPtr );

  BamgBamgEdgeSet( bamgPtr );

  BamgSubDomainSet( bamgPtr );

  bamgPtr->setSpecifiedVertices( getVertices() );   // vertices

  return;
}

void Geometry::BamgPointSet( Bamg *bamgPtr)
{
  listIterator <Point *>itr(pointPtrLst);

  for(itr.init(); !itr ; ++itr ) {
    
    bamgPtr->addVertices( itr() );   // the ordering of refNo and in the list
                                     // must be identical
  }
  return;
}

void Geometry::BamgBamgEdgeSet( Bamg *bamgPtr)
{
  listIterator <PolygonalRegion *>itr(polygonalRegionPtrLst);

  for(itr.init(); !itr ; ++itr ) {
    
    bamgPtr->addBamgEdgeByPolygonalRegion(  itr() );

  }
  return;
}

void Geometry::BamgSubDomainSet( Bamg *bamgPtr )
{
  listIterator <PolygonalRegion *>itr(polygonalRegionPtrLst);
  
  for(itr.init(); !itr ; ++itr ){
    bamgPtr->addBamgSubDomainByPolygonalRegion( itr() );
  }
  return;
}
