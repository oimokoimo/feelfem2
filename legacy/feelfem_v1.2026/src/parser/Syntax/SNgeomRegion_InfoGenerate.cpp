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
