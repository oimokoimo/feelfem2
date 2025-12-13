/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNgeomPoint_InfoGenerate.cpp
 *  Date     : 2002/03/18
 *  Modified : 
 *  
 *  Purpose  :
 *  
 */

#include "SNgeomPoint.hpp"
#include "feelfuncs.hpp"

#include "PointObject.hpp"
#include "GeometryObject.hpp"

int SNgeomPoint::InfoGenerate()
{
  for(int i=0;i<identifierLst->GetNumberOfElements(); i++) {
    string nm = (*identifierLst)[i]->GetName();

    PointObject *pPtr = new PointObject(nm);

    feelfemgeomobj.AddGeomObj( pPtr );
  }
  return(0);
}
