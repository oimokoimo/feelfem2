/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNfemVar_CHECK.cpp
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

#include "SNfemVar.hpp"
#include "Object.hpp"
#include "feelfuncs.hpp"

int SNfemVar::IsDefinedElement()
{
  return( feelfemobj.IsDefinedElementName ( elementName ) );
}
