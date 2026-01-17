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
 */
#include "../../class/string.hpp"
#include "../../class/list.hpp"
#include "SNidentifierlist.hpp"

SNidentifierlist::SNidentifierlist(int n) :
  SNunit("identifierlist",SN_IDENTIFIERLIST)
{
  elements = n;
  if(elements > 0) {
    contents = new (SNname *)[elements];
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
  delete contents;
  return;
}

void SNidentifierlist::print(ostream& ost)
{
  cerr << "welcome to identifierlist.print\n";

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

