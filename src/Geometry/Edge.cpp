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

#include "Point.hpp"
#include "Edge.hpp"
Edge::Edge(const char *nm, int typ)
{
  name   = nm;
  type   = typ;
  points = 0;
  return;
}


Edge::~Edge() = default;


void Edge::AddPointPtr(Point *pPtr)
{
  pPtrLst.addlast(pPtr);
  return;
}
