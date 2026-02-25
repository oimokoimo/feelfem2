/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SolveElement.cpp
 *  Date     : 1999/11/17
 *  Modified : 1999/11/17
 *  
 *  Purpose  : SolveElement instance
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
#include "feelfuncs.hpp"
#include "Object.hpp"         // for quadStr -> Quadrature *
#include "Configure.hpp"

#include "SolveElement.hpp"

#include "IntegrandSet.hpp"

int operator ==(const SolveElement &se1,const SolveElement &se2)
{
	std::cout << "Compareing SolveElements, its may be wrong!\n";
  exit(1);
  return(0);
}

SolveElement::SolveElement()
{
  solveNo     = 0;
  elemNo      = 0;
  edatno      = 0;
  sub_edatno  = 0;
  sub_mats    = 0;
  etype       = 0;
  spaceDim    = 0;

  unknowns    = 0;

  quadratures = 0;  // initialize

  nonlinearFlag = NO;

  seENPPtr      = 0;   // SolveElement ElementNodePattern Pointer

  parametricElementPtr = 0;   // parametric element pointer (020219)

  return;  
}

SolveElement::~SolveElement() = default;


void SolveElement::SetSpaceDim(int n)
{
  assert( n >= 1 && n <= 3);
  spaceDim = n;
  return;
}

int SolveElement::GetSolveNo(void)
{
  return(solveNo);
}

int SolveElement::GetElemNo(void)
{
  return(elemNo);
}

int SolveElement::GetNode(void)
{
  return(nodes);                  // number of nodes for ielem
}
int SolveElement::GetNdf(void)
{
  return(ndf);
}

int SolveElement::GetEdatno(void)
{
 
  return(edatno);
}


// Quadratures
void SolveElement::SetMainQuadratureName( string &qName )
{
  assert(quadratures == 0);
  assert(quadraturePtrLst.getNumberOfElements() == 0);
  quadratures++;
  
  Quadrature *qPtr;


  if(qName == DEFAULT_STRING) {
    qPtr = feelfemconf.GetDefaultQuadraturePtrByEtype( etype );
  }
  else {
    qPtr = feelfemobj.GetQuadraturePtrByName( qName );
  }

  quadraturePtrLst.add(qPtr);

  return;
}

void SolveElement::AddQuadratureName( string qName)
{
  Quadrature *qPtr = feelfemobj.GetQuadraturePtrByName( qName );

  quadraturePtrLst.addlast(qPtr);
  quadratures++;

  return;
}

// weak form, integrand
void SolveElement::AddIntegrandSetPtr( IntegrandSet *isetPtr)
{
  integrandSetLst.addlast(isetPtr);
  
  return;
}

// Get functions

int SolveElement::GetQuadratures(void)
{
  return(quadratures);
}

Quadrature *SolveElement::GetIthQuadraturePtr(int i)
{
  if(i < 0 || i >= quadratures) {
	  std::cerr << "Illegal no indicated in SolveElement::GetIthQuadraturePtr\n";
    exit(1);
  }
  
  listIterator <Quadrature *> itr(quadraturePtrLst);
  for(itr.init(); !itr; ++itr) {
    if(i==0) {
      return(itr());
    }
    i--;
  }
  std::cerr << "Illegal in SolveElement::GetIthQuadraturePtr\n";
  exit(1);
}

int SolveElement::GetIthIEDP(int i)
{
  if(i < 0 || i >= ndf) {
	  std::cerr << "Illegal i in SolveElement::GetIthIEDP\n";
    exit(1);
  }
  return(*(iedp+i));
}

int SolveElement::GetIthIENP(int i)
{
  if(i < 0 || i >= ndf) {
	  std::cerr << "Illegal i in SolveElement::GetIthIENP\n";
    exit(1);
  }
  return(*(ienp+i));
}


int SolveElement::GetNenfre(int no)
{
  assert(no >=0 && no <nodes);
  return(*(nodeFreedom + no));
}

// Information generate
void SolveElement::SetSolveNo(int no)
{
  solveNo = no;
  return;
}

void SolveElement::SetElemNo(int no)
{
  elemNo = no;
  return;
}

void SolveElement::SetEtype (int n )
{
  etype = n;
  return;
}

// parametric element
void SolveElement::SetParametricElement(string &paraElementName)
{
  parametricElementPtr = feelfemobj.GetElementPtrByName(paraElementName);
  return;
}

// from SNsolve_Infogenerate
void SolveElement::AddUnknownVariablePtr(Variable *ptr)
{
  unknownVarPtrLst.addlast(ptr);
  unknowns++;

  return;
}

// from SNsolve_Infogenerate
void SolveElement::AddVariablePtr_uniq_exceptUnknown(Variable *vPtr)
{
  if(unknownVarPtrLst.includes(vPtr) ) return;   // except Unknown
  if(varPtrLst.includes(vPtr)        ) return;   // uniq

  varPtrLst.add(vPtr);
  return;
}

// from SNsolve_Infogenerate.cpp
void SolveElement::AddVariablePtr_nonlinearCase(Variable *vPtr)
{
  varPtrLst.add(vPtr);    // without any judgment
  return;
}

DiscretizedComponent *SolveElement::GetIthDiscretizedComponentPtr(int i)
{
  DiscretizedComponent *dcPtr;
  dcPtr = discretizedCompPtrLst.getNthElement(i+1);
  return(dcPtr);
}

EcalInfo *SolveElement::GetIthEcalInfoPtr(int i)
{
  EcalInfo *eiPtr;
  eiPtr = ecalInfoPtrLst.getNthElement(i+1);
  return(eiPtr);
}

EsetInfo *SolveElement::GetIthEsetInfoPtr(int i)
{
  EsetInfo *esetInfoPtr;
  esetInfoPtr = esetInfoPtrLst.getNthElement(i+1);
  return(esetInfoPtr);
}

void SolveElement::AddTestfuncStr(string &testfuncSymbol)
{
  testfuncSymbolLst.addlast(testfuncSymbol);
  return;
}

Element *SolveElement::GetParametricElementPtr(void)  // called from ecal cg.
{
  return(parametricElementPtr);
}

int SolveElement::GetNumberOfUnknowns(void)
{
  return(unknowns);
}
