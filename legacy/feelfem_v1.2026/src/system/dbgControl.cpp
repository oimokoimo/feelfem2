/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : dbgControl.cpp
 *  Date     : 2001/12/17
 *  Modified : 
 *  
 *  Purpose  : debugging control program
 *             dbgOpenpl();  2001/12/17
 *  
 */

#include "dbgFunctions.hpp"
#include "xplotfuncs.hpp"

void dbgOpenpl(void)
{
  openpl();
  return;
}

void dbgOpenpl(int a, int b)
{
  openpl(a,b);
  return;
}
