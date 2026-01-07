/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : line.cpp
 *  Date     : 2001/12/19
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

void line(int x1,int y1,int x2,int y2)
{
  move(x1,y1);
  cont(x2,y2);

  return;
}

void fline(double x1,double y1,double x2,double y2)
{
  fmove(x1,y1);
  fcont(x2,y2);

  return;
}
