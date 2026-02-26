/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : Assign_EwiseQuad.cpp
 *  Date     : 2002/08/01
 *  Modified : 2002/11/02 (Modified for Integral)
 *  
 *  Purpose  : assign ewise quad related routines
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

#include "feeldef.hpp"
#include "Object.hpp"
#include "Configure.hpp"         // for default quadrature for integral
#include "GeometryObject.hpp"
#include "feelfuncs.hpp"
#include "Assign.hpp"

#include "EwiseQuadTC.hpp"
#include "EwiseQuadEcalInfo.hpp"
#include "Quadrature.hpp"
#include "Variable.hpp"
#include "ElementNodePattern.hpp"


void Assign::SetQuadraturePtr(Quadrature *qPtr)
{
  ewqQuadPtr = qPtr;
  return;
}

Quadrature *Assign::GetQuadraturePtr(void)
{
  return(ewqQuadPtr);
}

void Assign::EwiseQuadDiscretize(void)
{
  //  set parametric element ptr and ewqQuadPtr, they are used in 
  //  EwiseQuadIG_TermConvert();             // includes make EcalInfo
  //  EwiseQuadIG_ElementNodePattern();
  int etype;

  // determin etype
  switch( leftVarAssignType) {
  case AS_VAR_TYPE_EWISE_G:
    etype = leftVarPtr->GetEtype();
    ewqQuadPtr  = leftVarPtr->GetQuadraturePtr();
    break;

  case AS_VAR_TYPE_DOUBLE_INTEGRAL:
    etype = feelfemgeomobj.GetRegionalEtype();
    ewqQuadPtr  = GetQuadraturePtr();
    if(ewqQuadPtr == 0) {
      ewqQuadPtr = feelfemconf.GetDefaultQuadraturePtrByEtype(etype);
    }
    break;

    
  default:
    assert(1==0);
  }


  parametricElemPtr = feelfemobj.GetParametricElementPtrEwByEtype(etype);

  assert(ewqQuadPtr != 0);
  assert(parametricElemPtr != 0);

  EwiseQuadIG_TermConvert();             // includes make EcalInfo
  EwiseQuadIG_ElementNodePattern();

  return;
}

void Assign::EwiseQuadIG_TermConvert(void)
{
  void ewiseQuadEval(char *,char *,int);   // ginac/integrandEval.cpp
  EwiseQuadTC tc;

  listIterator <Variable *>itrV(varPtrLst);
  for(itrV.init(); !itrV ; ++itrV) {
    
    itrV()->initWorkTC();  // no initialize for element pointer (only for var)
    tc.AddVariable( itrV() );
    
  }
  tc.MakeReverseTC();

  // User Function symbols
  tc.AddUserFunctionSymbol();

  
  char *ret = tc.convertExpressionString( expr );
  
  char cformula[MAX_FORMULA_BUF];
  
  ewiseQuadEval( ret , cformula , MAX_FORMULA_BUF );

  // Set formula in Assign class
  ret = tc.ReverseConvertExpressionString( cformula );

  expr = ret; // converion

  
  // EcalInfo uses TermConvert tc

  // Make EwiseQuadEcalInfo class
  ewqEcalInfoPtr = new EwiseQuadEcalInfo();


  // integral (use determinant)
  switch(leftVarAssignType) {
  case AS_VAR_TYPE_DOUBLE_INTEGRAL:
    ewqEcalInfoPtr->AddUniqD1ElementPtrList(parametricElemPtr);
    break;

  case AS_VAR_TYPE_DOUBLE_BINTEGRAL:
    assert(1==0);  // not yet
    break;

  case AS_VAR_TYPE_EWISE_G:
    break;

  default:
    assert(1==0);
  }

  // set Quadrature ptr
  assert(ewqQuadPtr != 0);
  assert(parametricElemPtr != 0);
  ewqEcalInfoPtr->SetQuadraturePtr( ewqQuadPtr );
  ewqEcalInfoPtr->SetParametricElementPtr( parametricElemPtr);




  // variable ptr
  for(itrV.init(); !itrV ; ++itrV) {
    Variable *vPtr = itrV();
    ewqEcalInfoPtr->AddVariablePtr(vPtr);
  }
  // set identifier list
  ewqEcalInfoPtr->SetConvertedIdentifierList( tc );

  // set used user func list
  ewqEcalInfoPtr->SetConvertedUserFuncStrList( tc );

  // Generate information
  ewqEcalInfoPtr->InfoGenerate();

  // If differential is used, x,y,z use flags must be set
  if(ewqEcalInfoPtr->IsUseElementDerivative()) {

    UseDiff1st();     // only 1st order now

    switch( feelfemobj.GetSpaceDimension() ) {
    case 1:
      UseX();
      break;

    case 2:
      UseX();
      UseY();
      break;

    case 3:
      UseX();
      UseY();
      UseZ();
      break;
      
    default:
      assert(1==0);
    }
  }

  // delete TermConvert
  tc.~EwiseQuadTC();
  for(itrV.init(); !itrV ; ++itrV) {
    itrV()->initWorkTC();  // no initialize for element pointer (only for var)
  }

  // get user function information
  listIterator <string>itrfs(ewqEcalInfoPtr->GetUsedUserFuncStrList());
  for(itrfs.init(); !itrfs ; ++itrfs) {
    string nm = itrfs();
    AddUsedUserFuncSymbol( nm );
  }

  return;
}

void Assign::EwiseQuadIG_ElementNodePattern(void) 
{
  enpPtr = new ElementNodePattern();
  
  listIterator <Variable *>itrV(varPtrLst);
  for(itrV.init(); !itrV ; ++itrV ) {
    enpPtr->AddNodeByVariable(itrV());
  }

  enpPtr->AddNodeByElement( parametricElemPtr );

  enpPtr->MakePatternEwiseQuad();
 
  return;
}

int Assign::GetNodesEwiseQuad(void)
{
  return(enpPtr->GetNodes());
}


int Assign::GetNodesForElement(Element *ePtr)
{
  return(ePtr->GetElementFreedom());
}

int *Assign::GetNodeInfoElement(Element *ePtr)
{
  int *ret;
  ret = enpPtr->MakeNodeInfoForFEMvar( ePtr );
  return(ret);
}


int Assign::GetNodesForParametric(void)
{
  int etype;

  if(leftVarAssignType == AS_VAR_TYPE_EWISE_G) {
    etype = leftVarPtr->GetEtype();
  }
  else if( leftVarAssignType == AS_VAR_TYPE_DOUBLE_INTEGRAL) {
    etype = ewqQuadPtr->GetEtype();
  }
  else {
    assert(1==0);  // BINTEGRAL
  }

  Element *ePtr = feelfemobj.GetParametricElementPtrEwByEtype(etype);

  return(ePtr->GetElementFreedom());
}


int *Assign::GetNodeInfoParametric(void)
{
  int etype;

  if(leftVarAssignType == AS_VAR_TYPE_EWISE_G) {
    etype = leftVarPtr->GetEtype();
  }
  else if( leftVarAssignType == AS_VAR_TYPE_DOUBLE_INTEGRAL) {
    etype = ewqQuadPtr->GetEtype();
  }
  else {
    assert(1==0);  // BINTEGRAL
  }

  Element *ePtr = feelfemobj.GetParametricElementPtrEwByEtype(etype);

  int *ret;
  ret = enpPtr->MakeNodeInfoForFEMvar( ePtr );
  return(ret);

}


int Assign::GetNodesForVariable(Variable *vPtr)
{
  Element *ePtr = vPtr->GetElementPtr();

  return(ePtr->GetElementFreedom());
}


int *Assign::GetNodeInfoVariable(Variable *vPtr)
{
  Element *ePtr = vPtr->GetElementPtr();

  int *ret;
  ret = enpPtr->MakeNodeInfoForFEMvar( ePtr );
  return(ret);

}
