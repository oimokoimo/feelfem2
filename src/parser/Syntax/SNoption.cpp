/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNoption.cpp
 *  Date     : 2002/01/18
 *  Modified : 
 *  
 *  Purpose  : Option class
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

#include "SNoption.hpp"

SNoption::SNoption( const char *nm, Expression *ptr)
  :SNunit("option",SN_OPTION)
{
  optionIdentifier = nm;
  exprPtr          = ptr;
  
  return;
}

SNoption::SNoption( const char *nm, char *opt)
  :SNunit("option",SN_OPTION)
{
  optionIdentifier = nm;
  exprPtr          =  0;
  optionString     = opt;

  return;
}

void SNoption::print(std::ostream &ost)
{
  ost << "(" << optionIdentifier << "=";
  
  if(exprPtr == 0) {
    ost << optionString;
  }
  else {
    exprPtr->print(ost);
  }
  
  ost << ")";

  return;
}

Expression *SNoption::GetExprPtr(void)
{
  assert(exprPtr != 0);

  return(exprPtr);
}

void SNoption::GetValueAsString(string &str)
{
  if(exprPtr == 0) {
    str = optionString;
  }
  else {
    char buf[MAX_EXPRPRINT_BUF];
    buf[0]='\0';
    exprPtr->exprPrint(buf,EXPRPRINT_NORMAL,0,0);
    str = buf;
  }
  return;
}
