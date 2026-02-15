/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNgeomMesher_CHECK.cpp
 *  Date     : 2002/03/18
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

#include "SNgeomMesher.hpp"
#include "Configure.hpp"
#include "feelfuncs.hpp"

#include "../../check/check_funcs.hpp"

int SNgeomMesher::Check()
{
  int ret,errors;
  errors = 0;
  
  ret =  feelfemconf.IsValidMesherName( mesherName );
  
  if(ret != YES) {
    SystemErrorStrA( (SNunit *)this, mesherName, " is not valid mesher name.");
    errors = 1;
  }

  return(errors);
}
