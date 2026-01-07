/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : GetBoundaryInterp_cube.cpp
 *  Date     : 2002/03/26
 *  Modified : 
 *  
 *  Purpose  : Generate boundary interpolation function with node
 *  
 */
#include <assert.h>
#include <iostream.h>

#include "Interpolation.hpp"

Interpolation *Interpolation::GetBoundaryInterp_cube(void)
{
  // reference face is (0,0) - (1,0) with 'r'


  // s == 0
  cerr << "UN Interpolation *Interpolation::GetBoundaryInterp_cube(void)\n";
  assert(1==0);
  
  return(0);
}
