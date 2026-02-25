/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : Solve.cpp
 *  Date     : 1999/10/26
 *  Modified : 1999/12/02
 *  Modified : 2001/02/02 orderedPtrList
 *  
 *  Purpose  : solve.cpp (for test)
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

#include "Dirichlet.hpp"
#include "Neumann.hpp"
#include "Solve.hpp"

Solve::Solve()   // Constructor
{
  solves++;
  solveNo = solves;

  solveElements       = 0;
  dirichletConditions = 0;
  neumannConditions   = 0;

  nonlinearFlag = 0;
  unknowns      = 0;   // ???
  maxnodes    = 0;
  libraryType = 0;

  makeVariablePtrLstComeyetFlag = 0;

  return;
}

Solve::~Solve() = default;  // Deconstructor
   

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//
void Solve::SetSpaceDim(int n)
{
  spaceDim = n;
  return;
}

int Solve::GetSpaceDim(void)
{
  return(spaceDim);
}


int Solve::GetSolveNo(void)
{
  return (solveNo);
}

int Solve::GetLibraryType(void)
{
  return(libraryType);
}

int Solve::GetProgramModelType(void)
{
  return(programModelType);
}

void Solve::AddVariablePtr(Variable *varPtr)
{
   if(solveVariablePtrLst.includes( varPtr )) {
    return;
  }
  solveVariablePtrLst.add(varPtr);
  return;
}

void Solve::AddSolveElementPtr( SolveElement *ptr)
{
  solveSolveElementPtrLst.addlast(ptr);
  solveElements++;
  return;
}

void Solve::AddDirichletDataPtr( Dirichlet *ptr)
{
  solveDirichletPtrLst.addlast(ptr);
  dirichletConditions++;
  return;
}

void Solve::AddNeumannDataPtr( Neumann *ptr)
{
  solveNeumannPtrLst.addlast(ptr);
  neumannConditions++;
  return;
}

int Solve::GetMaxnodes()
{
  return(maxnodes);
}

///////////////////////////////////////////
//  SolveElement 
///////////////////////////////////////////
int Solve::GetSolveElements()
{
  return(solveElements);
}

SolveElement *Solve::GetIthSolveElementPtr( int i)
{
  assert(i < solveElements);

  listIterator <SolveElement *> itr(solveSolveElementPtrLst);
  for(itr.init(); !itr; ++itr){
    if(i==0) return (itr());
    i--;
  }
  assert(1==-1);
}
    
///////////////////////////////////////////
//  Dirichlet Data
///////////////////////////////////////////
int Solve::GetDconds()
{
  return(dirichletConditions);
}

Dirichlet *Solve::GetIthDirichletDataPtr(int no)
{
  if(no < 0 || no >=dirichletConditions) {
    assert(1==0);
  }
  listIterator <Dirichlet *>itr(solveDirichletPtrLst);
  int i = 0;
  for(itr.init(); !itr;++itr) {
    if(i == no) {
      return(itr());
    }
    i++;
  }
  assert(1==0);
  exit(1);
}

int Solve::GetIthDirichletNsetno(int no)
{
  if(no < 0 || no >=dirichletConditions) {
    assert(1==0);
  }
  listIterator <Dirichlet *>itr(solveDirichletPtrLst);
  int i = 0;
  for(itr.init(); !itr;++itr) {
    if(i == no) {
      return(itr()->GetNsetno());
    }
    i++;
  }
  assert(1==0);
}

orderedPtrList <Variable *>Solve::GetIthDirichletVariablePtrLst(int no)
{
  if(no < 0 || no >=dirichletConditions) {
    assert(1==0);
  }
  listIterator <Dirichlet *>itr(solveDirichletPtrLst);
  int i = 0;
  for(itr.init(); !itr;++itr) {
    if(i == no) {
      return(itr()->GetVariablePtrLst());
    }
    i++;
  }
  assert(1==0);
}
    
///////////////////////////////////////////
//  Neumann Data
///////////////////////////////////////////
int Solve::GetNconds()
{
  return(neumannConditions);
}

Neumann *Solve::GetIthNeumannDataPtr(int no)
{
  if(no < 0 || no >=neumannConditions) {
    assert(1==0);
  }
  listIterator <Neumann *>itr(solveNeumannPtrLst);
  int i = 0;
  for(itr.init(); !itr;++itr) {
    if(i == no) {
      return(itr());
    }
    i++;
  }
  assert(1==0);
  exit(1);
}


int Solve::GetIthNeumannNbedtno(int no)
{
  if(no < 0 || no >=neumannConditions) {
    assert(1==0);
  }
  listIterator <Neumann *>itr(solveNeumannPtrLst);
  int i = 0;
  for(itr.init(); !itr;++itr) {
    if(i == no) {
      return(itr()->GetNbedtno());
    }
    i++;
  }
  assert(1==0);
}

orderedPtrList <Variable *>Solve::GetIthNeumannVariablePtrLst(int no)
{
  if(no < 0 || no >=neumannConditions) {
    assert(1==0);
  }
  listIterator <Neumann *>itr(solveNeumannPtrLst);
  int i = 0;
  for(itr.init(); !itr;++itr) {
    if(i == no) {
      return(itr()->GetVariablePtrLst());
    }
    i++;
  }
  assert(1==0);
}
