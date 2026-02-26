/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : BamgExec.cpp
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

#include <cstdio>
#include <cstdlib>
#include "Bamg.hpp"

void Bamg::execBamg( const char *geomFilename, const char *meshFilename)
{
  char combuf[BUFSIZ];

  sprintf(combuf,"bamg -g %s -o %s >/dev/null",geomFilename,meshFilename);
  system(combuf);
  return;
}
