/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : BamgSubDomain.cpp
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

#include "Bamg.hpp"
#include "PolygonalRegion.hpp"
#include "Polygon.hpp"
#include "Point.hpp"

BamgSubDomain::BamgSubDomain(int bgEdgeRefNo, int dir, int mno)
{
  type            = 2;            // now fixed  it means line
  referenceEdgeNo = bgEdgeRefNo;
  direction       = dir;          // -1 or 1
  matno           = mno;

  return;
}

BamgSubDomain::~BamgSubDomain() = default;


