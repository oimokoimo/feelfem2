/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : Interpolation.cpp
 *  Date     : 2002/03/03
 *  Modified : 2002/04/01
 *  
 *  Purpose  : Storage class for interpolation data
 *  
 */

#include <assert.h>

#include "string.hpp"
#include "Node.hpp"
#include "Interpolation.hpp"

Interpolation::Interpolation()
{
  type    = 0;
  nodePtr = 0;   
  boundaryNodePtr = 0;

  return;
}

Interpolation::~Interpolation()
{
  return;
}

void Interpolation::SetType(int t)
{
  type = t;
  return;
}

void Interpolation::SetExprStr(char *cp)
{
  exprStr = cp;
  return;
}

void Interpolation::SetNodePtr(Node *ptr)
{
  nodePtr = ptr;
  return;
}

void Interpolation::SetBoundaryNodePtr(Node *ptr)
{
  boundaryNodePtr = ptr;
  return;
}

Node *Interpolation::GetNodePtr(void)
{
  return(nodePtr);
}

Node *Interpolation::GetBoundaryNodePtr(void)   // for boundary element
{
  return(boundaryNodePtr);
}

int operator < (const Interpolation &left, const Interpolation &right)
{
  if(left.type != right.type) {
    return( left.type  < right.type );
  }

  assert(!( *(left.nodePtr) == *(right.nodePtr)));

  return( *(left.nodePtr) < *(right.nodePtr));
}

int operator == (const Interpolation &left, const Interpolation &right)
{
  if(left.type != right.type) {
    return( left.type == right.type );
  }
  return( *(left.nodePtr) == *(right.nodePtr));
}
