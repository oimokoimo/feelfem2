/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : BoundaryElement.cpp
 *  Date     : 2002/03/21
 *  Modified : 
 *  
 *  Purpose  :
 *  
 */
#include <assert.h>

#include "feeldef.hpp"
#include "feelfuncs.hpp"

#include "Element.hpp"
#include "TermConvert.hpp"

Element *Element::AcquireBoundaryElementPtr(void)
{
  assert(boundaryElementFlag == NO);
  
  if(bElementPtr != 0) {
    return(bElementPtr);
  }

  MakeBoundaryElement();

  return(bElementPtr);
}

void Element::MakeBoundaryElement()
{
  TermConvert tc;
  
  switch(elementEtype) {
  case ELEMENT_TYPE_TRI:
    MakeBoundaryElement_tri(tc);
    break;

  case ELEMENT_TYPE_RECT:
    MakeBoundaryElement_rect(tc);
    break;

  case ELEMENT_TYPE_TETRA:
    MakeBoundaryElement_tetra(tc);
    break;

  case ELEMENT_TYPE_CUBE:
    MakeBoundaryElement_cube(tc);
    break;
    
  default:
    cerr << "MakeBoundaryElement illegal element\n";
    assert(1==0);
  }
  return;
}

int Element::GetIthOriginalIplus1(int ith)
{
  assert(boundaryElementFlag == YES);

  // used in TermConvert_MakeReverse_boundary.cpp
  int total = interpPtrLst.getNumberOfElements();
  
  int ith_finder = 0;
  for(int i = 0; i<total; i++) {
    
    if(bInterpolationFlag[i] == 1) {
      ith_finder++;
    }

    if(ith_finder == ith+1) {
      return(i+1);
    }

  }
  assert(1==0);
  return(-999);
}

Node *Element::GetIthBoundaryInterpolationNodePtr( int ith )
{
  int bno             = GetIthOriginalIplus1(ith);
  Interpolation *iPtr = GetIthInterpolationPtr( bno-1 );
  Node         *ndPtr = iPtr->GetBoundaryNodePtr();

  return(ndPtr);
}

Element *Element::GetParentElementPtr(void)
{
  assert(rElementPtr != 0);

  return(rElementPtr);
}
