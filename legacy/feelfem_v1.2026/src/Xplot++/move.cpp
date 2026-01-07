/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : move.cpp
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

void move(int x,int y)
{
  if(activeXplotPtr) {
    activeXplotPtr->moveToInteger(x,y);
  }

  if(activePsplotPtr) {
    activePsplotPtr->moveToInteger(x,y);
  }

  return;
}

void fmove(double x,double y)
{
  if(activeXplotPtr) {
    activeXplotPtr->moveToDouble(x,y);
  }

  if(activePsplotPtr) {
    activePsplotPtr->moveToDouble(x,y);
  }

  return;
}
