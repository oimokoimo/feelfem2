/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNdiv.cpp
 *  Date     : 2001/03/13
 *  Modified : 
 *  
 *  Purpose  :
 *  
 */

#include <stdio.h>                               // for sprintf
#include "../../class/feelfuncs.hpp"
#include "SNdiv.hpp"

void SNdiv::exprPrint( char *buf, int flag , void *ptr1,void *ptr2) 
{
  int charPointer;

  switch(flag) {
  case EXPRPRINT_NORMAL:
  case EXPRPRINT_SIMPLE:
  case EXPRPRINT_REPLACE_EVAL:
  case EXPRPRINT_REPLACE_EVALPAIR:

    arg1->exprPrint(buf,flag,ptr1,ptr2);

    charPointer = CstringLength(buf);

    if(charPointer + 1 + 1 > MAX_EXPRPRINT_BUF) {
      abortExit("Too long expression in SNdiv");
    }
    *(buf+charPointer  ) = '/' ;
    *(buf+charPointer+1) = '\0';

    arg2->exprPrint(buf,flag,ptr1,ptr2);

    break;
      
  default:
    abortExit("Illegal code for flag in SNdiv::exprPrint");
  }

  return;
}

int SNdiv::howManyNotDefinedVariable(int flag , void *ptr1,void *ptr2) 
{
  int ret1,ret2;

  ret1 = (arg1->howManyNotDefinedVariable(flag,ptr1,ptr2));
  ret2 = (arg2->howManyNotDefinedVariable(flag,ptr1,ptr2));
  return(ret1+ret2);
}


int SNdiv::howManyNotDefinedFunction(int flag , void *ptr1,void *ptr2) 
{
  int ret1,ret2;

  ret1 = (arg1->howManyNotDefinedFunction(flag,ptr1,ptr2));
  ret2 = (arg2->howManyNotDefinedFunction(flag,ptr1,ptr2));
  return(ret1+ret2);
}

int SNdiv::howManyNotAssignedVariable(int flag , void *ptr1,void *ptr2) 
{
  int ret1,ret2;

  ret1 = (arg1->howManyNotAssignedVariable(flag,ptr1,ptr2));
  ret2 = (arg2->howManyNotAssignedVariable(flag,ptr1,ptr2));
  return(ret1+ret2);
}
