/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNsolveNeumann_InfoGenerate.cpp
 *  Date     : 2002/02/05
 *  Modified : 
 *  
 *  Purpose  :
 *  
 */

#include <assert.h>

#include "SNsolveNeumann.hpp"

#include "feelfuncs.hpp"
#include "Object.hpp"
#include "Variable.hpp"
#include "Neumann.hpp"

#include "GeometryObject.hpp"
#include "BGeom.hpp"
#include "NeumannGeom.hpp"

void SNsolveNeumann::AddVariablePtr_Neumann(Neumann *nPtr)
{
  neumannPtr = nPtr;

  listIterator <Expression *>itr(nPairsPtr->neumannExpressionLst);
  for(itr.init(); !itr ; ++itr) {
    itr()->AddVariablePtr_Neumann(nPtr);
  }
  return;
}

int SNsolveNeumann::GeometryCreate()
{
  int errors = 0;

  for(int i=0;i<nBoundaryLst->GetNumberOfElements();i++) {
    string nm = (*nBoundaryLst)[i]->GetName();

    GeomObj *goPtr     = feelfemgeomobj.GetGeomObjByName(nm);
    NeumannGeom *ngPtr = feelfemgeomobj.AcquireNeumannGeomByName(goPtr);

    assert(neumannPtr != 0);

    // NeumannGeom data in Neumann,
    neumannPtr->AddNeumannGeomPtr( ngPtr );

    // Neumann data in NeumannGeom,
    ngPtr->StoreNeumannData( neumannPtr );

  }
  return(errors);
}

void SNsolveNeumann::AddNeumannDataPairs( Neumann *nPtr)
{
  nPairsPtr->AddNeumannDataPairs( nPtr );
  return;
}

