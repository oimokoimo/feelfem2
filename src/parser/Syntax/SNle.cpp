/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNle.cpp
 *  Date     : 2002/07/18  (copy of SNdiv @ 2001/03/13)
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
 *
 */

#include <stdio.h>                               // for sprintf
#include "../../class/feelfuncs.hpp"
#include "SNle.hpp"

void SNle::exprPrint( char *buf, int flag , void *ptr1,void *ptr2) 
{
  int charPointer;

  switch(flag) {
  case EXPRPRINT_NORMAL:
  case EXPRPRINT_SIMPLE:
  case EXPRPRINT_REPLACE_EVAL:
  case EXPRPRINT_REPLACE_EVALPAIR:

    arg1->exprPrint(buf,flag,ptr1,ptr2);

    charPointer = CstringLength(buf);

    if(charPointer + 2 + 1 > MAX_EXPRPRINT_BUF) {
      abortExit("Too long expression in SNle");
    }
    *(buf+charPointer  ) = '<' ;
    *(buf+charPointer+1) = '=' ;
    *(buf+charPointer+2) = '\0';

    arg2->exprPrint(buf,flag,ptr1,ptr2);

    break;
      
  default:
    abortExit("Illegal code for flag in SNlt::exprPrint");
  }

  return;
}

int SNle::howManyNotDefinedVariable(int flag , void *ptr1,void *ptr2) 
{
  int ret1,ret2;

  ret1 = (arg1->howManyNotDefinedVariable(flag,ptr1,ptr2));
  ret2 = (arg2->howManyNotDefinedVariable(flag,ptr1,ptr2));
  return(ret1+ret2);
}


int SNle::howManyNotDefinedFunction(int flag , void *ptr1,void *ptr2) 
{
  int ret1,ret2;

  ret1 = (arg1->howManyNotDefinedFunction(flag,ptr1,ptr2));
  ret2 = (arg2->howManyNotDefinedFunction(flag,ptr1,ptr2));
  return(ret1+ret2);
}

int SNle::howManyNotAssignedVariable(int flag , void *ptr1,void *ptr2) 
{
  int ret1,ret2;

  ret1 = (arg1->howManyNotAssignedVariable(flag,ptr1,ptr2));
  ret2 = (arg2->howManyNotAssignedVariable(flag,ptr1,ptr2));
  return(ret1+ret2);
}
