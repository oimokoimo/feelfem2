/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNexpr.cpp
 *  Date     : 2002/11/22
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

#include "SNexpr.hpp"
#include "SNunit.hpp"

SNexpr::SNexpr(Expression *ptr) :
  SNunit("expr",SN_EXPR) 
{
  exprPtr=ptr;
  return;
}

SNexpr::~SNexpr()
{
  // do nothing now
  return;
}
