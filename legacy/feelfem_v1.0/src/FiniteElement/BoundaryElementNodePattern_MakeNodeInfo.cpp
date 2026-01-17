/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : BoundaryElementNodePattern_MakeNodeInfo.cpp
 *  Date     : 2002/02/20
 *  Modified : 
 *  
 *  Purpose  : make ielem pattern for ecal argument
 *  
 */
#include <assert.h>
#include "feeldef.hpp"
#include "Element.hpp"
#include "Variable.hpp"
#include "BoundaryElementNodePattern.hpp"

int *BoundaryElementNodePattern::MakeNodeInfoForFEMvar( Variable *vPtr )
{
  if(vPtr->IsElementPtrReady() == NO) {
    assert(1==0);
  }
  
  Element *ePtr  = vPtr->GetElementPtr();
  Element *bePtr = ePtr->AcquireBoundaryElementPtr();  // boundary

  int *ret;

  ret = MakeNodeInfoForFEMvar( bePtr );

  return(ret);
}


int *BoundaryElementNodePattern::MakeNodeInfoForFEMvar( Element *bePtr )
{
  Element *ePtr;
  ePtr = bePtr->GetParentElementPtr();
  if(!elementPtrLst.includes(ePtr)) {
    assert(1==0);
  }

  if(bePtr->IsBoundaryElement() != YES) {
    cerr << "Non boudnary element pointer in BENP::MakeNodeInfoForFEMvar\n";
    assert(1==0);
  }
  

  int freedom;
  freedom = bePtr->GetElementFreedom();

  int *nodeInfoFEM = new int[freedom];    // allocate here, deallocated 

  for(int i=0;i<freedom;i++) {
    Node *ndPtr;
    ndPtr = bePtr->GetIthBoundaryInterpolationNodePtr( i );

    int pos;

    pos = nodeOrderedPtrLst.getPosition( ndPtr );
    
    *(nodeInfoFEM + i) = pos;

  }
  return(nodeInfoFEM);
}

  

  
  
  
