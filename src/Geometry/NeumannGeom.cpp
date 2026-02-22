/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : NeumannGeom.cpp
 *  Date     : 2002/03/24
 *  Modified : 
 *  
 *  Purpose  : Neumann data geometry
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

#include "feeldef.hpp"
#include "NeumannGeom.hpp"
#include "BGeom.hpp"

int NeumannGeom::ncondGeoms = 0;

NeumannGeom::NeumannGeom(GeomObj *gobjPtr) : BGeom(BGEOM_NEUMANN,gobjPtr)
{
  ncondGeoms++;
  no = ncondGeoms;

  return;
}

NeumannGeom::~NeumannGeom() = default;

void NeumannGeom::StoreNeumannData(Neumann *nPtr)
{
  nDataPtrLst.addlast(nPtr);
  return;
}
