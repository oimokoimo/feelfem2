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

#include <cassert>
#include <iostream>
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
