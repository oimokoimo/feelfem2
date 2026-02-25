/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : Neumann_InfoGenerate.cpp
 *  Date     : 2002/04/08
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

#include <iostream>

#include "feelfuncs.hpp"

#include "Neumann.hpp"
#include "IntegrandSet.hpp"
#include "DiscretizedComponent.hpp"
#include "Quadrature.hpp"

#include "BoundaryElementNodePattern.hpp"

void Neumann::discretizeInfoGenerate(void)
{
  // Set NPG, number of gauss points
  qPtr  = bIntegrandSetPtr->GetQuadraturePtr();
  NPG   = qPtr->GetQuadraturePoints();

  // set NDF, number of freedom
  NDF   = dcPtr->GetRows();    // assert(n==m) in constructor

  // has matrix entry?
  matNonZero = dcPtr->GetMatrixNonZero();

  
  MakeBoundaryElementNodePattern();

  return;

}

// different from SolveElement case, it is called from above function
void Neumann::MakeBoundaryElementNodePattern(void)
{
  nBENPPtr = new BoundaryElementNodePattern;

  listIterator <Variable *>itrU(unknownVarPtrLst);
  for(itrU.init(); !itrU ; ++itrU) {
    nBENPPtr->AddUnknownVariable( itrU() );
  }

  listIterator <Variable *>itrA(varPtrLst);
  for(itrA.init(); !itrA ; ++itrA) {
    nBENPPtr->AddNodeByVariable( itrA() );
  }

  // transfer element
  nBENPPtr->AddNodeByElement( parametricElementPtr );

  nBENPPtr->MakePattern();  // this is for this Neumann data

  // Set nodes (ielem nodes for boundary element)
  nodes = nBENPPtr->GetNodes();

  return;
}


