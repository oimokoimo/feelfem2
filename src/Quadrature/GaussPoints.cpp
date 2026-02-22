/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : GaussPoint.cpp
 *  Date     : 2001/12/10
 *  Modified : 
 *  
 *  Purpose  : Gauss point control
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
#include <cassert>

#include "Quadrature.hpp"



GaussPoints::GaussPoints()
{
  dimension = 0;
  points    = 0;
  x = y = z = nullptr;
  return;
}

GaussPoints::~GaussPoints()
{
  delete [] x;
  delete [] y;
  delete [] z;

  x = y = z = nullptr;
}

int GaussPoints::GetQuadraturePoints(void)
{
  return(points);
}

int GaussPoints::GetDimension(void)
{
  return(dimension);
}

void GaussPoints::SetDimensionAndPoints(int ndim, int pts)
{
  dimension = ndim;
  points    = pts;


  if(ndim < 1  || ndim > 3) {
    std::cerr << "GaussPoints::SetDimensionAndPoints ndim = " << ndim << std::endl;
    exit(1);
  }

  if(pts < 1 ) {
    std::cerr << "GaussPoints::SetDimensionAndPoints pts = " << pts << std::endl;
    exit(1);
  }


  // allocate array for weight
  w  =  new double[points];

  // allocate arrays for coordinates
  switch(ndim) {
  case 1:
    x = new double[points];
    break;

  case 2:
    x = new double[points];
    y = new double[points];
    break;

  case 3:
    x = new double[points];
    y = new double[points];
    z = new double[points];
    break;

  default:
    assert(1 == 2);
    break;
  }
  return;
}

// Int starts from 0
void GaussPoints::SetIthCoordinate(int i,double xval)
{
  assert(i  >= 0 && i < points);

  *(x+i) = xval;
  return;
}

void GaussPoints::SetIthCoordinate(int i,double xval,double yval)
{
  assert(i  >= 0 && i < points);

  *(x+i) = xval;
  *(y+i) = yval;
  return;
}

void GaussPoints::SetIthCoordinate(int i,double xval,double yval,double zval)
{
  assert(i  >= 0 && i < points);

  *(x+i) = xval;
  *(y+i) = yval;
  *(z+i) = zval;
  return;
}

void GaussPoints::SetIthWeight(int i,double weight)
{
  assert(i  >= 0 && i < points);

  *(w+i) = weight;
  return;
}



double GaussPoints::GetIthWeight( int i )
{
  assert( i >= 0 && i < points );
  
  return(*(w+i));
}

double GaussPoints::GetIthXi( int i )
{
  assert( i >= 0 && i < points );
  
  return(*(x+i));
}


double GaussPoints::GetIthEta( int i )
{
  assert( i >= 0 && i < points );
  
  return(*(y+i));
}

double GaussPoints::GetIthZeta( int i )
{
  assert( i >= 0 && i < points );
  
  return(*(z+i));
}
