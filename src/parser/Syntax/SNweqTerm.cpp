/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNweqTerm.cpp
 *  Date     : 2002/04/18 (BCN)
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

#include "feeldef.hpp"
#include "SNweqTerm.hpp"

int SNweqTerm::IsBoundaryTerm(void)
{
  if(integralType == TYPE_BOUNDARY_INTEGRAND) {
    return(YES);
  }
  else {
    return(NO);
  }
}
