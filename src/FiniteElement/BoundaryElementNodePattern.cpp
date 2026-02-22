/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : BoundaryElementNodePattern.hpp
 *  Date     : 2002/04/09 (copy of ElementNodePattern.hpp)
 *  Modified : 
 *  
 *  Purpose  : 
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

#include <iostream>
#include <cassert>

#include "BoundaryElementNodePattern.hpp"

#include "feelfuncs.hpp"
#include "Object.hpp"

BoundaryElementNodePattern::BoundaryElementNodePattern(void)
{
  etype          = 0;
  unknowns       = 0;

  numberOfFEMVariables = 0;
  numberOfVFEMVariables = 0;
  numberOfEWISEVariables = 0;
  
  nodes          = 0;
  totalFreedom   = 0;
  ewiseFreedom = 0;

  ewiseNodePtr   = 0;   // pointer initialize

  ewiseNodeNo    = 0;   // associated node number for EWISE freedom

  ienp   = 0;  // pointer initialize
  iedp   = 0;  // pointer initialize
  nenfre = 0;  // pointer initialize

  return;
}

BoundaryElementNodePattern::~BoundaryElementNodePattern(void) = default;



void BoundaryElementNodePattern::AddUnknownVariable(Variable *varPtr)
{
  unknowns++;
  unknownVarPtrLst.addlast(varPtr);

  int type;
  type = varPtr->GetType();

  Element *ePtr;
  Element *bePtr;  // bePtr for boundary element

  switch(type) {
  case VAR_FEM:
    ePtr  = varPtr->GetElementPtr();
    bePtr = ePtr->AcquireBoundaryElementPtr();   // boundary

    numberOfFEMVariables++;

    totalFreedom += bePtr->GetElementFreedom();  // boundary
    SetEtype(ePtr->GetEtype());

    if(!elementPtrLst.includes(ePtr)) {
      elementPtrLst.add(ePtr);
    }

    break;

  case VAR_VFEM:
    ePtr = varPtr->GetElementPtr();
    bePtr = ePtr->AcquireBoundaryElementPtr();      // boundary

    numberOfVFEMVariables++;

    totalFreedom += bePtr->GetElementFreedom();     // boundary
    SetEtype(ePtr->GetEtype());

    if(!elementPtrLst.includes(ePtr)) {
      elementPtrLst.add(ePtr);
    }

    std::cerr << "not supported now...\n";
    break;

  case VAR_EWISE_A:
    assert(varPtr->GetEwiseType() == EWISE_TYPE_INTERPOLATION);
    ePtr = varPtr->GetElementPtr();
    bePtr = ePtr->AcquireBoundaryElementPtr();     // boundary

    numberOfEWISEVariables++;

    totalFreedom   += bePtr->GetElementFreedom();  // boundary
    ewiseFreedom += ePtr->GetElementFreedom();
    SetEtype(ePtr->GetEtype());

    // Note.  Not used for degree of freedom, but node coordinate must
    // be generate.
    if(!elementPtrLst.includes(ePtr)) {
      elementPtrLst.add(ePtr);
    }

    break;

  default:
    assert(1==0);
  }
  return;
}

void BoundaryElementNodePattern::AddNodeByVariable( Variable *varPtr )
{
  int type;
  type = varPtr->GetType();

  Element *ePtr;

  switch(type) {
  case VAR_FEM:
    ePtr = varPtr->GetElementPtr();
    if(!elementPtrLst.includes(ePtr)) {
      elementPtrLst.add(ePtr);
    }

    break;

  case VAR_VFEM:
    ePtr = varPtr->GetElementPtr();
    if(!elementPtrLst.includes(ePtr)) {
      elementPtrLst.add(ePtr);
    }

    std::cerr << "not supported now...\n";
    break;

  case VAR_EWISE_A:
    if(varPtr->GetEwiseType() != EWISE_TYPE_INTERPOLATION) {
      break;
    }
    ePtr = varPtr->GetElementPtr();
    if(!elementPtrLst.includes(ePtr)) {
      elementPtrLst.add(ePtr);
    }
    break;

  default:
    break;     // known variables are scalar, etc.
  }
  return;
}


void BoundaryElementNodePattern::AddNodeByElement( Element *ePtr )
{
  if(!elementPtrLst.includes(ePtr)) {
    elementPtrLst.add(ePtr);
  }
  return;
}

void BoundaryElementNodePattern::SetEtype(int e)
{
  if(etype == 0) {
    etype  = e;

    // boundary element type
    switch(etype) {
    case ELEMENT_TYPE_TRI:
      betype = ELEMENT_TYPE_LINE;
      break;

    case ELEMENT_TYPE_RECT:
      betype = ELEMENT_TYPE_LINE;
      break;

    case ELEMENT_TYPE_TETRA:
      betype = ELEMENT_TYPE_TRI;
      break;

    case ELEMENT_TYPE_CUBE:
      betype = ELEMENT_TYPE_RECT;
      break;
    
    default:
      std::cerr << "MakeBoundaryElement node pattern illegal element\n";
      assert(1==0);
    }
  }
  assert(etype == e);
  return;
}

void BoundaryElementNodePattern::MakePattern()  // boundary version
{
  listIterator <Element *>itr(elementPtrLst);

  for(itr.init(); !itr; ++itr) {

    // boundary
    Element *bePtr;
    bePtr = itr()->AcquireBoundaryElementPtr();
    bePtr->SetNodePtrInGivenList(nodeOrderedPtrLst);  // Boundary
  }
  

  // check write
  listIterator <Node *>iii(nodeOrderedPtrLst);
  int no = 0;

  //  cerr << "CHECK at BoundaryElementNodePattern.cpp" << endl;
  //  for(iii.init(); !iii; ++iii) {
  //    no++;
  //    cerr << "No. " << no << " : ";
  //    iii()->print(cerr);
  //    cerr << endl;
  //  }
   
//  abortExit("show boundary node");
  
  
  if(numberOfEWISEVariables > 0) {
    
    switch(etype) {
    case ELEMENT_TYPE_LINE:
      ewiseNodePtr = new Node(etype,0.0);
      break;

    case ELEMENT_TYPE_TRI:
      ewiseNodePtr = new Node(etype,1.0/3.0,1.0/3.0);
      break;
      
    case ELEMENT_TYPE_RECT:
      ewiseNodePtr = new Node(etype,0.0,0.0);
      break;
	
    case ELEMENT_TYPE_TETRA:
      ewiseNodePtr = new Node(etype,1.0/4.0,1.0/4.0,1.0/4.0);
      break;
      
    case ELEMENT_TYPE_CUBE:
      ewiseNodePtr = new Node(etype,0.0,0.0,0.0);
      break;

    default:
      assert(1==0);
    }

    if(nodeOrderedPtrLst.includes(ewiseNodePtr)) {

      ewiseNodeNo = nodeOrderedPtrLst.getPosition(ewiseNodePtr);
      
      delete ewiseNodePtr;
      ewiseNodePtr = 0;
    }
    else {
      nodeOrderedPtrLst.add(ewiseNodePtr);
      ewiseNodeNo = nodeOrderedPtrLst.getPosition(ewiseNodePtr);
    }
  }
  nodes = nodeOrderedPtrLst.getNumberOfElements();

  if(numberOfEWISEVariables > 0) {
    assert( nodes == ewiseNodeNo);
    // currently, mid node must be the final node from Node.eval
    // implementation.
  }
  MakeElementEquationNo();

  return;
}

int BoundaryElementNodePattern::GetNodes()
{
  return(nodes);
}

int BoundaryElementNodePattern::GetTotalFreedom()
{
  return(totalFreedom);
}

int BoundaryElementNodePattern::GetEwiseFreedom()
{
  return(ewiseFreedom);
}

int *BoundaryElementNodePattern::MakeIEDPcopy(void)
{
  int *retPtr;
  assert( totalFreedom > 0);
  retPtr = new int[totalFreedom];
  for(int i=0;i<totalFreedom;i++) {
    *(retPtr+i) = *(iedp + i);
  }
  return(retPtr);
}

int *BoundaryElementNodePattern::MakeIENPcopy(void)
{
  int *retPtr;
  assert( totalFreedom > 0);
  retPtr = new int[totalFreedom];
  for(int i=0;i<totalFreedom;i++) {
    *(retPtr+i) = *(ienp + i);
  }
  return(retPtr);
}

int *BoundaryElementNodePattern::MakeNENFREcopy(void)
{
  int *retPtr;
  assert( nodes > 0);
  retPtr = new int[nodes];
  for(int i=0;i<nodes;i++) {
    *(retPtr+i) = *(nenfre + i);
  }
  return(retPtr);
}
