/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : GeomObj.hpp
 *  Date     : 2002/03/18
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

#include <cassert>
#include <iostream>

#include "feeldef.hpp"

#include "GeomObj.hpp"

GeomObj::GeomObj(int n,const char *nm)
{
  geomType = n;          // geomObj is a container
  name     = nm;

  geomObjNo++;       // geomObjNo is statinc int GeomObj::geomObjNo;
  geomNo = geomObjNo;

  dFlag  = NO;
  nFlag  = NO;
  
  return;
}

GeomObj::~GeomObj() = default;

int GeomObj::IsNameIs( string &nm)
{
  if(name == nm) return(YES);

  return(NO);
}

int GeomObj::GetType( void )
{
  return(geomType);
}
   
void GeomObj::SetDirichletFlag()
{
  dFlag = YES;
  return;
}

void GeomObj::SetNeumannFlag()
{
  nFlag = YES;
  return;
}

int GeomObj::GetDirichletFlag()
{
  return(dFlag);
}

int GeomObj::GetNeumannFlag()
{
  return(nFlag);
}

int GeomObj::GetPropertyNo(void)
{
	std::cerr << "It must not be called." << std::endl;
  assert(1==0);
  return(0);
}

