/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SolveElement_Infogenerate.cpp
 *  Date     : 2002/02/01
 *  Modified : 
 *  
 *  Purpose  : make ElementNodePattern
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

#include "SolveElement.hpp"
#include "ElementNodePattern.hpp"

#include "EcalInfo.hpp"

// called from SNsolve_Infogenerate.cpp
void SolveElement::MakeElementNodePattern(void)
{
  seENPPtr = new ElementNodePattern;

  listIterator <Variable *>itrU(unknownVarPtrLst);
  for(itrU.init(); !itrU ; ++itrU) {
    seENPPtr->AddUnknownVariable( itrU() );
  }

  listIterator <Variable *>itrA(varPtrLst);
  for(itrA.init(); !itrA ; ++itrA) {
    seENPPtr->AddNodeByVariable( itrA() );
  }

  // transfer element
  seENPPtr->AddNodeByElement( parametricElementPtr );
  seENPPtr->MakePattern();  // this is for this SolveElemnet

  return;
}

// called from SNsolve_Infogenerate.cpp
void SolveElement::SetIENPIEDP(void)
{
  ndf  = seENPPtr-> GetTotalFreedom();
  nedf = seENPPtr-> GetEwiseFreedom();
  iedp = seENPPtr-> MakeIEDPcopy();
  ienp = seENPPtr-> MakeIENPcopy();

  return;
}

void SolveElement::SetNENFRE(void)
{
  nodes= seENPPtr-> GetNodes();
  nodeFreedom = seENPPtr->MakeNENFREcopy();

  ielemNodes = nodes;   //   20020206
  
  return;
}
