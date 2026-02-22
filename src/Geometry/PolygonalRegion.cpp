/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : PolygonalRegion.cpp
 *  Date     : 2001/04/04
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

#include "Polygon.hpp"
#include "PolygonalRegion.hpp"


PolygonalRegion::PolygonalRegion(const char *nm,Polygon *polPtr)
{
  name  = nm;
  holes = 0;
  outerPolygonPtr = polPtr;
  
  return;
}


PolygonalRegion::~PolygonalRegion() = default;

void PolygonalRegion::setArea(void)
{
  area = outerPolygonPtr->getArea();

  listIterator <Polygon*>itr(holePolygonPtrLst);
  for(itr.init(); !itr ; ++itr) {
    area = area - itr()->getArea();
  }
  return;
}

double PolygonalRegion::getArea(void)
{
  return(area);
}

int PolygonalRegion::AddHolePolygonPtr(Polygon *holePolygonPtr)
{
  int ret,errors;
  
  errors = 0;

  ret   = holePolygonPtr->isIntersect(outerPolygonPtr);
  errors = errors+ret;
  
  listIterator <Polygon*>itr(holePolygonPtrLst);
  for(itr.init(); !itr ; ++itr) {
    ret = holePolygonPtr->isIntersect(itr());
    errors = errors + ret;
  }
  
  if(errors == 0) {
    holes++;
    holePolygonPtrLst.addlast(holePolygonPtr);
  }
  return(errors);
}

int PolygonalRegion::getFirstOuterPointRefNo()
{
  return(outerPolygonPtr->getFirstPointRefNo());
}

int PolygonalRegion::getSecondOuterPointRefNo()
{
  return(outerPolygonPtr->getSecondPointRefNo());
}

const char *PolygonalRegion::GetName()
{
  return name;
}
