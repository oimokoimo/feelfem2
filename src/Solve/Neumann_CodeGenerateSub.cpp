/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : Neumann_CodeGenerateSub.cpp
 *  Date     : 2002/04/10
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

#include "Neumann.hpp"
#include "BoundaryElementNodePattern.hpp"

int *Neumann::GetNodePatternForEcal(Variable *vPtr)
{
  int *ret;

  ret = nBENPPtr->MakeNodeInfoForFEMvar( vPtr );

  return(ret);
}

// this is for parametric element
int *Neumann::GetNodePatternForEcal(Element *ePtr)
{
  int *ret;

  ret = nBENPPtr->MakeNodeInfoForFEMvar( ePtr );

  return(ret);
}
