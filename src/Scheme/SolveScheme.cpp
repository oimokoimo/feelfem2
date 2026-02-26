/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SolveScheme.cpp
 *  Date     : 1999/10/26
 *  Modified : 1999/11/18
 *  
 *  Purpose  : test function
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

#include <assert.h>
#include "SolveScheme.hpp"

SolveScheme::SolveScheme() {

  solveSchemes++;
  return;
}

SolveScheme::~SolveScheme() = default;

