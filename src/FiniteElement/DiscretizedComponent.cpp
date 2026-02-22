/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : DiscretizedComponent.cpp
 *  Date     : 2002/02/12
 *  Modified : 
 *  
 *  Purpose  : constructor/destructor
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

#include "string.hpp"
#include "feeldef.hpp"
#include "DiscretizedComponent.hpp"

#include "TermConvert.hpp"

DiscretizedComponent::DiscretizedComponent(int n, int m)
{
  assert(n > 0);
  assert(m > 0);

  rows    = n;
  columns = m;

  assert(n==m);   // currently, this is necessary (020409)

  elementStiffMatPtr = new matrix <string>(n,m);
  sparseFlagMatPtr   = new matrix <int>   (n,m);
  rhsVecPtr          = new vector <string>(n);
  nullFlagRHSVecPtr  = new vector <int>(n);

  regionalIntegrationFlag = NO;
  boundaryIntegrationFlag = NO;
  solveNo = 0;
  solveElementNo = 0;
  quadNo = 0;
  ncondNo = 0;
  elementType = 0;

  matrixNonZero  = 0;
  
  parametricElemPtr = 0;

  return;
}

DiscretizedComponent::~DiscretizedComponent()
{
  delete elementStiffMatPtr;
  delete sparseFlagMatPtr;
  delete rhsVecPtr;
  delete nullFlagRHSVecPtr;

  elementStiffMatPtr   = nullptr;
  sparseFlagMatPtr     = nullptr;
  rhsVecPtr            = nullptr;
  nullFlagRHSVecPtr    = nullptr;

  return;
}

void DiscretizedComponent::SetNumbers(int sNo, int seNo, int qNo)
{
  solveNo = sNo;
  solveElementNo = seNo;
  quadNo = qNo;

  return;
}

void DiscretizedComponent::SetNumbers(int sNo, int nNo)
{
  solveNo = sNo;
  ncondNo = nNo;
  
  return;
}

void DiscretizedComponent::SetCoefficient(int i,int j,const char *fval)
{
  assert(i < rows);
  assert(j < columns);

  //  cerr << "i=" << i << "   j=" << j << "  fval=" << fval << endl; //oimo
  //  cerr << "rows="<< rows << "  columns="<<columns << endl;
  //  cerr << "TEST WRT " << elementStiffMatPtr->val(i,j)<< endl;

  elementStiffMatPtr->val(i,j) = fval;

  //  cerr << "FLAG SET\n"; // oimo
  if(*fval == '0' && *(fval+1) == '\0') {
    sparseFlagMatPtr->val(i,j) = 0;
  }
  else {
    sparseFlagMatPtr->val(i,j) = 1;
    matrixNonZero++;
  }

  //  cerr << "GOTO RET\n"; // oimo
  return;
}

void DiscretizedComponent::SetRHS(int i, const char *fval)
{
  (*rhsVecPtr)[i] = fval;

  if(*fval == '0' && *(fval+1) == '\0') {
    (*nullFlagRHSVecPtr)[i] = YES;
  }
  else {
    (*nullFlagRHSVecPtr)[i] = NO;
  }

  return;
}

// this pointer is used in ecal generator routine
void DiscretizedComponent::SetParametricElementPtr(Element *ptr)
{
  parametricElemPtr = ptr;
  return;
}

const char *DiscretizedComponent::GetElementMatIJ(int n,int m)
{
  assert(0< n && n <= rows );
  assert(0< m && m <= columns );

  return (const char *)(elementStiffMatPtr->val(n-1,m-1));
}

const char *DiscretizedComponent::GetElementLoadI(int n)
{
  assert(0< n && n <= rows );
  return (const char *)((*rhsVecPtr)[n-1]);
}

int DiscretizedComponent::IsZeroMatCoeff(int n,int m)
{
  if(sparseFlagMatPtr->val(n-1,m-1) == 1) {
    return(NO);
  }
  return(YES);
}

int DiscretizedComponent::IsZeroRHSVec(int n)
{
  if( (*nullFlagRHSVecPtr)[n-1] == YES) {
    return (YES);
  }
  return(NO);
}


void DiscretizedComponent::print(std::ostream &ost)
{
  ost << "DiscretizedComponent  ("<<rows <<"," << columns<<")" << std::endl;

  ost << "----------------------------------------------------" << std::endl;  
  for(int i=0;i<rows;i++) {
    for(int j=0;j<columns;j++) {

      if(sparseFlagMatPtr->val(i,j) == 1) {
	ost << "[" << i+1 << "," << j+1 << "] ";
      }
      else {
	ost << "(" << i+1 << "," << j+1 << ") ";
      }
      ost << elementStiffMatPtr->val(i,j) << std::endl;
    }
    ost << "----------------------------------------------------" << std::endl;  
    ost << "RHS[" << i+1 << "] " << (*rhsVecPtr)[i] << std::endl;
    ost << "----------------------------------------------------" << std::endl;  
    ost << "----------------------------------------------------" << std::endl;  
  }



  ost << "----------------------------------------------------" << std::endl;  
  ost << " IDENTIFIERS"<<std::endl;
  ost << "----------------------------------------------------" << std::endl;  

  listIterator <string>itrS(identifierLst);
  for(itrS.init(); !itrS; ++itrS){
    ost << "  {" << itrS() << "}" << std::endl;
  }


  ost << "----------------------------------------------------" << std::endl;  
  ost << " ELEMENTS"<<std::endl;
  ost << "----------------------------------------------------" << std::endl;  

  listIterator <Element *>itrE(elementPtrLst);
  for(itrE.init(); !itrE; ++itrE) {
    ost << "Element " << itrE()->GetName() << std::endl;
  }

  
  return;
}

//for ecal family
void DiscretizedComponent::SetIdentifierList(TermConvert *tcPtr)
{
  tcPtr->GetConvertedIdentifierInReverseList(identifierLst);
  return;
}

void DiscretizedComponent::SetElementPtrList(TermConvert *tcPtr)
{
  tcPtr->GetConvertedElementPtrList(elementPtrLst);
  return;
}

int DiscretizedComponent::IsUsedIntegrandTerm(string &term)
{
  if(identifierLst.includes(term)) {
    return(YES);
  }
  return(NO);
}

