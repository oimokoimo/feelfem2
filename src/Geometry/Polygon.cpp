/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : Polygon.cpp
 *  Date     : 2001/04/05
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

#include "feelfuncs.hpp"       // feelfemgeom
#include "Geometry.hpp"        // feelfemgeom
#include "feeldef.hpp"
#include "Polygon.hpp"
#include "Edge.hpp"
#include "Point.hpp"


Polygon::Polygon(int typ)
{
  type     = typ;
  vertices = 0;
  
  return;
}

Polygon::Polygon(int typ,const char *nm)
{
  type     = typ;
  name     = nm;
  vertices = 0;
  
  return;
}

Polygon::~Polygon(void) = default;

int Polygon::isIntersect(double x1,double y1,double x2,double y2)
{
  int isIntersectTwoLines(double,double,double,double,
			  double,double,double,double);

  Point *fromPtPtr,*toPtPtr;

  fromPtPtr = vpPtrLst.lastElement();
  listIterator <Point *>itr(vpPtrLst);

  int ret;
  
  for(itr.init();!itr; ++itr) {
    toPtPtr = itr();

    ret = isIntersectTwoLines(x1,y1,x2,y2,
			      fromPtPtr->getX(),fromPtPtr->getY(),
			      toPtPtr->getX(),toPtPtr->getY()      );

    if(ret != 0) return(ret);
    fromPtPtr = toPtPtr;
  }
  return(0);
}

int Polygon::isIntersect(Polygon *oPtr)
{
  double x1,y1,x2,y2;
  
  Point *fromPtPtr,*toPtPtr;

  fromPtPtr = (oPtr->vpPtrLst).lastElement();
  listIterator <Point *>itr(oPtr->vpPtrLst);

  int ret;
  
  for(itr.init();!itr; ++itr) {
    toPtPtr = itr();

    x1 = fromPtPtr->getX();
    y1 = fromPtPtr->getY();
    x2 = toPtPtr->getX();
    y2 = toPtPtr->getY();
    
    ret = isIntersect(x1,y1,x2,y2);
    if(ret != 0) return(ret);
    fromPtPtr = toPtPtr;
  }
  return(0);
}

double Polygon::getArea(void)
{
  double getPolygonalArea(double *,double *, int );
  
  if(vertices==0) return (0.0);

  double *x,*y;
  
  x = new double[vertices];
  y = new double[vertices];

  listIterator <Point *>itr(vpPtrLst);

  int ip = 0;
  for(itr.init();!itr;++itr) {
    *(x+ip) = itr()->getX();
    *(y+ip) = itr()->getY();
    ip++;
  }

  double area = getPolygonalArea( x, y, vertices);
  
  delete x,y;

  return(area);
}

void Polygon::AddLastPointPtr(Point *pPtr)
{
  vertices++;
  vpPtrLst.addlast(pPtr);
  return;
}

void Polygon::AddLastPointPtrUniq(Point *pPtr)
{
  Point *prevPointPtr;

  if(vertices != 0) {
    prevPointPtr = vpPtrLst.lastElement();
    if(*prevPointPtr == *pPtr) { // Point operator == checks the coordinate
      return;  // do nothing;
    }
  }

  vertices++;
  vpPtrLst.addlast(pPtr);
  return;
}


void Polygon::AddLastEdgePtrUniq(Edge *ePtr)
{
  listIterator <Point *>itr(ePtr->pPtrLst);
  for(itr.init(); !itr; ++itr) {
    AddLastPointPtrUniq( itr());
  }
  return;
}



int Polygon::AddObjectByStrLst( list <string> &strLst)
{
  int error;
  
  error = 0;
  listIterator<string> itr(strLst);

  for(itr.init();!itr ; ++itr) {
    Point *pPtr;
    Edge  *ePtr;

    ePtr = 0;
    pPtr = feelfemgeom.GetPointPtrByName( itr() );

    /*    cerr << itr() ;
    if(pPtr != 0) {
      pPtr->print(cerr);
    }
    else {
      cerr <<" NULL!!!";
    }
    cerr << endl;
    */

    if(pPtr == 0) {
      ePtr = feelfemgeom.GetEdgePtrByName( itr() );
    }
    if(pPtr == 0 && ePtr == 0) {

	    std::cerr << "cannot find " <<itr() << std::endl;
      error++;
      continue;
    }
    if(pPtr != 0) {
      AddLastPointPtrUniq( pPtr );
    }
    else {
      AddLastEdgePtrUniq( ePtr );
    }
  }
  return(error);
}


int Polygon::getFirstPointRefNo()
{
  Point *pPtr = vpPtrLst.firstElement();
  assert(pPtr != 0);

  return(pPtr->getRefNo());
}

int Polygon::getSecondPointRefNo()
{
  assert(vertices > 1);
  Point *pPtr = vpPtrLst.getNthElement(2);
  assert(pPtr != 0);

  return(pPtr->getRefNo());
}
