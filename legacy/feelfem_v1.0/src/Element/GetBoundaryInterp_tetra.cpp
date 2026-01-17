/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : GetBoundaryInterp_tetra.cpp
 *  Date     : 2002/03/26
 *  Modified : 
 *  
 *  Purpose  : Generate boundary interpolation function with node
 *  
 */
#include <assert.h>
#include <iostream.h>

#include "Interpolation.hpp"

Interpolation *Interpolation::GetBoundaryInterp_tetra(void)
{
  // reference face is (0,0) - (1,0) with 'r'

  // s == 0

  cerr << "UC Interpolation *Interpolation::GetBoundaryInterp_tetra(void)\n";
  assert(1==0);
  return(0);
}
