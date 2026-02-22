/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : Write.cpp
 *  Date     : 2002/11/22
 *  Modified : 
 *  
 *  Purpose  : Write statement
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


#include "Write.hpp"

Write::Write(void)
{
  return;
}

Write::~Write(void) = default;



void Write::AddLastItem(const char *s)
{
  itemStrLst.addlast(s);
  return;
}

void Write::AddLastItemType(int n)
{
  itemTypeLst.addlast(n);
  return;
}
