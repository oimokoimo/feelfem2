/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : PolygonalRegion.hpp
 *  Date     : 2001/04/03
 *  Modified : 
 *  
 *  Purpose  : Polygonal Region (Polygonal region possibly with
 *                               polygonal hole.
 *
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
 *
 */

#ifndef FEM_CLASS_POLYGONALREGION
#define FEM_CLASS_POLYGONALREGION

#include "list.hpp"
#include "string.hpp"

class Polygon;

class PolygonalRegion {
public:
  PolygonalRegion(const char *,Polygon *);
  ~PolygonalRegion();
  
  void SetRefNo(int n) {refNo = n; return;}
  int  getRefNo(void ) {return(refNo); }
  double getArea();   // not calculate  (different from Polygon.hpp)
  void setArea();     // calculate
  int AddHolePolygonPtr(Polygon *); // check the intersection
  int getFirstOuterPointRefNo();
  int getSecondOuterPointRefNo();

  const char *GetName();


  friend class Bamg;  // to access outerPolygonPtr, holePolygonPtrLst from
                      // Bamg::addBamgEdgeByPolygonalRegion

private:
  string name;
  int    refNo;
  int    matno;   // currently, same as refNo.....
  int    holes;
  double area;
  Polygon *outerPolygonPtr;
  list <Polygon *>holePolygonPtrLst;

};


#endif
