/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : EsetInfo.cpp
 *  Date     : 2002/03/01
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

#include "feeldef.hpp"
#include "EsetInfo.hpp"

EsetInfo::EsetInfo()
{
  dependencyFlag = NO;
  return;
}


EsetInfo::~EsetInfo() = default;

int EsetInfo::HasDependency()
{
  return(dependencyFlag);
}

list <string>&EsetInfo::GetArgStrList(void)
{
  return( argStrLst );
}


