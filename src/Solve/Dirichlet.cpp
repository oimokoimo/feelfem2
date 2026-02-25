/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : Dirichlet.cpp
 *  Date     : 1999/11/30
 *  Modified : 1999/11/30
 *             2002/04/19 (BCN)  temporary coding for GiD
 *  
 *  Purpose  : Dirichlet class
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

#include "list.hpp"
#include "Variable.hpp"
#include "Dirichlet.hpp"

#include "DirichletGeom.hpp"

Dirichlet::Dirichlet()
{ 
  solveNo = 0;
  dcondNo = 0;
  nsetno  = 0;
  
  dirichletVarPtr = 0;   // pointer initialize

  dGeoms  = 0;
  
  return;
}


Dirichlet::~Dirichlet() = default;


void Dirichlet::operator =(const Dirichlet &src)
{ 
	std::cout << "Dirichlet operator = called\n";
  nsetno          = src.nsetno;
  dirichletVarPtr = src.dirichletVarPtr;
  varPtrLst       = src.varPtrLst;
  return;
}

// Set series
void Dirichlet::SetSolveNo(int no)
{
  solveNo = no;
  return;
}

void Dirichlet::SetDcondNo(int no)
{
  dcondNo = no;
  return;
}

void Dirichlet::SetNsetno( int no)
{
  nsetno = no;
  return;
}

void Dirichlet::SetDirichletVarPtr( Variable *ptr )
{
  dirichletVarPtr = ptr;
  return;
}

// Add Variable pointer
void Dirichlet::AddVariablePtr(Variable *varPtr)
{
   if(varPtrLst.includes( varPtr )) {
    return;
  }
   varPtrLst.add(varPtr);
  return;
}

// Get series
int Dirichlet::GetNsetno(void)
{
  return(nsetno);
}


void Dirichlet::SetDataExprStr( char *expr )
{
  dDataExpr = expr;
  return;
}

void Dirichlet::SetDataSimpleExprStr( char *expr )
{
  dDataSimpleExpr = expr;
  return;
}


// test series
void Dirichlet::testSetNsetno( int no)
{
  nsetno = no;
  return;
}


void Dirichlet::testSetTestExpression( const char *str)
{
  testExpression = str;
  return;
}

const char *Dirichlet::testGetTestExpression( void)
{
  return(testExpression);
}

void Dirichlet::AddDirichletGeomPtr(DirichletGeom *dgPtr)
{
  dGeoms++;
  
  dirichletGeomPtrLst.addlast(dgPtr);
  return;
}

int  Dirichlet::GetNumberOfDirichletGeoms(void)
{
  return(dGeoms);
}

DirichletGeom *Dirichlet::GetIthDirichletGeomPtr(int i)
{
  assert(i < dGeoms);
  DirichletGeom *dgPtr = dirichletGeomPtrLst.getNthElement(i+1);
  return(dgPtr);
}

int Dirichlet::GetFirstDirichletGeomNo_DOTMP(void)
{
  listIterator <DirichletGeom *>itr(dirichletGeomPtrLst);
  
  itr.init();

  return(itr()->GetDirichletGeomNo() );
}
