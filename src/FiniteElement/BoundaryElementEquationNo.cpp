/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : BoundaryElementEquationNo.cpp
 *  Date     : 2002/04/09 (copy of ElementEquationNo.cpp)
 *  Modified : 
 *  
 *  Purpose  : BoundaryElementEquationNo class implementation
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

#include <cassert>

// BoundaryElementEquationNo is declared here.
#include "BoundaryElementNodePattern.hpp"  

BoundaryElementEquationNo::BoundaryElementEquationNo( const char *nm , int dof)
{
  varName = nm;
  freedom = dof;
  
  assert (dof >0);
  
  ienp = new int[dof];
  iedp = new int[dof];

  return;
}

BoundaryElementEquationNo::~BoundaryElementEquationNo(void) {
  // destructor
  // string member instance is cleared by c++

  delete []ienp;
  delete []iedp;

  return;
}

void BoundaryElementEquationNo::SetIthIenpIedp(int i, int np, int dp)
{
  assert( 0<= i && i < freedom);

  *(ienp + i) = np;
  *(iedp + i) = dp;

  return;
}
