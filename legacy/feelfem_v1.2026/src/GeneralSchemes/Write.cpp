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
 */


#include "Write.hpp"

Write::Write(void)
{
  return;
}

Write::~Write(void)
{
  // do nothing now
}

void Write::AddLastItem(char *s)
{
  itemStrLst.addlast(s);
  return;
}

void Write::AddLastItemType(int n)
{
  itemTypeLst.addlast(n);
  return;
}
