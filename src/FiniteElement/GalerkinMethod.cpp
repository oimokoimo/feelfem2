/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : GalerkinMethod.cpp
 *  Date     : 2002/01/30
 *  Modified : 
 *  
 *  Purpose  : Galerkin method 
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

#include "GalerkinMethod.hpp"
#include "Variable.hpp"
#include "IntegrandSet.hpp"


GalerkinMethod::GalerkinMethod()
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


  return;
}

GalerkinMethod::~GalerkinMethod() = default;
/*
{
  unknownVarPtrLst.~list();
  testfuncStrLst.~list();
  elementPtrLst.~list();

  return;
}
*/


void GalerkinMethod::SetNumberOfUnknowns(int n)
{
  unknowns = n;
  return;
}

void GalerkinMethod::AddUnknownVariablePtr( Variable *ptr)
{
  unknownVarPtrLst.addlast(ptr);
  return;
}
  
void GalerkinMethod::AddTestfuncStr( string nm)
{
  testfuncStrLst.addlast(nm);
  return;
}

void GalerkinMethod::SetIntegrandSetPtr( IntegrandSet *ptr)
{
  weakIntegrandPtr = ptr;
  return;
}

void GalerkinMethod::SetParametricElementPtr( Element *ptr )
{
  assert(ptr != 0);
  parametricElemPtr = ptr;
  return;
}
