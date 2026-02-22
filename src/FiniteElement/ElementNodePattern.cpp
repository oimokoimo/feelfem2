/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : ElementNodePattern.hpp
 *  Date     : 2002/01/31
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

#include "ElementNodePattern.hpp"

#include "feelfuncs.hpp"
#include "Object.hpp"

ElementNodePattern::ElementNodePattern(void)
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

  ienp   = nullptr;  // pointer initialize
  iedp   = nullptr;  // pointer initialize
  nenfre = nullptr;  // pointer initialize

  return;
}


ElementNodePattern::~ElementNodePattern(void)
{
  if(ienp != nullptr) {
    delete [] ienp;   ienp = nullptr;
  }
  if(iedp != nullptr) {
    delete [] iedp;   iedp = nullptr;
  }
  if(nenfre != nullptr) {
    delete [] nenfre; nenfre = nullptr;
  }

  return;
}



void ElementNodePattern::AddUnknownVariable(Variable *varPtr)
{
  unknowns++;
  unknownVarPtrLst.addlast(varPtr);

  int type;
  type = varPtr->GetType();

  Element *ePtr;

  switch(type) {
  case VAR_FEM:
    ePtr = varPtr->GetElementPtr();
    numberOfFEMVariables++;

    totalFreedom += ePtr->GetElementFreedom();
    SetEtype(ePtr->GetEtype());

    if(!elementPtrLst.includes(ePtr)) {
      elementPtrLst.add(ePtr);
    }

    break;

  case VAR_VFEM:
    ePtr = varPtr->GetElementPtr();
    numberOfVFEMVariables++;

    totalFreedom += ePtr->GetElementFreedom();
    SetEtype(ePtr->GetEtype());

    if(!elementPtrLst.includes(ePtr)) {
      elementPtrLst.add(ePtr);
    }
    std::cerr << "vfem\n";
    
    assert(1==0);
    break;

  case VAR_EWISE_A:
    assert(varPtr->GetEwiseType() == EWISE_TYPE_INTERPOLATION);
    ePtr = varPtr->GetElementPtr();
    numberOfEWISEVariables++;

    totalFreedom   += ePtr->GetElementFreedom();
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


void ElementNodePattern::AddNodeByVariable( Variable *varPtr )
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


void ElementNodePattern::AddNodeByElement( Element *ePtr )
{
  if(!elementPtrLst.includes(ePtr)) {
    elementPtrLst.add(ePtr);
  }
  return;
}

void ElementNodePattern::SetEtype(int e)
{
  if(etype == 0) {
    etype = e;
    return;
  }
  assert(etype == e);
  return;
}


// Making new node for ewise unknowns,  this may be changed in the future
// Similar function is MakePatternEwiseQuad, where only node order pattern
// is made
void ElementNodePattern::MakePattern()
{
  listIterator <Element *>itr(elementPtrLst);

  for(itr.init(); !itr; ++itr) {
    itr()->SetNodePtrInGivenList(nodeOrderedPtrLst);
  }
  
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

void ElementNodePattern::MakePatternEwiseQuad()
{
  listIterator <Element *>itr(elementPtrLst);

  for(itr.init(); !itr; ++itr) {
    itr()->SetNodePtrInGivenList(nodeOrderedPtrLst);
  }
  
  nodes = nodeOrderedPtrLst.getNumberOfElements();

  return;
}


int ElementNodePattern::GetNodes()
{
  return(nodes);
}

int ElementNodePattern::GetTotalFreedom()
{
  return(totalFreedom);
}

int ElementNodePattern::GetEwiseFreedom()
{
  return(ewiseFreedom);
}

int *ElementNodePattern::MakeIEDPcopy(void)
{
  int *retPtr;
  assert( totalFreedom > 0);
  retPtr = new int[totalFreedom];
  for(int i=0;i<totalFreedom;i++) {
    *(retPtr+i) = *(iedp + i);
  }
  return(retPtr);
}

int *ElementNodePattern::MakeIENPcopy(void)
{
  int *retPtr;
  assert( totalFreedom > 0);
  retPtr = new int[totalFreedom];
  for(int i=0;i<totalFreedom;i++) {
    *(retPtr+i) = *(ienp + i);
  }
  return(retPtr);
}

int *ElementNodePattern::MakeNENFREcopy(void)
{
  int *retPtr;
  assert( nodes > 0);
  retPtr = new int[nodes];
  for(int i=0;i<nodes;i++) {
    *(retPtr+i) = *(nenfre + i);
  }
  return(retPtr);
}
