/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNgeomMaterialRegion_CHECK.cpp
 *  Date     : 2002/08/30
 *  Modified : 
 *  
 *  Purpose  :
 *  
 */

#include <assert.h>

#include "SNgeomMaterialRegion.hpp"
#include "GeometryObject.hpp"
#include "feelfuncs.hpp"

#include "../../check/check_funcs.hpp"

int SNgeomMaterialRegion::Check()
{
  // This routine is called after region geometry objects have been created.
  int errors = 0;

  list <string> regionStrLst;
  identifierLst->StoreContentsInStringLst(regionStrLst);

  listIterator<string> itr(regionStrLst);

  for(itr.init(); !itr ; ++itr) {
    string nm = itr();
    if(feelfemgeomobj.IsRegionObjectName( nm )) continue;

    SystemErrorStrA(this,nm," is not a region name.");
    errors++;
  }

  return(errors);
}
