/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : GiD.cpp
 *  Date     : 2002/03/24
 *  Modified : 
 *  
 *  Purpose  : GiD interface
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

#include "GiD.hpp"
#include "feelfuncs.hpp"
#include "GeometryObject.hpp"
#include "string.hpp"

GiD::GiD()
{
  problemTypeName = feelfemgeomobj.GetProblemName();
  dimension       = feelfemgeomobj.GetSpaceDimension();

  return;
}

GiD::~GiD() = default;
