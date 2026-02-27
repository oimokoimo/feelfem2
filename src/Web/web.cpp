/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : web.cpp
 *  Date     : 2002/08/23
 *  Modified : 
 *  
 *  Purpose  : post process for web
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

#include "Object.hpp"
#include "feelfuncs.hpp"
#include "feelfem.hpp"

void web_tar();

void web(void)
{

  if(feelfem_web == YES) {

    web_tar();

    printf("web:NORMAL\n");
  }

  return;
}
