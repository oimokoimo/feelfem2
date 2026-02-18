/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : Polygon.hpp
 *  Date     : 2001/04/03
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

#ifndef FEM_CLASS_POLYGON
#define FEM_CLASS_POLYGON

#include "string.hpp"
#include "list.hpp"

class Point;
class Edge;

class Polygon {
public:
  Polygon(int);               // type (TYPE_POLYGON_NORMAL,TYPE_POLYGON_HOLE)
  Polygon(int,const char *);  // type and name
  ~Polygon();

  int isIntersect(double x1,double y1,double x2,double y2);
  int isIntersect(Polygon *);
  double getArea();
  void AddLastPointPtr(Point *);
  void AddLastPointPtrUniq(Point *);          // if same with the last, no add
  void AddLastEdgePtrUniq(Edge *);

  int getFirstPointRefNo();
  int getSecondPointRefNo();


  // Use feelfemgeom Object
  int  AddObjectByStrLst( list <string> &);   // return non zero if err


  friend class Bamg;   // to access Point Ptr in Bamg::addBamgEdgeByPolygon

private:
  string name;   // not use,maybe
  int    refNo;  // not use,maybe
  int    type;   // TYPE_POLYGON_NORMAL,TYPE_POLYGON_HOLE

  int    vertices;
  list <Point *>vpPtrLst;
};

#endif
