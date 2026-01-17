/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNgeomSurface_InfoGenerate.cpp
 *  Date     : 2002/03/18
 *  Modified : 
 *  
 *  Purpose  :
 *  
 */

#include "SNgeomSurface.hpp"
#include "feelfuncs.hpp"

#include "SurfaceObject.hpp"
#include "GeometryObject.hpp"

int SNgeomSurface::InfoGenerate()
{
  for(int i=0;i<identifierLst->GetNumberOfElements(); i++) {
    string nm = (*identifierLst)[i]->GetName();

    SurfaceObject *surfPtr = new SurfaceObject(nm);

    feelfemgeomobj.AddGeomObj( surfPtr );
  }
  return(0);
}
