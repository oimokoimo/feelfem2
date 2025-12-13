/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : 
 *  Date     : 2001/04/10
 *  Modified : 
 *  
 *  Purpose  :
 *  
 */

#include <assert.h>
#include <iostream.h>
#include "xplot.hpp"
#include "psplot.hpp"
#include "xplotfuncs.hpp"

void cont(int x,int y)
{
  if(activeXplotPtr) {
    activeXplotPtr->contToInteger(x,y);
  }

  if(activePsplotPtr) {
    activePsplotPtr->contToInteger(x,y);
  }

  return;
}

void fcont(double x,double y)
{
  if(activeXplotPtr) {
    activeXplotPtr->contToDouble(x,y);
  }

  if(activePsplotPtr) {
    activePsplotPtr->contToDouble(x,y);
  }

  return;
}
