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
