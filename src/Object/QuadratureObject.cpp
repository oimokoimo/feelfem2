/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : QuadratureObject.cpp
 *  Date     : 1999/11/29
 *  Modified : 2000/12/27   abortExit
 *  
 *  Purpose  : Object record for Quadratures
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

#include "feelfuncs.hpp"
#include "Object.hpp"

int streq(const char*,const char *);

void Object::StoreQuadrature(Quadrature *qPtr)
{
  quadratures++;

  quadraturePtrLst.add(qPtr);
  return;
}

Quadrature * Object::GetQuadraturePtrByName(const char *name)
{
  listIterator <Quadrature *> itr(quadraturePtrLst);
  for(itr.init(); !itr ; ++itr) {
    if(itr()->isNameIs(name)) {
      Quadrature *ret = itr();
      return ret;
    }
  }
  std::cerr << "CANNOT FIND QUAD " << name << std::endl;
  assert(1==0);
  return(NULL);
}

int Object::IsDefinedQuadratureName( const char *name )
{
  listIterator <Quadrature *> itr(quadraturePtrLst);
  for(itr.init(); !itr ; ++itr) {
    if(itr()->isNameIs(name)) {
      return(YES);
    }
  }
  return(NO);
}
