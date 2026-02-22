/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : evalNodeOrder.cpp
 *  Date     : 2002/01/01
 *  Modified : 
 *  
 *  Purpose  : evaluation of point order in element
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
#include <cmath>      // for std::abs


#define EVALNODE_EPS    1.0e-10



//
// eval line   -1 to 1   x--------------x 
//                      0.0            1.0
//                 
// range   ret = 0.0,1.0, 1,0< ret < 2.0


double evalNodePoint(void)
{
  return(0.0);
}


double evalNodeLine(double xi)
{
  if(xi == 0.0) return (0.0);
  if(xi == 1.0) return (1.0);

  return(xi+1.0);
}

/*
//
// eval triangle
//
//      3
//      +
//      |\
// 5.0->| \     <- 4.0
//      |  \                   midpoint = 10.0
//      | 6 \
//      +----+     <- 3.0
//     1      2
*/

double evalNodeTri(double xi,double eta)
{
  if(xi == 0.0 && eta == 0.0) return(0.0);
  if(xi == 1.0 && eta == 0.0) return(1.0);
  if(xi == 0.0 && eta == 1.0) return(2.0);

  if(eta      == 0.0) return( 3.0 +  xi);
  if(std::abs((xi + eta-1.0))<EVALNODE_EPS) {
    return( 5.0 -  xi);
  }
  if(xi       == 0.0) return( 6.0 - eta);

  if( (xi -(1.0/3.0))*(xi -(1.0/3.0)) +
      (eta-(1.0/3.0))*(eta-(1.0/3.0))  < EVALNODE_EPS) {

    return(10.0);
  }


  return(xi+eta+6.0 );
}  

//
// eval rectangle
//
//       4 7[6.x]   3
//       +---------+ 
//       |         |
// 8[7.x]|  [9.x]  |6[5.x]    midpoint = 20.0
//       |         |
//       |         |
//       +---------+ 
//      1   5[4.x]  2
//

double evalNodeRect(double xi,double eta)
{
  if(xi == -1.0 && eta == -1.0) return(0.0);
  if(xi ==  1.0 && eta == -1.0) return(1.0);
  if(xi ==  1.0 && eta ==  1.0) return(2.0);
  if(xi == -1.0 && eta ==  1.0) return(3.0);
  
  if(eta  == -1.0) return( 4.0 + ( xi+1.0)/2.0);
  if(xi   ==  1.0) return( 5.0 + (eta+1.0)/2.0);
  if(eta  ==  1.0) return( 6.0 + (1.0- xi)/2.0);
  if(xi   == -1.0) return( 7.0 + (1.0-eta)/2.0);

  if(xi == 0.0 && eta == 0.0) return(20.0);

  return(9.0 + (eta + 1.0)/2.0 * 10.0 + (xi+1.0)/2.0);
}

// eval tetrapod
//
//
//
//    |
//    |
//    |
//    |
//
//
//
double evalNodeTetra(double xi,double eta,double zeta)
{
  // mid point
  if(xi == 0.25 && eta == 0.25 && zeta == 0.25) return(0.0);  //bug?  it was 1.0...

  // No.1 (0,0,0)
  if(xi == 0.0 && eta == 0.0 && zeta == 0.0) return(1.0);

  // No.2 (1,0,0)
  if(xi == 1.0 && eta == 0.0 && zeta == 0.0) return(2.0);

  // No.3 (0,1,0)
  if(xi == 0.0 && eta == 1.0 && zeta == 0.0) return(3.0);
  
  // No.4 (0,0,1)
  if(xi == 0.0 && eta == 0.0 && zeta == 1.0) return(4.0);


  // 6 edges

  // Edge No.1 to No.2 (x-axis)                 10.0 < val < 11.0
  if(zeta == 0.0 && eta == 0.0)   return (10.0 + xi );

  // Edge No.2 to No.3 (zeta = 0, xi+eta = 1.0  12.0 < val < 13.0
  if(std::abs((xi + eta-1.0))<EVALNODE_EPS && zeta == 0.0) {
    return(12.0+ (1.0  -  xi) );
  }

  // Edge No.3 to No.1 (eta-axis)               14.0 < val < 15.0
  if(xi == 0.0 && zeta == 0.0)   return( 14.0 + (1.0 - eta));

  // Edge No.1 to No.4 (zeta-axis)              16.0 < val < 17.0
  if(xi == 0.0 && eta  == 0.0)   return( 16.0 + zeta );

  // Edge No.2 to No.4 (eta = 0, xi+zeta = 1.0  18.0 < val < 19.0
  if(std::abs((xi+zeta-1.0))<EVALNODE_EPS && eta == 0.0) {
    return(18.0 + zeta);
  }

  // Edge No.3 to No.4 (xi = 0,etai+zeta = 1.0  20.0 < val < 21.0
  if(std::abs((eta+zeta-1.0))<EVALNODE_EPS && xi == 0.0) {
    return(20.0 + zeta);
  }


  // on face, only barycentric center points are allowed.

  
  // center point on the face against No.1          val = 100.0
  if( (xi  -(1.0/3.0))*(xi  -(1.0/3.0)) +
      (eta -(1.0/3.0))*(eta -(1.0/3.0)) +
      (zeta-(1.0/3.0))*(zeta-(1.0/3.0))  < EVALNODE_EPS) {
    return(100.0);
  }


  // center point on the face against No.2          val = 200.0
  if( xi == 0.0 &&
      (eta -(1.0/3.0))*(eta -(1.0/3.0)) +
      (zeta-(1.0/3.0))*(zeta-(1.0/3.0))  < EVALNODE_EPS) {
    return(200.0);
  }

  // center point on the face against No.3          val = 300.0
  if( eta == 0.0 &&
      (xi  -(1.0/3.0))*(xi  -(1.0/3.0)) +
      (zeta-(1.0/3.0))*(zeta-(1.0/3.0))  < EVALNODE_EPS) {
    return(300.0);
  }
  // center point on the face against No.4          val = 400.0
  if( zeta == 0.0 &&
      (xi  -(1.0/3.0))*(xi  -(1.0/3.0)) +
      (eta -(1.0/3.0))*(eta -(1.0/3.0))  < EVALNODE_EPS) {
    return(400.0);
  }

  std::cerr << "Illegal node position in Tetrahedra\n";
  std::cerr << "xi   = " << xi   <<std::endl;
  std::cerr << "eta  = " << eta  <<std::endl;
  std::cerr << "zeta = " << zeta <<std::endl;

  exit(1);
}

double evalNodeCube(double xi,double eta,double zeta)
{
	std::cerr<< "FiniteElement/evalNodeOrder.cpp evelNodeCube() is underconstruct\n";
  exit(1);
}
