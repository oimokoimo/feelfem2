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

#include <iostream>

#include "xplotfuncs.hpp"
#include "xplot.hpp"
#include "psplot.hpp"

void space(int x1,int y1,int x2,int y2)
{
  int dx = x2 - x1;
  int dy = y2 - y1;

  if(dx <= 0 || dy <= 0) {               /* parameter error */
	  std::cerr << "space range error" << std::endl;
    return;
  }

  if(activeXplotPtr) {
    activeXplotPtr->spaceInteger(x1,y1,x2,y2);
  }

  if(activePsplotPtr) {
    activePsplotPtr->spaceInteger(x1,y1,x2,y2);
  }

  return;
}

void fspace(double x1,double y1,double x2,double y2)
{
  double dx = x2 - x1;
  double dy = y2 - y1;

  if(dx <= 0.0 || dy <= 0.0) {               /* parameter error */
	  std::cerr << "fspace range error" << std::endl;
    return;
  }

  if(activeXplotPtr) {
    activeXplotPtr->spaceDouble(x1,y1,x2,y2);
  }

  if(activePsplotPtr) {
    activePsplotPtr->spaceDouble(x1,y1,x2,y2);
  }
  return;
}

