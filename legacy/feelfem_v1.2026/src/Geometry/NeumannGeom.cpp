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

NeumannGeom::~NeumannGeom()
{
  // do nothing
  return;
}

void NeumannGeom::StoreNeumannData(Neumann *nPtr)
{
  nDataPtrLst.addlast(nPtr);
  return;
}
