/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : IntegrandSet.cpp
 *  Date     : 2002/02/08
 *  Modified : 
 *  
 *  Purpose  :
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

#include <cassert>
#include <iostream>

#include "feeldef.hpp"

#include "IntegrandSet.hpp"
#include "Variable.hpp"
#include "Quadrature.hpp"
#include "list.hpp"
#include "string.hpp"


IntegrandSet::IntegrandSet()
{
  // constructor
  equations = 0;

  useX = NO;
  useY = NO;
  useZ = NO;

  return;
}

IntegrandSet::~IntegrandSet()
{
  // destructor   do nothing now for IntegrandSet destructor
  return;
}

void IntegrandSet::SetEquations(int n)
{
  equations = n;
  return;
}

void IntegrandSet::SetQuadraturePtr(Quadrature *ptr)
{
  quadPtr = ptr;
  return;
}

void IntegrandSet::SetIntegrandStr(string &integrandStr)
{
  integrandLst.addlast(integrandStr);
  return;
}


void IntegrandSet::SetUseX()
{
  useX = YES;
  return;
}
void IntegrandSet::SetUseY()
{
  useY = YES;
  return;
}
void IntegrandSet::SetUseZ()
{
  useZ = YES;
  return;
}

int IntegrandSet::GetUseX()
{
  return useX;
}

int IntegrandSet::GetUseY()
{
  return useY;
}

int IntegrandSet::GetUseZ()
{
  return useZ;
}


void IntegrandSet::AddVariablePtr( Variable *ptr)
{
  if(varPtrLst.includes(ptr)) return;

  varPtrLst.addlast(ptr);

  return;
}

Quadrature *IntegrandSet::GetQuadraturePtr(void)
{
  if(quadPtr == 0) {
	  std::cerr << "IntegrandSet::quadPtr == 0" << std::endl;
    assert(1==0);
  }
  return(quadPtr);
}  

void IntegrandSet::print(std::ostream &ost)
{
  ost << "--------------------------------" << std::endl;
  ost << "IntegrandSet :: equations = " << equations << std::endl;
  ost << "Quadrature method           " << quadPtr->GetName() << std::endl;

  listIterator<string> itr(integrandLst);
  int no=1;
  for(itr.init(); !itr ; ++itr) {
    ost << "No."<<no<< "  "<< itr() << std::endl;
    no++;
  }

  ost << "Variable : ";
  listIterator<Variable *>itrV(varPtrLst);
  for(itrV.init(); !itrV ; ++itrV) {
    ost << " " << itrV()->GetName();
  }
  ost << std::endl;

  ost << "--------------------------------" << std::endl;

  return;
}
