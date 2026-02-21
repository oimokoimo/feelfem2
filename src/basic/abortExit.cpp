/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999,2000
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : 
 *  Date     : 2000/12/26
 *  
 *  Purpose  : exit function
 *  
 */
#include <stdio.h>
#include <stdlib.h>

void abortExit(int iout)
{
  exit(iout);
}

void abortExit(const char *mesg)
{
  fprintf(stderr,"abortExit feelfem : %s\n",mesg);
  exit(1);
}
