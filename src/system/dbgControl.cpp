/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : dbgControl.cpp
 *  Date     : 2001/12/17
 *  Modified : 
 *  
 *  Purpose  : debugging control program
 *             dbgOpenpl();  2001/12/17
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

#include "dbgFunctions.hpp"
#include "xplotfuncs.hpp"

void dbgOpenpl(void)
{
  openpl();
  return;
}

void dbgOpenpl(int a, int b)
{
  openpl(a,b);
  return;
}
