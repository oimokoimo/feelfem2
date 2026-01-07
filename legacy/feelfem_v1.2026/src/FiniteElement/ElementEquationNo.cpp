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
 */

#include <assert.h>

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
  varName.~string();

  delete ienp;
  delete iedp;

  return;
}

void ElementEquationNo::SetIthIenpIedp(int i, int np, int dp)
{
  assert( 0<= i && i < freedom);

  *(ienp + i) = np;
  *(iedp + i) = dp;

  return;
}
