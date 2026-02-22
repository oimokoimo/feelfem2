/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : Node.cpp   (Inside of elements)
 *  Date     : 2002/01/03
 *  Modified : 2002/01/06 (operator implementation)
 *             2002/01/08 (eval() function )
 *  
 *  Purpose  : constructors
 *  
 *             operators (== and <)
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

#include "feeldef.hpp"
#include "FiniteElement.hpp"
#include "Node.hpp"

Node::Node(int e)
{
  dimension = 0;

  assert(e == ELEMENT_TYPE_POINT);
  etype     = ELEMENT_TYPE_POINT ;

  return;
}

Node::Node(int e,double r)
{
  dimension = 1;
  xi        = r;
  assert(e == ELEMENT_TYPE_LINE);
  etype     = ELEMENT_TYPE_LINE;


  eta       = 0.0;
  zeta      = 0.0;
  return;
}

Node::Node(int e,double r,double s)
{
  dimension = 2;
  xi        = r;
  eta       = s;
  zeta      = 0.0;

  assert( (e == ELEMENT_TYPE_TRI) || (e == ELEMENT_TYPE_RECT) );
  etype     = e;

  return;
}

Node::Node(int e,double r,double s,double t)
{
  dimension = 3;
  xi        = r;
  eta       = s;
  zeta      = t;

  assert( (e == ELEMENT_TYPE_TETRA) || (e == ELEMENT_TYPE_CUBE) );
  etype     = e;

  return;
}

// destructor
Node::~Node() = default;

// evaluator interface
double Node::eval(void) const
{
  double val;

  switch(etype) {

  case ELEMENT_TYPE_POINT:
    val = evalNodePoint();
    break;

  case ELEMENT_TYPE_LINE:
    val = evalNodeLine( xi );
    break;

  case ELEMENT_TYPE_TRI:
    val = evalNodeTri(xi,eta);
    break;


  case ELEMENT_TYPE_RECT:
    val = evalNodeRect(xi,eta);
    break;

  case ELEMENT_TYPE_TETRA:
    val = evalNodeTetra(xi,eta,zeta);
    break;

  case ELEMENT_TYPE_CUBE:
    val = evalNodeCube(xi,eta,zeta);
    break;

  default:
    assert(1==0);
  }
  return(val);
}


int operator ==(const Node &left, const Node &right)
{
  if(left.dimension != right.dimension) {
	  std::cerr << "Try to compare nodes of different dimension numbers.\n";
    assert(1==0);
    return(1 == 0);
  }

  switch(left.dimension) {
    
  case 1:
    return(left.xi == right.xi);

  case 2:
    return(left.xi  == right.xi  && 
	   left.eta == right.eta     );
    
  case 3:
    return(left.xi   == right.xi    && 
	   left.eta  == right.eta   &&
	   left.zeta == right.zeta    );
    
  default:
    break;
    assert(1==0);

  }

  assert(1==0);
  return(-1);
}


int operator < (const Node &left, const Node &right)
{
  double lval,rval;
  
  lval = left.eval();
  rval = right.eval();

  return (lval < rval);
}

  
