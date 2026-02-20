/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : symbol.cpp
 *  Date     : 2001/07/17
 *  Modified : 
 *  
 *  Purpose  : symbol,fsymbol
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

#include "xplot.hpp"
#include "psplot.hpp"
#include "xplotfuncs.hpp"

void symbol(int x,int y, const char *mesg)
{
  if(activeXplotPtr) {
    activeXplotPtr->symbolInteger(x,y,mesg);
  }

  if(activePsplotPtr) {
    activePsplotPtr->symbolInteger(x,y,mesg);
  }

  return;
}

void fsymbol(double x,double y,const char *mesg)
{
  if(activeXplotPtr) {
    activeXplotPtr->symbolDouble(x,y,mesg);
  }

  if(activePsplotPtr) {
    activePsplotPtr->symbolDouble(x,y,mesg);
  }

  return;
}
