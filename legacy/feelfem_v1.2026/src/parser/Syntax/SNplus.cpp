/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNplus.cpp
 *  Date     : 2001/03/12
 *  Modified : 
 *  
 *  Purpose  :
 *  
 */

#include <stdio.h>                               // for sprintf
#include "../../class/feelfuncs.hpp"
#include "SNplus.hpp"

void SNplus::exprPrint( char *buf, int flag , void *ptr1,void *ptr2) 
{

  int charPointer;

  arg1->exprPrint(buf,flag,ptr1,ptr2);

  charPointer = CstringLength(buf);

  if(charPointer + 1 + 1 > MAX_EXPRPRINT_BUF) {
    abortExit("Too long expression in SNplus");
  }
  *(buf+charPointer  ) = '+' ;
  *(buf+charPointer+1) = '\0';

  arg2->exprPrint(buf,flag,ptr1,ptr2);

  return;
}


int SNplus::howManyNotDefinedVariable( int flag , void *ptr1,void *ptr2) 
{
  int ret,ret1,ret2;

  ret1 = arg1->howManyNotDefinedVariable(flag,ptr1,ptr2);
  ret2 = arg2->howManyNotDefinedVariable(flag,ptr1,ptr2);

  ret  = ret1 + ret2;

  return(ret);
}

int SNplus::howManyNotDefinedFunction( int flag , void *ptr1,void *ptr2) 
{
  int ret,ret1,ret2;

  ret1 = arg1->howManyNotDefinedFunction(flag,ptr1,ptr2);
  ret2 = arg2->howManyNotDefinedFunction(flag,ptr1,ptr2);

  ret  = ret1 + ret2;

  return(ret);
}

int SNplus::howManyNotAssignedVariable( int flag , void *ptr1,void *ptr2) 
{
  int ret,ret1,ret2;

  ret1 = arg1->howManyNotAssignedVariable(flag,ptr1,ptr2);
  ret2 = arg2->howManyNotAssignedVariable(flag,ptr1,ptr2);

  ret  = ret1 + ret2;

  return(ret);
}

