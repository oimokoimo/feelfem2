/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNgeomEdge_InfoGenerate.cpp
 *  Date     : 2002/03/18
 *  Modified : 
 *  
 *  Purpose  :
 *  
 */

#include "SNgeomEdge.hpp"
#include "feelfuncs.hpp"

#include "EdgeObject.hpp"
#include "GeometryObject.hpp"

int SNgeomEdge::InfoGenerate()
{
  for(int i=0;i<identifierLst->GetNumberOfElements(); i++) {
    string nm = (*identifierLst)[i]->GetName();

    EdgeObject *pPtr = new EdgeObject(nm);

    feelfemgeomobj.AddGeomObj( pPtr );
  }
  return(0);
}
