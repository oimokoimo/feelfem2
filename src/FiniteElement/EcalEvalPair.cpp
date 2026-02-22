/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : EcalEvalPair.cpp
 *  Date     : 2002/03/05
 *  Modified : 2002/04/10   type->diffType
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

#include "list.hpp"
#include "EcalInfo.hpp"

EcalEvalPair::EcalEvalPair( Element *ptr, int t)
{
  elemPtr = ptr;
  diffType    = t;

  return;
}

EcalEvalPair::~EcalEvalPair() = default;

int operator ==(const EcalEvalPair &left,const EcalEvalPair &right)
{
  return( left.diffType == right.diffType && left.elemPtr == right.elemPtr );
}
