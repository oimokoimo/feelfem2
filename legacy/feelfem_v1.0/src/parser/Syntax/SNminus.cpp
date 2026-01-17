/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNminus.cpp
 *  Date     : 2001/03/12
 *  Modified : 
 *  
 *  Purpose  :
 *  
 */

#include <stdio.h>                               // for sprintf
#include "../../class/feelfuncs.hpp"
#include "SNminus.hpp"

void SNminus::exprPrint( char *buf, int flag , void *ptr1,void *ptr2) 
{

  int charPointer;
  
  charPointer = CstringLength(buf);
  if(charPointer + 1 + 1 > MAX_EXPRPRINT_BUF) {
    abortExit("Too long expression in SNminus");
  }
  *(buf+charPointer  ) = '-' ;
  *(buf+charPointer+1) = '\0';

  arg->exprPrint(buf,flag,ptr1,ptr2);


  return;
}

int SNminus::howManyNotDefinedVariable(int flag , void *ptr1,void *ptr2) 
{
  int ret;
  ret = arg->howManyNotDefinedVariable(flag,ptr1,ptr2);
  return( ret );
}

int SNminus::howManyNotDefinedFunction(int flag , void *ptr1,void *ptr2) 
{
  int ret;
  ret = arg->howManyNotDefinedFunction(flag,ptr1,ptr2);
  return( ret );
}

int SNminus::howManyNotAssignedVariable(int flag , void *ptr1,void *ptr2) 
{
  int ret;
  ret = arg->howManyNotAssignedVariable(flag,ptr1,ptr2);
  return( ret );
}
