/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SystemErrorFilename.cpp
 *  Date     : 2001/03/13
 *  Modified : 
 *  
 *  Purpose  : Store the filename
 *  
 */

#include <stream.h>
#include "string.hpp"
#include "list.hpp"

static list <string> sourceFileList;
static int sourceNo = 0;

void storeSourceFileName( char *filename)
{
  sourceFileList.addlast( filename );
  sourceNo++;
  return;
}

int currentSourceFileNo(void) 
{
  return(sourceNo);
}

void wrtErrSourceFilename(ostream &ost, int no)
{
  ost << sourceFileList.getNthElement(no);
  return;
}
