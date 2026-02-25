/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999,2000
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : doNothingNow.cpp
 *  Date     : 2000/11/09
 *  Modified : 2000/11/09
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
#include <cstdio>
#include "feelfuncs.hpp"

static FILE *fpDoNothingNow;
static int comeYetdoNothingNow = 0;

void doNothingNow( const char *mesg )
{
  if(comeYetdoNothingNow == 0) {
    fpDoNothingNow = fopen("donothingnow.feelfem","w");
    if(fpDoNothingNow == NULL) {
      fprintf(stderr,"Cannot open donothingnow.feelfem to write\n");
      abortExit(1);
    }
    comeYetdoNothingNow = 1;
  }

  fprintf(fpDoNothingNow, "%s\n",mesg);

  return;
}
