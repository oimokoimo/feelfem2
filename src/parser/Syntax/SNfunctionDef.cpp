/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNfunctionDef.cpp
 *  Date     : 2002/09/12
 *  Modified : 
 *  
 *  Purpose  : function definition
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
#include <iostream>

#include "SNfunctionDef.hpp"

SNfunctionDef::SNfunctionDef( const char *nm , SNidentifierlist *ptr) 
    : SNunit("functionDef", SN_FUNCTIONDEF) 
{
  name = nm;
  identifierLst = ptr;
  return;
}

void SNfunctionDef::print(std::ostream &ost)
{
  ost << "functionDef " << name << " ";
  identifierLst->print(ost);
  return;
}

int SNfunctionDef::GetNumberOfArgs(void)
{
  return identifierLst->GetNumberOfElements();
}

