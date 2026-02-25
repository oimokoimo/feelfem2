/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SolveElement_CodeGenerateSub.cpp
 *  Date     : 2002/02/19
 *  Modified : 
 *  
 *  Purpose  : Utility functions while code generation
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

int *SolveElement::GetNodePatternForEcal(Variable *vPtr)
{
  int *ret;

  ret = seENPPtr->MakeNodeInfoForFEMvar( vPtr );

  return(ret);
}

// this is for parametric element
int *SolveElement::GetNodePatternForEcal(Element *ePtr)
{
  int *ret;

  ret = seENPPtr->MakeNodeInfoForFEMvar( ePtr );

  return(ret);
}
