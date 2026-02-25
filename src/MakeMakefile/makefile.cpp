/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : makefile.cpp
 *  Date     : 2001/10/31
 *  Modified : 
 *  
 *  Purpose  : Generate makefile
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

#include "Source.hpp"

void makefile(void)
{
  
  Source *makefileObj = new Source();

  makefileObj->makeMakefile(1);

  return;
}
