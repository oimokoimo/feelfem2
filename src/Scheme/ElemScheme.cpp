/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : ElemScheme.cpp
 *  Date     : 1999/12/10
 *  Modified : 1999/12/10
 *  
 *  Purpose  : Assembly routine definition
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

#include <cassert>
#include <iostream>
#include "ElemScheme.hpp"

ElemScheme::ElemScheme() {

  elemSchemes++;
  return;
}

ElemScheme::~ElemScheme() = default;

