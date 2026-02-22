/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : EdgeObject.cpp
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

#include "EdgeObject.hpp"
#include "Edge.hpp"

EdgeObject::EdgeObject(const char *nm) 
  : GeomObj(GOBJ_EDGE,nm) 
{
  edgeNo++;
  no   = edgeNo;
  edgePtr = 0;

  return;
}

EdgeObject::EdgeObject(Edge *ptr)
  : GeomObj(GOBJ_EDGE, ptr->GetName()) 
{
  edgeNo++;
  no   = edgeNo;

  name = ptr->GetName();
  edgePtr = ptr;

  return;
}
EdgeObject::~EdgeObject()
{
  name.~string();
  return;
}
