/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : openpl.cpp
 *  Date     : 2001/04/10
 *  Modified : 
 *  
 *  Purpose  :
 *  
 */

#include <stdio.h>
#include <stdlib.h>
#include "xplot.hpp"
#include "psplot.hpp"
#include "xplotfuncs.hpp"


#include <stdio.h>
#include <X11/Xlib.h>

void openpl(void)
{
  xplot      *xp = new xplot(getenv("DISPLAY"));
  activeXplotPtr = xp;

  return;
}

void openpl(int xlen, int ylen)
{
  xplot      *xp = new xplot(getenv("DISPLAY"),xlen,ylen);
  activeXplotPtr = xp;

  return;
}

void openplps(const char *filename)
{
  psplot     *pp  = new psplot(filename);
  activePsplotPtr = pp;

  return;
}
