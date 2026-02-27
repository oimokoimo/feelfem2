/*
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
 *
 *
 */
#include <cstdio>

#define DBG

void dbgGeneratorReport(const char *module,const char *mesg )
{
  static int flag = 0;
  FILE      *fpDBG;
#ifdef DBG
  if(flag = 1 && fpDBG == NULL) return;
  if(flag == 0) {
    fpDBG = fopen("DbgReportFeelfem.txt","w");
    if(fpDBG == NULL ) {
      flag = 1;
      fprintf(stderr,"Cannot open DBGReportFeelfem.txt\n");
      return;
    }
  }

  fprintf(fpDBG,"[%s] : %s\n",module,mesg);
#endif

  return;
}

