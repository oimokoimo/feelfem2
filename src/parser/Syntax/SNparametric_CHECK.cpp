/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNparametric_CHECK.cpp
 *  Date     : 2002/07/11
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

#include "feelfem.hpp"

#include "SNparametric.hpp"
#include "Object.hpp"
#include "feelfuncs.hpp"

#include "../../check/check_funcs.hpp"

int SNparametric::IsValidParametricName(void)
{
  // Element is defined???
  if(!feelfemobj.IsDefinedElementName( parametricName ) ) {
    
    SystemErrorAStrA(this,"Element ",parametricName," is not defined.");
    return(0);
  }

  if( feelfemobj.StoreParametricElementEw( parametricName ) ) {
    
    SystemErrorA(this,"The parametric element for this element type is already defined.");
    return(0);
  }

  return(1);
}
