/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : BamgExec.cpp
 *  Date     : 2001/04/10
 *  Modified : 
 *  
 *  Purpose  :
 *  
 */

#include <stdio.h>
#include <stdlib.h>
#include "Bamg.hpp"

void Bamg::execBamg( const char *geomFilename, const char *meshFilename)
{
  char combuf[BUFSIZ];

  sprintf(combuf,"bamg -g %s -o %s >/dev/null",geomFilename,meshFilename);
  system(combuf);
  return;
}
