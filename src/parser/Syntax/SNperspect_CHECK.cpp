/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNperspect_CHECK.cpp
 *  Date     : 2002/01/21
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
#include "SNperspect.hpp"
#include "Expression.hpp"

int SNperspect::checkExprWellDefined(void)
{
  int ret;

  SNunit *suPtr = this;

  ret = exprPtr->checkDefinedFEMObjectSN(suPtr);

  return(ret);

}
