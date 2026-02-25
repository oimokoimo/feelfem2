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
 */
#include <stdlib.h>
#include <iostream.h>
#include "SolveElement.hpp"


void SolveElement::testSetSolveNo(int no)
{
  solveNo = no;
  return;
}

void SolveElement::testSetElemNo(int no)
{
  elemNo = no;
  return;
}

void SolveElement::testSetNonlinearFlag(int no)
{
  nonlinearFlag = no;
  return;
}

void SolveElement::testSetUnknowns(int n)
{
  unknowns = n;
  return;
}

void SolveElement::testSetEdatno(int no)
{
  edatno = no;
  return;
}

void SolveElement::testSetIelemNodes(int n)
{
  ielemNodes = n;
  return;
}

void SolveElement::testSetNodeFreedom(int n,int *iptr)
{
  nodeFreedom = new int[n];
  nodes       =  n;
  for(int i=0;i<nodes;i++) {
    *(nodeFreedom+i) = *(iptr+i);
  }
  return;
}

void SolveElement::testAddVariablePtr(Variable *ptr)
{
  varPtrLst.add(ptr);
  return;
}

void SolveElement::testAddUnknownVariablePtr(Variable *ptr)
{
  unknownVarPtrLst.addlast(ptr);
  return;
}

void SolveElement::testAddQuadraturePtr(Quadrature *ptr)
{
  quadratures++;
  quadraturePtrLst.addlast(ptr);
  return;
}

void SolveElement::testSetNDFIENPIEDP( int n, int *ienpPtr, int *iedpPtr)
{
  ndf  = n;
  ienp = ienpPtr;
  iedp = iedpPtr;

  return;
}

void SolveElement::testAddEcalArgs( char *term )
{
  string a(term);
  testEcalCallValueLst.addlast(a);
  
  return;
}
