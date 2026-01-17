/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNsolveWeq_Infogenerate.cpp
 *  Date     : 2002/01/31
 *  Modified : 
 *  
 *  Purpose  : making SolveElement, NeumannData class
 *  
 */

#include "SNsolveWeq.hpp"

class SolveElement;

void SNsolveWeq::AddVariablePtr_Regional(SolveElement *sePtr,
					 list <string> &testFuncLst)
{
  leftHandSideWeqTermsPtr->
    AddVariablePtr_Regional( sePtr, testFuncLst);

  rightHandSideWeqTermsPtr->
    AddVariablePtr_Regional( sePtr, testFuncLst);

  return;
}

void SNsolveWeq::ListUpQuadrature_Regional(list <string> &quadNameLst)
{
  leftHandSideWeqTermsPtr ->ListUpQuadrature_Regional(quadNameLst);
  rightHandSideWeqTermsPtr->ListUpQuadrature_Regional(quadNameLst);

  return;
}

void SNsolveWeq::AddVariablePtr_Boundary(Neumann *nPtr,
					 list <string> &testFuncLst,
					 list <string> &nTVarLst)
{
  leftHandSideWeqTermsPtr->
    AddVariablePtr_Boundary( nPtr, testFuncLst,nTVarLst);

  rightHandSideWeqTermsPtr->
    AddVariablePtr_Boundary( nPtr, testFuncLst,nTVarLst);

  return;
}

