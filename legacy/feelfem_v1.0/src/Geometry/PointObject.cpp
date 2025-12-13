/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : PointObject.cpp
 *  Date     : 2002/03/19
 *  Modified : 
 *  
 *  Purpose  :
 *  
 */
#include <iostream.h>

#include "feeldef.hpp"
#include "PointObject.hpp"
#include "Point.hpp"

PointObject::PointObject(char *nm) 
  : GeomObj(GOBJ_POINT,nm) 
{
  pointNo++;
  no   = pointNo;
  pPtr = 0;

  return;
}

PointObject::PointObject(Point *p)
  : GeomObj(GOBJ_POINT,p->GetName()) 
{
  pointNo++;
  no   = pointNo;

  name = p->GetName();
  pPtr = p;

  return;
}
PointObject::~PointObject()
{
  name.~string();
  return;
}
