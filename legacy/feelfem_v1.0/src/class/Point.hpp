/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : Point.hpp
 *  Date     : 2001/04/02
 *  Modified : 
 *  
 *  Purpose  : Point class
 *  
 */

#ifndef FEM_CLASS_POINT
#define FEM_CLASS_POINT

#include "string.hpp"

class Point {
public:
  Point(double);
  Point(double,double);
  Point(double,double,double);
  Point(const char *,double);
  Point(const char *,double,double);
  Point(const char *,double,double,double);
  ~Point();

  int isNameIs(const char *n) { 
    return( name == n); 
  }

  void print(ostream &ost) {
    ost << "(" << x << "," << y << ")";
  }


  void   SetRefNo(int n) { refNo = n; return; }  // used in Geometry.cpp,
                                                 //         SNpedge.cpp
  void   SetType (int n) { type  = n; return; }  // used SNpedge.cpp

  int    getRefNo(void ) { return( refNo ); }
  int    getType (void ) { return( type  ); }
  int    getDimension(void) { return( dimension ); }
  double getX() { return x; }
  double getY() { return y; }
  double getZ() { return z; }
  char *GetName() { return (char *)name; }

  // this operator checks the coordinate only, not refNo.
  friend int operator == (const Point &left, const Point &right);
  friend class Polygon;

private:
  int    dimension;         // space dimension
  int    type;              // Syntax point or point on a parameteric edge
  string name;              // name
  int    refNo;             // reference No.
  double x,y,z;             // coordinate value
};

#endif
