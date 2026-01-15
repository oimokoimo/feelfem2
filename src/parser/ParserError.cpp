/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : ParserErrror.cpp
 *  Date     : 1999/07/22
 *  Modified : 1999/07/22
 *  
 *  Purpose  : Error handle routine while parsing
 *  
 */

#include <stdlib.h>
#include <iostream.h>


int numberOfErrors = 0;

void parseWarning( char *msg, int lineno )
{
  cerr << currentFileName << ":" << (lineno?dec(lineno) : "?")<<":";
  cerr << msg << "\n";

  return;
}


void parseError(char * msg, int lineno = 0)
{
  parseWarning( msg, lineno);
  
  numberOfErrors++;
  
  if(numberOfErrors > MaxNumberOfError) {
    cerr << currentFileName << ":" << (lineno ? dec(lineno) : "?" ) << ":";
    cerr << "too many errors.\n";
    exit(1);
  }
}

