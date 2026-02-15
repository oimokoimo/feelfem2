/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNewiseVar_CHECK.cpp
 *  Date     : 2001/11/05
 *  Modified : 
 *  
 *  Purpose  : check the specified element is defined or not.
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

#include "SNewiseVar.hpp"
#include "Object.hpp"
#include "feelfuncs.hpp"

int SNewiseVar::IsValidAttribute(void)
{
  if(isAttribute == NO) {
    return(YES);   // this is material ewise variable
  }

  if(feelfemobj.IsDefinedElementName ( attributeName ) == YES) {
    return(YES);   // valid element name
  }
  
  if(feelfemobj.IsDefinedQuadratureName( attributeName ) == YES) {
    return(YES);   // valid quadrature name
  }

  return(NO);

}

	  

