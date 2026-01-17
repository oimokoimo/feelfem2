/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : makefile.cpp
 *  Date     : 2001/10/31
 *  Modified : 
 *  
 *  Purpose  : Generate makefile
 *  
 */

#include "Source.hpp"

void makefile(void)
{
  
  Source *makefileObj = new Source();

  makefileObj->makeMakefile(1);

  return;
}
