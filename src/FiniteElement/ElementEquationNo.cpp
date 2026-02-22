/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : ElementEquationNo.cpp
 *  Date     : 2002/02/01
 *  Modified : 
 *  
 *  Purpose  : ElementEquationNo class implementation
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

#include "ElementNodePattern.hpp"  // ElementEquationNo is declared here.

ElementEquationNo::ElementEquationNo( const char *nm , int dof)
{
  varName = nm;
  freedom = dof;
  
  assert (dof >0);
  
  ienp = new int[dof];
  iedp = new int[dof];

  return;
}

ElementEquationNo::~ElementEquationNo(void)
{
  // destructor

  delete []ienp;
  delete []iedp;

  return;
}

void ElementEquationNo::SetIthIenpIedp(int i, int np, int dp)
{
  assert( 0<= i && i < freedom);

  *(ienp + i) = np;
  *(iedp + i) = dp;

  return;
}
