/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNgeomMaterialRegion_InfoGenerate.cpp
 *  Date     : 2002/08/30
 *  Modified : 
 *  
 *  Purpose  :
 *  
 */

#include <assert.h>

#include "feelfuncs.hpp"
#include "SNgeomMaterialRegion.hpp"

#include "GeometryObject.hpp"
#include "RegionObject.hpp"

#include "Object.hpp"
#include "Configure.hpp"

int SNgeomMaterialRegion::InfoGenerate(void)
{
  int errors = 0;

  list <string> regionStrLst;
  identifierLst->StoreContentsInStringLst(regionStrLst);

  listIterator<string> itr(regionStrLst);

  for(itr.init(); !itr ; ++itr) {
    string nm = itr();

    RegionObject *roPtr = feelfemgeomobj.GetRegionObjectPtrByName( nm );

    // duplication error will be checked at SNmaterialVar_CHECK.cpp
    roPtr->AddMaterialAttribute( name );
  }

  return(0);
}


  
