/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNprogramModel_CHECK.cpp
 *  Date     : 2001/10/26
 *  Modified : 
 *  
 *  Purpose  : check program model name
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

#include "feelfem.hpp"

#include "SNprogramModel.hpp"
#include "Procedure.hpp"
#include "Configure.hpp"
#include "feelfuncs.hpp"

int SNprogramModel::IsDefinedProgramModelName(void)
{
  int ret = feelfemconf.IsValidProgramModelName( modelName );

  return(ret);
}

void SNprogramModel::set_feelfemproc(void)
{
  int code = feelfemconf.GetProgramModelCodeFromName( modelName );
  feelfemproc.SetProgramModel( code );

  NOTE("ProgramModel set in feelfemproc at SNprogramModel::set_feelfemproc");

  return;
}
