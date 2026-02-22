/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : BoundaryIntegrandSet.cpp
 *  Date     : 2002/03/27
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

#include "IntegrandSet.hpp"

#include "IntegrandSet.hpp"
#include "Quadrature.hpp"
#include "list.hpp"
#include "string.hpp"

#include "TermConvert.hpp"

BoundaryIntegrandSet::BoundaryIntegrandSet()
{
  useNX = 0;
  useNY = 0;
  useNZ = 0;

  return;
}

BoundaryIntegrandSet::~BoundaryIntegrandSet()
{
  return;   // do nothing now
}

void BoundaryIntegrandSet::SetUseNX(void)
{
  useNX = 1;
  return;
}

void BoundaryIntegrandSet::SetUseNY(void)
{
  useNY = 1;
  return;
}

void BoundaryIntegrandSet::SetUseNZ(void)
{
  useNZ = 1;
  return;
}

int BoundaryIntegrandSet::GetUseNX(void)
{
  return useNX;
}

int BoundaryIntegrandSet::GetUseNY(void)
{
  return useNY;
}

int BoundaryIntegrandSet::GetUseNZ(void)
{
  return useNZ;
}

BoundaryIntegrandSet *BoundaryIntegrandSet::GetNewByTC(TermConvert &tc)
{
  BoundaryIntegrandSet *newPtr = new BoundaryIntegrandSet;

  newPtr->useX = useX;
  newPtr->useY = useY;
  newPtr->useZ = useZ;

  newPtr->useNX = useNX;
  newPtr->useNY = useNY;
  newPtr->useNZ = useNZ;

  newPtr->equations = equations;
  newPtr->quadPtr   = quadPtr;
  
  newPtr->varPtrLst       = varPtrLst;
  newPtr->functionNameLst = functionNameLst;

  listIterator <string>itrS(integrandLst);
  for(itrS.init(); !itrS ; ++itrS ) {
    string ret;

    ret = tc.convertExpressionString( (const char *) itrS() );
    (newPtr->integrandLst).addlast( ret );
  }

  return(newPtr);
}
