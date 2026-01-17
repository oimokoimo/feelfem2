/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : BoundaryElementNodePattern_EqNo.cpp
 *  Date     : 2002/04/09  (copy of ElementNodePattern_EqNo.cpp)
 *  Modified : 
 *  
 *  Purpose  : make ienp, iedp arrays
 *  
 */

#include <assert.h>

#include "feeldef.hpp"

#include "BoundaryElementNodePattern.hpp"

void BoundaryElementNodePattern::MakeElementEquationNo(void)
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
    Element *bePtr;                   // boundary

    ePtr    = itr()->GetElementPtr();
    bePtr   = ePtr->AcquireBoundaryElementPtr();   // boundary

    freedom = bePtr ->GetElementFreedom();         // boundary

    // in fact, BoundaryElementEquationNo == ElementEquatonNo
    BoundaryElementEquationNo *eenPtr 
      = new BoundaryElementEquationNo( itr()->GetName(), freedom);

    elemEqNoPtrLst.addlast(eenPtr);
    
    
    // calculate iedp and indp
    
    if(itr()->GetType() == VAR_EWISE_A ) {   // ewise freedom is at ewiseNodeNO
      

      assert(1==0);  // currently, no ewise variable with neumann condtion
      // boundary edat data must have corresponding region element number.
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


      // boundary
      for(int i=0;i<freedom;i++) {
	int ithIenp;
	int ithIedp;
	
	int bno;

	bno = bePtr->GetIthOriginalIplus1(i);

	Node *nPtr;      // Ith  -> bno-1
	nPtr = bePtr->GetIthInterpolationBoundaryNodePtr( bno-1 ); // boundary

	// check write
	//	cerr << "for freedom No. " << i + 1 << endl;
	//	cerr << "    bno        =" << bno << endl;
	//	cerr << "Node            ";
	//	nPtr->print(cerr) ;  cerr << endl;
	
      
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



  //  cerr << "debug check" << endl;
  //  cerr << "ienp : ";
  //  for(int i=0;i<totalFreedom;i++) {
  //    cerr << *(ienp+i) << " ";
  //  }
  //  cerr << endl;

  //  cerr << "iedp : ";
  //  for(int i=0;i<totalFreedom;i++) {
  //    cerr << *(iedp+i) << " ";
  //  }
  //  cerr << endl;

  return;
}
