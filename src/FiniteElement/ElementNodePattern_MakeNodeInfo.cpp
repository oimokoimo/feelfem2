/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : ElementNodePattern_MakeNodeInfo.cpp
 *  Date     : 2002/02/20
 *  Modified : 
 *  
 *  Purpose  : make ielem pattern for ecal argument
 *
 *
 *  feelfem2 (modernized/ported)
 *  Copyright (C) 2025-2026 Hidehiro Fujio and contributors
 *  SPDX-License-Identifier: BSD-3-Clause
 *  Repository: https://github.com/oimokoimo/feelfem2
 *
 *
 *  Notes:
 *  
 */
#include <cassert>
#include "feeldef.hpp"
#include "Element.hpp"
#include "Variable.hpp"
#include "ElementNodePattern.hpp"

int *ElementNodePattern::MakeNodeInfoForFEMvar( Variable *vPtr )
{
  if(vPtr->IsElementPtrReady() == NO) {
    assert(1==0);
  }
  
  Element *ePtr = vPtr->GetElementPtr();

  int *ret;

  ret = MakeNodeInfoForFEMvar( ePtr );

  return(ret);
}


int *ElementNodePattern::MakeNodeInfoForFEMvar( Element *ePtr )
{
  if(!elementPtrLst.includes(ePtr)) {
    assert(1==0);
  }

  int freedom;
  freedom = ePtr->GetElementFreedom();

  int *nodeInfoFEM = new int[freedom];

  for(int i=0;i<freedom;i++) {
    Node *ndPtr;

    ndPtr = ePtr->GetIthInterpolationNodePtr( i );

    int pos;

    pos = nodeOrderedPtrLst.getPosition( ndPtr );
    
    *(nodeInfoFEM + i) = pos;

  }

  return(nodeInfoFEM);
}

  

  
  
  
