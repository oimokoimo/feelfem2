/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : peke.cpp
 *  Date     : 2001/12/19
 *  Modified : 
 *  
 *  Purpose  : draw peke mark
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

void peke(int x,int y)
{
  if(activeXplotPtr) {
    activeXplotPtr->pekeToInteger(x,y);
  }

  if(activePsplotPtr) {
    activePsplotPtr->pekeToInteger(x,y);
  }

  return;
}

void fpeke(double x,double y)
{
  if(activeXplotPtr) {
    activeXplotPtr->pekeToDouble(x,y);
  }

  if(activePsplotPtr) {
    activePsplotPtr->pekeToDouble(x,y);
  }

  return;
}
