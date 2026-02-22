/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : Function.cpp
 *  Date     : 2002/09/12
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

#include "Function.hpp"

#include "Object.hpp"
#include "feelfuncs.hpp"

Function::Function(const char *nm, int n)
{

  name      = nm;
  arguments = n;

  tcno = feelfemobj.GetUserFunctionTCno(arguments);
  return;
}

Function::~Function() = default;

int Function::GetFunctionTCno(void)
{
  return tcno;
}
