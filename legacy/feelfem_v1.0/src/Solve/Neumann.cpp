/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : Neumann.cpp
 *  Date     : 1999/11/30
 *  Modified : 1999/11/30
 *             2002/03/28 boundary integrand
 *  
 *  
 *  Purpose  : Neumann class
 *  
 */

#include <assert.h>

#include "feeldef.hpp"
#include "feelfuncs.hpp"

#include "Object.hpp"

#include "Variable.hpp"
#include "Neumann.hpp"

#include "NeumannGeom.hpp"

Neumann::Neumann()
{ 
  solveNo = 0;
  ncondNo = 0;
  nbedtNo = 0;

  nGeoms  = 0;

  spaceDim = 0;

  NPG     = 0;
  NDF     = 0;

  qxFlag  = NO;
  qyFlag  = NO;
  qzFlag  = NO;
  
  normalFlag     = NO;

  nxFlag  = NO;
  nyFlag  = NO;
  nzFlag  = NO;

  tangentialFlag = NO;

  unknowns = 0;             // used for ApplyGalerkin(), etc.

  nBENPPtr = 0;             // Neumann BoundaryElementNodePattern pointer

  return;
}

Neumann::~Neumann()
{ 
  return;
}

// Set series
void Neumann::SetSolveNo( int no )
{
  solveNo = no;
  return;
}

void Neumann::SetNcondNo( int no )
{
  ncondNo = no;
  return;
}

void Neumann::SetNbedtno( int no )
{
  nbedtNo = no;
  return;
}

// Use series
void Neumann::UseX(void)
{
  qxFlag = YES;
  return;
}

void Neumann::UseY(void)
{
  qyFlag = YES;
  return;
}

void Neumann::UseZ(void)
{
  qzFlag = YES;
  return;
}

// 
void Neumann::UseNX(void)
{
  nxFlag = YES;
  return;
}

void Neumann::UseNY(void)
{
  nyFlag = YES;
  return;
}

void Neumann::UseNZ(void)
{
  nzFlag = YES;
  return;
}

int Neumann::IsUseX(void)
{
  return(qxFlag);
}

int Neumann::IsUseY(void)
{
  return(qyFlag);
}

int Neumann::IsUseZ(void)
{
  return(qzFlag);
}

int Neumann::IsUseNX(void)
{
  return(nxFlag);
}

int Neumann::IsUseNY(void)
{
  return(nyFlag);
}

int Neumann::IsUseNZ(void)
{
  return(nzFlag);
}

// test series
void Neumann::testSetNbedtno( int no)
{
  nbedtNo = no;
  return;
}

void Neumann::AddVariablePtr(Variable *varPtr)
{
   if(varPtrLst.includes( varPtr )) {
    return;
  }
   varPtrLst.add(varPtr);
  return;
}

// for Neumann data pair
void Neumann::AddNeumannDataSSPairPtr( StrStrPair *ptr)
{
  neumannPairDataPtrLst.addlast(ptr);
  return;
}


void Neumann::operator =(const Neumann &src)
{
  cout << "Neumann operator = called\n";
  nbedtNo       = src.nbedtNo;
  //  neumannVarPtr = src.neumannVarPtr;
  varPtrLst     = src.varPtrLst;
  return;
}

int Neumann::GetNbedtno(void)
{
  return(nbedtNo);
}

void Neumann::AddNeumannGeomPtr(NeumannGeom *ngPtr)
{
  nGeoms++;
  neumannGeomPtrLst.addlast(ngPtr);
  return;
}

int  Neumann::GetNumberOfNeumannGeoms(void)
{
  return(nGeoms);
}

NeumannGeom *Neumann::GetIthNeumannGeomPtr(int i)
{
  assert(i < nGeoms);
  NeumannGeom *ngPtr = neumannGeomPtrLst.getNthElement(i+1);
  return(ngPtr);
}

// for bounary integrand

// from SNsolve_
void Neumann::SetBoundaryIntegrandSetPtr(BoundaryIntegrandSet *ptr) 
{
  bIntegrandSetPtr = ptr;
  return;
}

// from SNsolve_Infogenerate_Neumann.cpp (for boundary integration)
void Neumann::AddUnknownVariablePtr(Variable *ptr)
{
  unknownVarPtrLst.addlast(ptr);
  unknowns++;

  return;
}

void Neumann::AddTestfuncStr(string &testfuncSymbol)
{
  testfuncSymbolLst.addlast(testfuncSymbol);
  return;
}

// parametric element
void Neumann::SetParametricElement(string &paraElementName)
{
  parametricElementPtr = feelfemobj.GetElementPtrByName(paraElementName);
  return;
}

void Neumann::SetSpaceDim(int n)
{
  spaceDim = n;
  return;
}

int Neumann::GetFirstNeumannGeomNo_DOTMP(void)
{
  listIterator <NeumannGeom *>itr(neumannGeomPtrLst);
  
  itr.init();
 
  return(itr()->GetNeumannGeomNo() );
}
