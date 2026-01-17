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
 */

#include <assert.h>

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

BoundaryElementEquationNo::~BoundaryElementEquationNo(void)
{
  // destructor
  varName.~string();

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
