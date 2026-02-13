/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNbracket.cpp
 *  Date     : 2001/03/13
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
 */

#include <stdio.h>                               // for sprintf
#include "../../class/feelfuncs.hpp"
#include "SNbracket.hpp"

void SNbracket::exprPrint( char *buf, int flag , void *ptr1,void *ptr2) 
{

  int charPointer;
  
  charPointer = CstringLength(buf);
  if(charPointer + 1 + 1 > MAX_EXPRPRINT_BUF) {
    abortExit("Too long expression in SNbracket");
  }
  *(buf+charPointer  ) = '(' ;
  *(buf+charPointer+1) = '\0';

  expr->exprPrint(buf,flag,ptr1,ptr2);


  charPointer = CstringLength(buf);
  if(charPointer + 1 + 1 > MAX_EXPRPRINT_BUF) {
    abortExit("Too long expression in SNbracket");
  }
  *(buf+charPointer  ) = ')' ;
  *(buf+charPointer+1) = '\0';

  return;
}

int SNbracket::howManyNotDefinedVariable( int flag,void *ptr1,void *ptr2)
{
  int ret;

  ret = expr->howManyNotDefinedVariable(flag,ptr1,ptr2);
  return ( ret ) ;
}

int SNbracket::howManyNotDefinedFunction ( int flag,void *ptr1,void *ptr2)
{
  int ret;

  ret = expr->howManyNotDefinedFunction(flag,ptr1,ptr2);
  return ( ret ) ;
}

int SNbracket::howManyNotAssignedVariable( int flag,void *ptr1,void *ptr2)
{
  int ret;

  ret = expr->howManyNotAssignedVariable(flag,ptr1,ptr2);
  return ( ret ) ;
}
