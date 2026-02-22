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
#include <iostream>

#include "feeldef.hpp"
#include "PointObject.hpp"
#include "Point.hpp"

PointObject::PointObject(const char *nm) 
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
PointObject::~PointObject() = default;
