/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : fileOpen.cpp
 *  Date     : 2002/08/23
 *  Modified : 
 *  
 *  Purpose  :
 *  
 */

#include <stdio.h>
#include "Object.hpp"
#include "feelfuncs.hpp"

FILE *fileOpenToWrite(const char *fname)
{
  FILE *fp;

  fp = fopen(fname,"w");

  feelfemobj.StoreFileObject( fname );

  return(fp);
}

