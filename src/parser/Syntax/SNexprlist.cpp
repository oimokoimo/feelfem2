/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNexprlist.cpp
 *  Date     : 2001/02/21
 *  Modified : 
 *  
 *  Purpose  :
 *  
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

#include "SNexprlist.hpp"

SNexprlist::SNexprlist(int n) : SNunit("exprlist",SN_EXPRLIST)
{
  elements = n;
  if(elements > 0) {
    contents = new SNunit *[elements];
  }
  else {
    contents = nullptr;
  }
  for(int i=0; i< elements; i++) contents[i] = 0;

  return;
}

SNexprlist::~SNexprlist()
{
  for(int i=0;i < elements;i++) {
    if(contents[i]) delete contents[i];
  }
  delete[] contents;
  return;
}

void SNexprlist::print(std::ostream& ost)
{
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

void SNexprlist::exprPrint( char *buf, int flag , void *ptr1,void *ptr2) 
{

  int charPointer;

  switch(flag) {
  case EXPRPRINT_NORMAL:
  case EXPRPRINT_SIMPLE:
  case EXPRPRINT_REPLACE_EVAL:
  case EXPRPRINT_REPLACE_EVALPAIR:

    for(int i=0;i<elements;i++) {

      if(i != 0) {
	charPointer = stringLength(buf);
	if(charPointer + 1 + 1 > MAX_EXPRPRINT_BUF) {
	  abortExit("Too long expression in SNexprlist");
	}
	*(buf+charPointer  ) = ',';
	*(buf+charPointer+1) = '\0';
      }

      SNunit *ptr = contents[i];
      ptr->exprPrint(buf,flag,ptr1,ptr2);
    }
    break;
      
  default:
    abortExit("Illegal code for flag in SNexprlist::exprPrint");
  }

  return;
}

int SNexprlist::howManyNotDefinedVariable(int flag , void *ptr1,void *ptr2) 
{
  int ret;
  ret = 0;
  for(int i=0;i<elements;i++) {
    SNunit *ptr = contents[i];
    ret = ret + ptr->howManyNotDefinedVariable(flag,ptr1,ptr2);
  }
  return(ret);
}

int SNexprlist::howManyNotDefinedFunction(int flag , void *ptr1,void *ptr2) 
{
  int ret;
  ret = 0;
  for(int i=0;i<elements;i++) {
    SNunit *ptr = contents[i];
    ret = ret + ptr->howManyNotDefinedFunction(flag,ptr1,ptr2);
  }
  return(ret);
}

int SNexprlist::howManyNotAssignedVariable(int flag , void *ptr1,void *ptr2) 
{
  int ret;
  ret = 0;
  for(int i=0;i<elements;i++) {
    SNunit *ptr = contents[i];
    ret = ret + ptr->howManyNotAssignedVariable(flag,ptr1,ptr2);
  }
  return(ret);
}
