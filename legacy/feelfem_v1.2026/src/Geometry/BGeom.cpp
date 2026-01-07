/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : BGeom.cpp
 *  Date     : 2002/03/24
 *  Modified : 
 *  
 *  Purpose  :
 *  
 */

#include <assert.h>

#include "feeldef.hpp"

#include "BGeom.hpp"
#include "GeomObj.hpp"

int BGeom::bgeoms = 0;

BGeom::BGeom(int type,GeomObj *ptr)
{
  condType = type;
  goPtr    = ptr;

  bgeoms++;
  bgeomNo  = bgeoms;

  if(condType == BGEOM_DIRICHLET ) {
    goPtr->SetDirichletFlag();
  }
  else{
    assert(condType == BGEOM_NEUMANN);
    goPtr->SetNeumannFlag();
  }

  return;
}

int BGeom::IsNameIs( string &name )
{
  return( goPtr->IsNameIs( name ));
}

int BGeom::IsBothCondition(void)
{
  if( goPtr->GetDirichletFlag() == YES &&
      goPtr->GetNeumannFlag()   == YES    ) {
    return(YES);
  }
  else {
    return(NO);
  }
}

