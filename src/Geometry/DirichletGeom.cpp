/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : DirichletGeom.cpp
 *  Date     : 2002/03/21
 *  Modified : 
 *  
 *  Purpose  : Geometry for Dirichlet
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
#include "DirichletGeom.hpp"
#include "BGeom.hpp"

int DirichletGeom::dcondGeoms = 0;

DirichletGeom::DirichletGeom(GeomObj *gobjPtr) : BGeom(BGEOM_DIRICHLET,gobjPtr)
{
  dcondGeoms++;
  no = dcondGeoms;

  return;
}

DirichletGeom::~DirichletGeom()
{
  // do nothing
  return;
}

void DirichletGeom::StoreDirichletData(Dirichlet *dPtr)
{
  dDataPtrLst.addlast(dPtr);
  return;
}
