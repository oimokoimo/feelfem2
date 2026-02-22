/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : isIntersectTwoLines.cpp
 *  Date     : 2001/04/11
 *  Modified : 
 *  
 *  Purpose  : Judge the intersection of (x1,y1)-(x2,y2) and
 *                                       (s1,t1)-(s2,t2)
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
#include <cassert>
#include <iostream>


int isIntersectTwoLines(double x1,double y1,double x2,double y2,
			double s1,double t1,double s2,double t2 )
  //
  // return value is
  // 0 : They have no intersection.       TYPE_LINE_NOINTERSECTION
  // 1 : They are an identical line.      TYPE_LINE_IDENTICAL
  // 2 : Their edge point is the same     TYPE_LINE_CONNECTED
  // 3 : They have common intervals.      TYPE_LINE_INTERSECTION
  // 4 : They have an intersection        TYPE_LINE_CROSS_AT_1_POINT
{

  // if the two lines are not parallel,
  // 
  // linear system for p,q can be solved.
  //
  // (x1,y1)+p(x2-x1,y2-y1) = (s1,t1) + q(s2-s1,t2-t1)
  //
  //  p(dx,dy)-q(ds,dt) = (sx,ty)
  //
  // where dx = x2-x1, dy = y2-y1, ds = s2-s1, dt = t2-t1
  //       sx = s1-x1, ty = t1-y1  
  //oimo cerr << "LINE("<< x1 <<"," << y1 <<")-("<<x2 << "," << y2 << ")\n";
  //oimo cerr << "LINE("<< s1 <<"," << t1 <<")-("<<s2 << "," << t2 << ")\n";
 
  double dx = x2-x1;
  double dy = y2-y1;
  double ds = s2-s1;
  double dt = t2-t1;
  double sx = s1-x1;
  double ty = t1-y1;

  // now the matrix form is
  //
  //  | dx  -ds || p |   | sx |
  //  |         ||   | = |    |
  //  | dy  -dt || q |   | ty |
  //

  
  double det = dx * (-dt) - (-ds * dy);

  // if det is not zero, there is a interconnection


  //  | p |    1  | -dt  ds || sx |
  //  |   | =-----|         ||    |
  //  | q |   det | -dy  dx || ty |

  //oimo cerr << "det = " << det << endl;

  if(det != 0.0 ) {
    double p = (-dt * sx + ds * ty) /det;
    double q = (-dy * sx + dx * ty) /det;

    if( s1 == x1 && t1 == y1) {
      //oimo cerr << "They are not parallel, but share (x1,y1):(s1,t1)\n";
      return(0);
    }

    if( s1 == x2 && t1 == y2) {
      //oimo cerr << "They are not parallel, but share (x2,y2):(s1,t1)\n";
      return(0);
    }

    if( s2 == x1 && t2 == y1) {
      //oimo cerr << "They are not parallel, but share (x1,y1):(s2,t2)\n";
      return(0);
    }

    if( s2 == x2 && t2 == y2) {
      //oimo cerr << "They are not parallel, but share (x2,y2):(s2,t2)\n";
      return(0);
    }


    if( p > 0.0 && p < 1.0 && q > 0.0 && q < 1.0) {

      // This means the intersection is inside of both lines.

      //oimo cerr << "Intersection (not parallel)\n";
      return(1);
    }
    else {
      if( p == 0.0 || q == 0.0 || p == 1.0 || q == 1.0) {
	//
	//oimo cerr << "They are connecting line.\n";
	return(0);
      }	

      // Intersection is not inside the both segments.
      //oimo cerr << "not parallel and not intersect\n";
      return(0);
    }
  }

  // det == 0
  else {

    // parallel or two lines are on the same line.
    //
    // The possibilities are,
    // 1) they are purly on different line
    // 2) they are on the same line and have intersection
    // 3) they are on the same line but they don't have intersection.
    //
    // in order to treat generally, the first line specified by
    //
    // (X,Y) = t(x2-x1,y2-y1) + (x1,y1)
    // 
    //    X  = t * dx + x1
    //    Y  = t * dy + y1
    //
    // Delete t and get the relation ship between X, Y becomes,
    //
    //  dy * X - dx * Y =  dy * x1 - dx * y1
    //
    //  if dy * (s1) - dx * (t1) not equal to dy * x1 - dx * y1,
    //  it is the case 1).

    if(dy * s1 - dx * t1 != dy * x1 - dx * y1) {
      //oimo cerr << "parallel, but on different line\n";
      return (0);   // they are on different parallel lines.
    }
    else {
      // They are on the same line.............
      //  Have common intersection or just a neibour line...
      //
      //  can be solve p and q
      //  (s1,t1) = p *(dx,dy) + (x1,y1) 
      //  (s2,t2) = q *(dx,dy) + (x1,y1)
      //
      //  p = (s1-x1)/dx = (t1-y1)/dy
      //  q = (s2-x1)/dx = (t2-y1)/dy
      //

      double p,q;
      if(dx != 0) {
	p = (s1-x1)/dx;
	q = (s2-x1)/dx;
      }
      else {

	if(dy == 0) {
	  //oimo cerr << "Jesus, dx == dy == 0 !!!(isIntersectTwoLine)\n";
	}

	p = (t1-y1)/dy;
	q = (t2-y1)/dy;
      }
      
      if( p * q == 0.0 && (p == 1.0 || q == 1)) {
	// this means same line...
	//oimo cerr << "they are identical line\n";
	return(1);
      }

      // (x1,y1)  (x2,y2)
      //   +--------+========+
      //          (s1,t1)   (s2,t2)
      //  or      (s2,t2)   (s1,t1)
      if(( p == 1.0 || q == 1.0) && p*q > 1.0) {
	//oimo cerr << "(x2,y2) is the start point of line 2\n";
	return(0);
      }
    
      //              (x1,y1)  (x2,y2)
      //       +=========+--------+
      //    (s1,t1)   (s2,t2)
      // or (s2,t2)   (s1,t1)

      if((p == 0.0 && q < 0.0) || (q == 0.0 && p < 0.0 )) {
	//oimo cerr << "(x1,y1) is the start point of line 2\n";
	return(0);

      }

      //    intersection (share a common segment)
      //
      //         (x1,y1)     (x2,y2)
      //       +====+=====+-----+
      //    (s1,t1)   (s2,t2)
      

      if(  0.0 < p && p < 1.0 ) {
	//oimo cerr << "(s1,t1) is in the line (x1,y1)-(x2,y2).\n";
	return (1);
      }
      if(  0.0 < q && q < 1.0 ) {
	//oimo cerr << "(s2,t2) is in the line (x1,y1)-(x2,y2).\n";
	return (1);
      }

      // otherwise
      //                    (x1,y1)  (x2,y2)
      //       +=========+     +--------+
      //    (s1,t1)   (s2,t2)                    etc.

      //oimo cerr << "they are on the same line, but no intersection\n";
      return(0);

    } //

  }
  assert(1==0);   // never comes here
}
