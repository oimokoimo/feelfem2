/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : BoundaryGalerkinMethod.cpp
 *  Date     : 2002/03/29  (copy of GalerkinMethod.cpp)
 *  Modified : 
 *  
 *  Purpose  : Galerkin method for Boundary integration term
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

#include "feeldef.hpp"

#include "BoundaryGalerkinMethod.hpp"
#include "Variable.hpp"
#include "IntegrandSet.hpp"

BoundaryGalerkinMethod::BoundaryGalerkinMethod()
{
  // initialization in constructor 
  unknowns   = 0;
  totalDOF   = 0;
  equations  = 0;
  elements   = 0;

  // Variable information   (pointers)   (not used....)
  variables     = 0;
  elementNo     = 0;
  degOfFreedom  = 0;
  startingSblNo = 0;
  varType       = 0;
  ewiseType     = 0;

  parametricElemPtr = 0;

  nxFlag = NO;
  nyFlag = NO;
  nzFlag = NO;

  return;
}

BoundaryGalerkinMethod::~BoundaryGalerkinMethod() = default;


void BoundaryGalerkinMethod::SetNumberOfUnknowns(int n)
{
  unknowns = n;
  return;
}

void 
BoundaryGalerkinMethod::SetBoundaryIntegrandSetPtr(BoundaryIntegrandSet *ptr)
{
  weakIntegrandPtr = ptr;
  return;
}

void BoundaryGalerkinMethod::SetParametricElementPtr( Element *ptr )
{
  assert(ptr != 0);
  parametricElemPtr = ptr;
  return;
}

void BoundaryGalerkinMethod::AddUnknownVariablePtr( Variable *ptr)
{
  unknownVarPtrLst.addlast(ptr);
  return;
}
  
void BoundaryGalerkinMethod::AddTestfuncStr( string nm)
{
  testfuncStrLst.addlast(nm);
  return;
}

void BoundaryGalerkinMethod::UseNX()
{
  nxFlag = YES;
  return;
}

void BoundaryGalerkinMethod::UseNY()
{
  nyFlag = YES;
  return;
}

void BoundaryGalerkinMethod::UseNZ()
{
  nzFlag = YES;
  return;
}
