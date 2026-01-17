/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : xwait.cpp
 *  Date     : 2001/04/10
 *  Modified : 
 *  
 *  Purpose  :
 *  
 */

#include <assert.h>
#include "xplotfuncs.hpp"
#include "xplot.hpp"

void xwait(void)
{
  if(activeXplotPtr) {
    activeXplotPtr->waitEvent();
  }

  if(activePsplotPtr) {
    ;
  }
  return;
}
