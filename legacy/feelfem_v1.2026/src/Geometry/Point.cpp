/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : Point.cpp
 *  Date     : 2001/04/02
 *  Modified : 
 *  
 *  Purpose  : Point object
 *  
 */

#include <assert.h>
#include "Point.hpp"

#include "../parser/Syntax/SNpoint.hpp"

Point::Point(double s) {
  dimension = 1;
  x         = s;
  type      = TYPE_POINT_NORMAL;
  return;
}

Point::Point(double s,double t) {
  dimension = 2;
  x         = s;
  y         = t;
  type      = TYPE_POINT_NORMAL;
  return;
}

Point::Point(double s,double t,double u) {
  dimension = 3;
  x         = s;
  y         = t;
  z         = u;
  type      = TYPE_POINT_NORMAL;
  return;
}

Point::Point(const char *nm,double s) {
  name      = nm;
  dimension = 1;
  x         = s;
  type      = TYPE_POINT_NORMAL;
  return;
}

Point::Point(const char *nm,double s,double t) {
  name      = nm;
  dimension = 2;
  x         = s;
  y         = t;
  type      = TYPE_POINT_NORMAL;
  return;
}

Point::Point(const char *nm,double s,double t,double u) {
  name      = nm;
  dimension = 3;
  x         = s;
  y         = t;
  z         = u;
  type      = TYPE_POINT_NORMAL;
  return;
}

Point::~Point()
{
  // do nothing;
  return;
}

int operator == (const Point &left, const Point &right)
{
  if(left.dimension != right.dimension ) return(1 == 0);

  switch(left.dimension){
  case 1:
    return( left.x == right.x);

  case 2:
    if(left.x != right.x) return(1 == 0);
    return( left.y == right.y);    

  case 3:
    if(left.x != right.x) return(1 == 0);    
    if(left.y != right.y) return(1 == 0);
    return( left.z == right.z);    

  default:
    assert( 1 != 0 );
    break;
  }
  assert( 1 != 0);

  return(1 == 0);
}

