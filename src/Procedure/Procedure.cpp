/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : Procedure.cpp
 *  Date     : 2001/04/23
 *  Modified : 
 *  
 *  Purpose  : Program model... (still pending for purpose)  2002.1.10
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

#include "Procedure.hpp"
#include "feeldef.hpp"

Procedure feelfemproc;             

Procedure::Procedure()
{
  // do nothing now
  
  programModel = PROC_DEFAULT_PROGRAM_MODEL;

  return;
}


Procedure::~Procedure() = default;
