/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : Label.cpp
 *  Date     : 2002/07/19 (aist)
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

#include "Label.hpp"

int Label::labels = 0;

Label::Label(const char *nm)
{
  name    = nm;

  labels++;
  labelNo = labels;

  return;
}

Label::~Label() = default;


int Label::GetLabelNo(void)
{
  return( labelNo );
}

const char *Label::GetName(void)
{
  return ( (const char *)name);

}
