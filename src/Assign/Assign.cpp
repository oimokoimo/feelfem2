/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : Assign.cpp
 *  Date     : 2002/04/15 (BCN)
 *  Modified : 
 *  
 *  Purpose  :
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

#include "Assign.hpp"

int Assign::totalAssigns = 0;

Assign::Assign(void)
{
  totalAssigns++;
  
  assignNo     = totalAssigns;

  geometryType       = 0;  // ASSIGN_TYPE_NORMAL,ELEM,NSET,NODE
  numberOfPlaces     = 0;  // number of associated place names

  leftVarAssignType  = 0;  // AS_VAR_TYPE_INTEGER,,,
  leftVarPtr         = 0;  // null pointer initialize

  parametricElemPtr = 0;

  userFuncs          = 0;   // user defined function

  useX         = 0;
  useY         = 0;
  useZ         = 0;

  useXval      = 0;   // used in assignEwiseQuad
  useYval      = 0;
  useZval      = 0;

  useNX        = 0;
  useNY        = 0;
  useNZ        = 0;

  useDiff1st   = 0;
  useDiff2nd   = 0;

  coroutineFlag = NO;


  // for functionals  (integral,bintegral, max,min, etc.)
  int regionalIntegralFlag = NO;
  int boundaryIntegralFlag = NO;

  return;
}

Assign::~Assign() =  default;

void Assign::AddLeftVarPtr( Variable *vPtr )
{
  leftVarPtr = vPtr;
  
  if(!varPtrLst.includes( vPtr )) {
    varPtrLst.add(vPtr);
  }
  return;
}

void Assign::AddGeomObjPtr( GeomObj *goPtr)
{
  geomObjPtrLst.addlast (goPtr);
  return;
}


// coroutine flag
int Assign::HasCoroutine(void)
{
  return(coroutineFlag);   // default is NO
}

void Assign::UseCoroutine(void)
{
  coroutineFlag = YES;
  return;
}

void Assign::AddUsedUserFuncSymbol(string &nm)
{
  userFuncStrLst.addlast(nm);
  return;
}
