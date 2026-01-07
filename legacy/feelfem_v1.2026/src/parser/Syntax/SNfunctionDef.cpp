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
 */
#include <iostream.h>

#include "SNfunctionDef.hpp"

SNfunctionDef::SNfunctionDef( char *nm , SNidentifierlist *ptr) 
    : SNunit("functionDef", SN_FUNCTIONDEF) 
{
  name = nm;
  identifierLst = ptr;
  return;
}

void SNfunctionDef::print(ostream &ost)
{
  ost << "functionDef " << name << " ";
  identifierLst->print(ost);
  return;
}

int SNfunctionDef::GetNumberOfArgs(void)
{
  return identifierLst->GetNumberOfElements();
}

