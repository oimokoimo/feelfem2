/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNsolve_InfoGenerate_BGeom.cpp
 *  Date     : 2002/03/25
 *  Modified : 
 *  
 *  Purpose  : Boundary geometry data creation
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

#include "SNsolve.hpp"
#include "SNsolveDirichlet.hpp"
#include "SNsolveNeumann.hpp"

int SNsolve::BoundaryGeometryCreate(void)
{
  int errors=0;

  listIterator <SNsolveDirichlet *>itrD(dcondLst);
  for(itrD.init();!itrD;++itrD) {
    errors += itrD()->GeometryCreate();
  }

  listIterator <SNsolveNeumann *>itrN(ncondLst);
  for(itrN.init();!itrN;++itrN) {
    errors += itrN()->GeometryCreate();
  }
  return(errors);
}

