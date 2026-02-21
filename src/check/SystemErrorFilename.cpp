/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SystemErrorFilename.cpp
 *  Date     : 2001/03/13
 *  Modified : 
 *  
 *  Purpose  : Store the filename
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
#include "string.hpp"
#include "list.hpp"

static list <string> sourceFileList;
static int sourceNo = 0;

void storeSourceFileName( char *filename)
{
  sourceFileList.addlast( filename );
  sourceNo++;
  return;
}

int currentSourceFileNo(void) 
{
  return(sourceNo);
}

void wrtErrSourceFilename(std::ostream &ost, int no)
{
  ost << sourceFileList.getNthElement(no);
  return;
}
