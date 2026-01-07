/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : geom_materialRegion_create.cpp
 *  Date     : 2002/09/02
 *  Modified : 
 *  
 *  Purpose  :
 *  
 */

#include "feeldef.hpp"

#include "GeometryObject.hpp"
#include "../parser/Syntax/SNunit.hpp"
#include "../parser/Syntax/SNgeomMaterialRegion.hpp"



int geom_materialRegion_create( list <SNunit *> &parseGeomLst)
{
  int errors;
  errors = 0;

  listIterator <SNunit *>itrGeom(parseGeomLst);

  // if not MaterialRegion
  for(itrGeom.init(); !itrGeom; ++itrGeom) {

    if(itrGeom()->GetType() != SN_GEOMMATERIALREGION) continue;

    // material region check
    
    errors += itrGeom()->InfoGenerate();

  }
  return(errors);
}
