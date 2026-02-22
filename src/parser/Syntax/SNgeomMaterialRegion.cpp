/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNgeomMaterialRegion.cpp
 *  Date     : 2002/08/30
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

#include "SNgeomMaterialRegion.hpp"

SNgeomMaterialRegion::SNgeomMaterialRegion(const char *nm,SNidentifierlist *ptr) 
    : SNunit("geomMaterialRegion",SN_GEOMMATERIALREGION)
{
  name = nm;
  identifierLst = ptr;
  return;
}

