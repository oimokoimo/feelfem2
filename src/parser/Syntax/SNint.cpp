/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNint.cpp
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
 *
 */

#include "../../class/feelfuncs.hpp"
#include "SNint.hpp"

void SNint::exprPrint( char *buf, int flag , void *ptr1,void *ptr2) 
{

  int charPointer = stringLength( buf );
  int wrtLength;

  char intwrtbuf[BUFSIZ];
  sprintf(intwrtbuf,"%d%c",val,'\0');

  wrtLength = stringLength(intwrtbuf);


  if(wrtLength < 1) {
    abortExit("Illegal wrtLength in SNint");
  }

  if(charPointer + wrtLength + 1 > MAX_EXPRPRINT_BUF) {
    abortExit("Too long expression in SNint");
  }

  sprintf(buf+charPointer,"%s",intwrtbuf);
  *(buf+charPointer+wrtLength) = '\0';

  return;
}

