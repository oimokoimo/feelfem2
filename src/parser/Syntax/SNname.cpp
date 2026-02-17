/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNname.cpp
 *  Date     : 2001/02/19
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

#include "SNname.hpp"

SNname::SNname(const char *ptr)
{
  name=ptr;
  return;
}

SNname::~SNname()
{
  name.~string();
  return;
}

SNname::operator const char * () const
{
   return ((const char *)name);
}
