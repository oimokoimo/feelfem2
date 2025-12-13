/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SolveObject.cpp
 *  Date     : 2002/03/07
 *  Modified : 2002/06/27  (GetIthSolvePtr  for solv_dat)
 *  
 *  Purpose  :
 *  
 */

#include <assert.h>

#include "list.hpp"

#include "Solve.hpp"
#include "Object.hpp"

int Object::HowManySolves()
{
  return solves;
}

void Object::StoreSolve( Solve *solvePtr)
{
  solves++;
  
  solvePtrLst.addlast(solvePtr);
}

Solve* Object::GetIthSolvePtr(int i)
{
  assert(i < solves);

  Solve *sPtr = solvePtrLst.getNthElement(i+1);
  
  return(sPtr);
}
  
