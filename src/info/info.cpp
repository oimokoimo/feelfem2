/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : info.cpp
 *  Date     : 2001/09/04
 *  Modified : 
 *  
 *  Purpose  : Information class generation
 *
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
#include "feelfem.hpp"              // for command options

#include "list.hpp"
#include "parseExternals.hpp"       // for parser  trees
#include "feelfuncs.hpp"


int scheme_info_generate(list <void *>&);

void info(void)
{
  NOTE("Welcome to info");

  // Info Generate for scheme block

  int ret_scheme_info_generate = scheme_info_generate(parseSchemeLst);
  if(ret_scheme_info_generate) {
    abortExit("due to scheme info generate.");
  }  

  return;
}
