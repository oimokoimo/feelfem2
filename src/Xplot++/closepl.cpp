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
#include "xplotfuncs.hpp"
#include "xplot.hpp"
#include "psplot.hpp"

void closepl(void)
{
  if(activeXplotPtr) {
    activeXplotPtr->closeWindow();
  }

  if(activePsplotPtr) {
    activePsplotPtr->closeFile();
  }

  return;
}
