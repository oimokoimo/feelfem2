/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNidentifierlist.cpp
 *  Date     : 2001/02/23
 *  Modified : 
 *  
 *  Purpose  : Identifier list
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
#include "../../class/string.hpp"
#include "../../class/list.hpp"
#include "SNidentifierlist.hpp"

SNidentifierlist::SNidentifierlist(int n) :
  SNunit("identifierlist",SN_IDENTIFIERLIST)
{
  elements = n;
  if(elements > 0) {
    contents = new SNname *[elements];
  }
  else {
    contents = 0;
  }
  for(int i=0; i< elements; i++) contents[i] = 0;

  return;
}

SNidentifierlist::~SNidentifierlist()
{
  for(int i=0;i < elements;i++) {
    if(contents[i]) delete contents[i];
  }
  delete[] contents;
  return;
}

void SNidentifierlist::print(std::ostream& ost)
{
	std::cerr << "welcome to identifierlist.print\n";

  ost << "(";
    
  if(elements == 0) {
    ost << "*NULL*";
  }
  else {
    for(int i=0;i<elements;i++) {
      if(i>0) ost << ",";
      (contents[i])->print(ost);
    }
  }
  ost << ")";
  return;
}

void SNidentifierlist::StoreContentsInStringLst(list<string>&strLst)
{
  for(int i=0;i<elements;i++) {
    SNname  *nmPtr;
    nmPtr = *(contents+i);
    strLst.addlast( (const char *)(*nmPtr) );
  }
  return;
}

