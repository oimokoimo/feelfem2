/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SurfaceObject.cpp
 *  Date     : 2002/03/19
 *  Modified : 
 *  
 *  Purpose  :
 *  
 */

#include "SurfaceObject.hpp"

SurfaceObject::SurfaceObject(char *nm) 
  : GeomObj(GOBJ_SURFACE,nm) 
{
  surfaceNo++;
  no = surfaceNo;
  return;
}

SurfaceObject::~SurfaceObject() 
{
  name.~string();
  return;
}
