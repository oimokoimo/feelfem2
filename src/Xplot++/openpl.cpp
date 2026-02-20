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
 *
 *  feelfem2 (modernized/ported)
 *  Copyright (C) 2025-2026 Hidehiro Fujio and contributors
 *  SPDX-License-Identifier: BSD-3-Clause
 *  Repository: https://github.com/oimokoimo/feelfem2
 *
 *
 *  Notes:
 *  
 */

#include <iostream>
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
