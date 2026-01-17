/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : Bamg.cpp
 *  Date     : 2001/03/30
 *  Modified : 2001/04/09
 *  
 *  Purpose  : Bamg class constructor
 *  
 */

#include "feelfuncs.hpp"   // abortExit
#include "feeldef.hpp"
#include "Bamg.hpp"
#include "Point.hpp"
#include "Edge.hpp"
#include "Polygon.hpp"
#include "PolygonalRegion.hpp"

BamgPoint::BamgPoint(Point *pPtr, int no)
{
  x         = pPtr->getX();
  y         = pPtr->getY();
  type      = pPtr->getType();
  refNo     = pPtr->getRefNo();

  bamgRefNo = no;

  return;
}

Bamg::Bamg() 
{
  dimension = 2;             // fixed
  maximalAngleOfCorner = 91; // fixed

  bamgRefNoMaster = 0;

  bamgVertices    = 0;         // used also enumerate counter
  bamgEdges       = 0;         // used also enumerate counter
  bamgSubDomains  = 0;

  //  corners = 0;
  isolatePoints = 0;

  return;
}

Bamg::~Bamg()
{
  // do nothing now , but oimo oimo oimo
}

  
int Bamg::getBamgPointRefNoFromOriginalRefNo( int n )
{
  listIterator <BamgPoint *>itr(bamgPointPtrLst);
  for(itr.init(); !itr ; ++itr ) {
    if(n == itr()->getOriginalRefNo()) {
      return(itr()->getBamgRefNo());
    }
  }
  abortExit("Cannot find(BAmg::getBamgPointRefNoFromOriginalRefNo)");
  return(0);
}

void Bamg::addVertices (Point *pPtr)    // called from Geometry::BamgPointSet
  //
  // Duplication is not accepted.  (certification up to user)
  //
{
  int bamgRefNo;

  bamgVertices++;
  BamgPoint *bamgPointPtr = new BamgPoint(pPtr,bamgVertices);
  
  //  assert( vertices == pPtr->getRefNo());
  
  bamgPointPtrLst.addlast(bamgPointPtr);
  return;
}

// Bamg correspondance SubDomain
void Bamg::addBamgEdgeByPolygonalRegion( PolygonalRegion *prPtr)  
{
  addBamgEdgeByPolygon(prPtr->outerPolygonPtr);
  
  listIterator<Polygon *>itr(prPtr->holePolygonPtrLst);
  for(itr.init();!itr;++itr) {
    addBamgEdgeByPolygon(itr());
  }

  return;
}


void Bamg::addBamgEdgeByPolygon( Polygon *poPtr )
{
  for(int i=0;i<poPtr->vertices;i++) {
    Point *p1Ptr,*p2Ptr;

    p1Ptr = (poPtr->vpPtrLst).getNthElement(i+1);
    if(i == poPtr->vertices-1) {
      p2Ptr = (poPtr->vpPtrLst).getNthElement(1);
    }
    else {
      p2Ptr = (poPtr->vpPtrLst).getNthElement(i+1+1);      
    }
    addBamgEdgeBy2OriginalRefNo( p1Ptr->getRefNo(), p2Ptr->getRefNo());

  }
  return;
}

void Bamg::addBamgEdgeBy2OriginalRefNo( int from, int to )
  //
  // If the combination is already defined, simply ignored.
  //
{
  int bamgFrom,bamgTo;

  BamgEdge *ptr;

  bamgFrom = getBamgPointRefNoFromOriginalRefNo( from );
  bamgTo   = getBamgPointRefNoFromOriginalRefNo( to   );

  listIterator <BamgEdge *>itr(bamgEdgePtrLst);
  for(itr.init(); !itr ; ++itr) {
    ptr = itr();
    if(ptr->isSameEdge( bamgFrom, bamgTo) ) {
      return;  // already registered.
    }
  }

  bamgEdges++;
  ptr = new BamgEdge(bamgFrom,bamgTo,bamgEdges);

  bamgEdgePtrLst.addlast(ptr);
  return;
}

int Bamg::getBamgEdgeRefNoFrom2OriginalRefNo( int from, int to )
  //
  // If the combination is already defined, simply ignored.
  //
{
  int bamgFrom,bamgTo;

  BamgEdge *ptr;

  bamgFrom = getBamgPointRefNoFromOriginalRefNo( from );
  bamgTo   = getBamgPointRefNoFromOriginalRefNo( to   );

  listIterator <BamgEdge *>itr(bamgEdgePtrLst);
  for(itr.init(); !itr ; ++itr) {
    ptr = itr();
    if(ptr->isSameEdge( bamgFrom, bamgTo) ) {
      if( bamgFrom == ptr->getFrom()) {
	return( ptr->getBamgRefNo());
      }
      else {
	return(-( ptr->getBamgRefNo()));
      }
    }
  }
  abortExit("not exist edge required:getBamgEdgeRefNoFrom2OriginalRefNo");

  return(-1);
}

void Bamg::addBamgSubDomainByPolygonalRegion(PolygonalRegion *poPtr)
{

  int refTo   = poPtr->getFirstOuterPointRefNo();
  int refFrom = poPtr->getSecondOuterPointRefNo();

  int bamgEdgeRefNo = getBamgEdgeRefNoFrom2OriginalRefNo(refFrom,refTo);

  int dir;
  if(bamgEdgeRefNo > 0) {
    dir = -1;
  }
  else {
    bamgEdgeRefNo = -bamgEdgeRefNo;
    dir = 1;
  }
  
  BamgSubDomain *bsdPtr = new BamgSubDomain( bamgEdgeRefNo,dir,
					     poPtr->getRefNo());

  bsdPtr->setArea( poPtr->getArea() );

  bamgSubDomains++;
  bamgSubDomainPtrLst.addlast(bsdPtr);

  return;
}
