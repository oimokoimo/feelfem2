/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNgeomRegion_InfoGenerate.cpp
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

#include "SNgeomRegion.hpp"
#include "feelfuncs.hpp"

#include "RegionObject.hpp"
#include "GeometryObject.hpp"

int SNgeomRegion::InfoGenerate()
{
  for(int i=0;i<identifierLst->GetNumberOfElements(); i++) {
    string nm = (*identifierLst)[i]->GetName();

    RegionObject *pPtr = new RegionObject(nm);

    feelfemgeomobj.AddGeomObj( pPtr );
  }
  return(0);
}
