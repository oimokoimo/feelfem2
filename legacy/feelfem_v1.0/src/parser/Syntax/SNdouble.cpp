/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNdouble.cpp
 *  Date     : 2001/03/12
 *  Modified : 
 *  
 *  Purpose  :
 *  
 */

#include <stdio.h>                               // for sprintf
#include "../../class/feelfuncs.hpp"
#include "SNdouble.hpp"

void SNdouble::exprPrint( char *buf, int flag , void *ptr1,void *ptr2) 
{

  int charPointer = stringLength( buf );
  int wrtLength;

  char dblwrtbuf[BUFSIZ];

  if(flag == EXPRPRINT_SIMPLE) {                // for GID cnd file
    sprintf(dblwrtbuf,"%lf%c",val,'\0');
  }
  else {
    sprintf(dblwrtbuf,"%18.15lf%c",val,'\0');    
  }


  wrtLength = stringLength(dblwrtbuf);


  if(wrtLength < 1) {
    abortExit("Illegal wrtLength in SNdouble");
  }

  if(charPointer + wrtLength + 1 > MAX_EXPRPRINT_BUF) {
    abortExit("Too long expression in SNdouble");
  }

  sprintf(buf+charPointer,"%s",dblwrtbuf);
  *(buf+charPointer+wrtLength) = '\0';

  return;
}

