/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : Element.cpp
 *  Date     : 2001/03/28
 *  Modified : 
 *  
 *  Purpose  :
 *  
 */
#include <assert.h>

#include "feeldef.hpp"
#include "Element.hpp"
//#include "../parser/Syntax/SNunit.hpp"
//#include "../parser/Syntax/SNelement.hpp"
//#include "../parser/Syntax/SNelementDoubleVar.hpp"
//#include "../parser/Syntax/SNelementAssignment.hpp"
//#include "../parser/Syntax/SNelementIntp.hpp"

Element::Element()
{
  estno_termConvert = 0;
  elementEtype      = 0;
  elementType       = 0;
  numberOfNodes     = 0;
  numberOfFreedom   = 0;
  numberOfRegionFreedom = 0;
  
  coordinateDependFlag = NO;

  boundaryElementFlag = NO;
  bElementPtr         = 0;   // for neumann condition
  rElementPtr         = 0;   // for parent element ptr
  bInterpolationFlag  = 0;   // null pointer

  return;
}

Element::~Element()
{
  cerr << "ELEMENT DESTRUCTOR IS CALLED...\n";
  return;
}

void Element::SetName(const char *nm) 
{
  name = nm;
  return;
}

void Element::SetEtype(int e) 
{
  elementEtype = e;
  return;
}

void Element::SetType(int t)
{
  elementType = t;
  return;
}

void Element::SetNumberOfNodes(int nds)
{
  numberOfNodes = nds;
  return;
}

void Element::SetNumberOfFreedom(int f)
{
  numberOfFreedom = f; 
  return;
}

// used in ElementNodePattern::MakePattern()
void Element::SetNodePtrInGivenList( orderedPtrList <Node *>& oNdLst)
{
  Node *nPtr;
  listIterator <Node *>itr(nodePtrLst);

  for(itr.init();!itr;++itr) {
    
    nPtr = itr();

    if(oNdLst.includes(nPtr)) continue;

    oNdLst.add(nPtr);
  }
  return;
}

// used in ElementNodePattern::MakeElementEquationNo()
Node *Element::GetIthInterpolationNodePtr( int ith )
{
  Interpolation *ipPtr;
  Node *nPtr;

  assert( 0 <= ith && ith < numberOfFreedom );

  ipPtr = interpPtrLst.getNthElement(ith + 1);

  nPtr = ipPtr->GetNodePtr();

  assert(nPtr != 0);
  
  return(nPtr);
}

// used in ElementNodePattern::MakeElementEquationNo()
Node *Element::GetIthInterpolationBoundaryNodePtr( int ith )
{
  assert( boundaryElementFlag == YES);
  assert( 0 <= ith && ith < numberOfRegionFreedom );  // boundary interp has
                                                      // the same number of 
                                                      // interpolations
  Interpolation *ipPtr;
  Node *nPtr;

  ipPtr = interpPtrLst.getNthElement(ith + 1);

  nPtr = ipPtr->GetBoundaryNodePtr();                 // boundary node

  assert(nPtr != 0);
  
  return(nPtr);
}

int Element::HasAlreadyDefinedNode( Node *ndPtr) 
{
  if(nodePtrLst.includes(ndPtr)) {
    return(YES);
  }
  else {
    return(NO);
  }
}

void Element::AddNodePtr( Node *ndPtr )  // this is allocated in SNelement
{
  nodePtrLst.add(ndPtr);
  return;
}

int operator ==(const Element &left, const Element &right)
{
  return(left.name == right.name);
}

const char *Element::GetName()
{
  return( const char *)name;
}

void Element::SetEstNo(int no)
{
  assert(estno_termConvert == 0);
  assert(boundaryElementFlag  == NO);
  estno_termConvert = no;  
  return; 
}

int Element::GetEstNo(void)
{ 
  assert(estno_termConvert    != 0 );
  assert(boundaryElementFlag  == NO);
  return estno_termConvert; 
}

void Element::initWorkTC(void)
{
  assert(boundaryElementFlag  == NO);
  estno_termConvert = 0;
  return;
}

void Element::AddInterpolationPtr(Interpolation *ptr)
{
  //  cerr << "AddInterpolationPtr " <<endl;
  //  ptr->print(cerr);
  //  cerr << "---" << endl;

  assert(!interpPtrLst.includes(ptr));

  interpPtrLst.add(ptr);
  return;
}

Interpolation* Element::GetIthInterpolationPtr(int i)
{
  Interpolation *iPtr;

  iPtr = interpPtrLst.getNthElement(i+1);
  
  assert(iPtr != 0);

  return(iPtr);
}
