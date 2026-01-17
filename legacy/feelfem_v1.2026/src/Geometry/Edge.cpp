/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : Edge.cpp
 *  Date     : 2001/04/04
 *  Modified : 
 *  
 *  Purpose  : Edge class
 *  
 */

#include "Point.hpp"
#include "Edge.hpp"
Edge::Edge(const char *nm, int typ)
{
  name   = nm;
  type   = typ;
  points = 0;
  return;
}


Edge::~Edge()
{
  // do nothing now

  return;
}


void Edge::AddPointPtr(Point *pPtr)
{
  pPtrLst.addlast(pPtr);
  return;
}
