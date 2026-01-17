/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNif_InfoGenerate.cpp
 *  Date     : 2002/07/18
 *  Modified : 
 *  
 *  Purpose  :
 *  
 */

#include <iostream.h>

#include "SNif.hpp"

#include "IfBlock.hpp"

int SNif::InfoGenerate(void)
{

  ifblockPtr = new IfBlock(gotoLabel);
  
  exprPtr->MakeVariablePtr(ifblockPtr->varPtrLst);
  
  char exprbuf[MAX_EXPRPRINT_BUF];
  exprbuf[0] = '\0';
  exprPtr->exprPrint(exprbuf,EXPRPRINT_NORMAL,0,0);
  ifblockPtr->expr = exprbuf;

  return(0);
}
