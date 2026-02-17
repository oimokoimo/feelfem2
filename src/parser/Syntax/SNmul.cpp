/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNmul.cpp
 *  Date     : 2001/03/12
 *  Modified : 
 *  
 *  Purpose  :
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

#include "../../class/feelfuncs.hpp"
#include "SNmul.hpp"

void SNmul::exprPrint( char *buf, int flag , void *ptr1,void *ptr2) 
{
  int charPointer;

  arg1->exprPrint(buf,flag,ptr1,ptr2);

  charPointer = CstringLength(buf);

  if(charPointer + 1 + 1 > MAX_EXPRPRINT_BUF) {
    abortExit("Too long expression in SNmul");
  }
  *(buf+charPointer  ) = '*' ;
  *(buf+charPointer+1) = '\0';

  arg2->exprPrint(buf,flag,ptr1,ptr2);

  return;
}

int SNmul::howManyNotDefinedVariable(int flag , void *ptr1,void *ptr2) 
{
  int ret,ret1,ret2;
  ret1 = arg1->howManyNotDefinedVariable(flag,ptr1,ptr2);
  ret2 = arg2->howManyNotDefinedVariable(flag,ptr1,ptr2);

  ret = ret1 + ret2;

  return(ret);
}

int SNmul::howManyNotDefinedFunction(int flag , void *ptr1,void *ptr2) 
{
  int ret,ret1,ret2;
  ret1 = arg1->howManyNotDefinedFunction(flag,ptr1,ptr2);
  ret2 = arg2->howManyNotDefinedFunction(flag,ptr1,ptr2);

  ret = ret1 + ret2;

  return(ret);
}

int SNmul::howManyNotAssignedVariable(int flag , void *ptr1,void *ptr2) 
{
  int ret,ret1,ret2;
  ret1 = arg1->howManyNotAssignedVariable(flag,ptr1,ptr2);
  ret2 = arg2->howManyNotAssignedVariable(flag,ptr1,ptr2);

  ret = ret1 + ret2;

  return(ret);
}
