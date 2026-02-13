/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : Edge.hpp
 *  Date     : 2001/04/03
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

#ifndef FEM_CLASS_EDGE
#define FEM_CLASS_EDGE

#include "list.hpp"
#include "string.hpp"
class Point;

class Edge {
public:
  Edge(const char *, int);
  ~Edge();

  void SetRefNo(int n) { refNo = n; return; }  // in Geometry.cpp
  void AddPointPtr(Point *pPtr);
  
  int  isNameIs(const char *nm) {
    return( name == nm );
  }

  const char *GetName(void) { return name; }

  // this operator checks the coordinate only, not refNo.
  friend class Polygon;   // to access Point list

private:
  int    type;              // Syntax edge or edge on a parameteric edge
  string name;              // name
  int    refNo;             // reference No.

  int    points;
  list <Point *>pPtrLst;

};

#endif
