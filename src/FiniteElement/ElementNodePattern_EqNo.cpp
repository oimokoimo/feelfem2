/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : ElementNodePattern_EqNo.cpp
 *  Date     : 2002/02/01
 *  Modified : 
 *  
 *  Purpose  : make ienp, iedp arrays
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

#include "ElementNodePattern.hpp"

void ElementNodePattern::MakeElementEquationNo(void)
{
  assert(totalFreedom >0);
  assert(nodes > 0);
  nenfre = new int [nodes];
  ienp = new int[totalFreedom];
  iedp = new int[totalFreedom];

  assert(nodes > 0);
  int *nodeIedpWork;
  nodeIedpWork = new int[nodes];

  for(int i=0;i<totalFreedom;i++) {
    *(ienp+i) = 0;
    *(iedp+i) = 0;
  }
  
  for(int i=0;i<nodes;i++) {
    *(nenfre+i)       = 0;         // nenfre initialize
    *(nodeIedpWork+i) = 0;         // work initialize
  }
  

  //
  int currentDegreeOfFreedom;

  listIterator <Variable *>itr(unknownVarPtrLst);

  // Generate ienp, iedp information
  currentDegreeOfFreedom = 0;
  for(itr.init(); !itr ; ++itr) {
    int freedom;
    Element *ePtr;

    ePtr    = itr()->GetElementPtr();
    freedom = ePtr ->GetElementFreedom();

    ElementEquationNo *eenPtr 
      = new ElementEquationNo( itr()->GetName(), freedom);

    elemEqNoPtrLst.addlast(eenPtr);
    
    
    // calculate iedp and indp
    
    if(itr()->GetType() == VAR_EWISE_A ) {   // ewise freedom is at ewiseNodeNO
      
      for(int i=0;i<freedom;i++) {

	int ithIenp,ithIedp;

	ithIenp =   ewiseNodeNo;
	ithIedp = *(nodeIedpWork + (ithIenp-1)) ;

	// Variable IENP,IEDP
	eenPtr->SetIthIenpIedp( i, ithIenp, ithIedp);

	// Element IENP,IEDP
	*(ienp + currentDegreeOfFreedom + i) = ithIenp;
	*(iedp + currentDegreeOfFreedom + i) = ithIedp;

	// increment
	*(nodeIedpWork + (ithIenp -1)) += 1;
      }
    }

    else {  // element freedom

      for(int i=0;i<freedom;i++) {
	int ithIenp;
	int ithIedp;
	
	Node *nPtr;
	nPtr = ePtr->GetIthInterpolationNodePtr( i );
      
	ithIenp = nodeOrderedPtrLst.getPosition(nPtr);
	ithIedp = *(nodeIedpWork + (ithIenp-1)) ;

	assert(ithIenp > 0 && ithIenp <= nodes);

	// Variable IENP,IEDP
	eenPtr->SetIthIenpIedp( i, ithIenp, ithIedp);

	// Element IENP,IEDP
	*(ienp + currentDegreeOfFreedom + i) = ithIenp;
	*(iedp + currentDegreeOfFreedom + i) = ithIedp;

	// increment
	*(nodeIedpWork + (ithIenp -1)) += 1;
      }

    }
    currentDegreeOfFreedom+= freedom;
  }

  for(int i=0;i<nodes;i++) {         // strange implementation, but ...
    *(nenfre+i) = *(nodeIedpWork+i);
  }

  // delete work area
  delete [] nodeIedpWork;  // 020409

  return;
}
