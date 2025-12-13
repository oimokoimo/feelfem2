/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNsolve_Infogenerate_SE.cpp
 *  Date     : 2002/02/05
 *  Modified : 2002/03/27 (add boundaryIntegrand)
 *  
 *  Purpose  :
 *  
 */

#include <iostream.h>
#include <stdlib.h>     // for debug exit(1)

#include "SNsolve.hpp"
#include "SNname.hpp"

#include "Object.hpp"
#include "feelfuncs.hpp"

#include "Solve.hpp"
#include "Variable.hpp"

#include "feelfuncs.hpp"     // these 4 includes are for IntegrandSet
#include "Object.hpp"
#include "Configure.hpp"
#include "Quadrature.hpp" 

void SNsolve::MakeSolveElement(Solve *solvePtr, int solveNo, int seNo)
{
  SolveElement *sePtr;    // SUBSOLVE

  sePtr = new SolveElement;
  solvePtr -> AddSolveElementPtr( sePtr );

  // set numbers
  sePtr->SetSolveNo( solveNo  );
  sePtr->SetElemNo ( seNo     );
  sePtr->SetEtype  ( refEtype );
  sePtr->SetSpaceDim( solvePtr->GetSpaceDim() );

  sePtr->SetParametricElement( parametricName );
  
  // set Unknowns   //SUBSOLVE  generating solveElement from one solve
  Variable *varPtr;
  SNname   *snnPtr;

  for(int i=0;i<unknownIdentifierList->GetNumberOfElements();i++) {
    snnPtr = (*unknownIdentifierList)[i];
    varPtr = feelfemobj.GetVariablePtrWithName(snnPtr->GetName());

    sePtr->AddUnknownVariablePtr( varPtr );

    // if nonlinear, unknown variables are also referenced variables
    if(nonlinearFlag == YES) {
      sePtr->AddVariablePtr_nonlinearCase( varPtr );
    }
  }

  // Make testFuncSymbolLst (in addition)   (used in ApplyGalerkinMethod)
  string testFuncVar;
  for(int i=0;i<testFunctionIdentifierList->GetNumberOfElements();i++) {
    snnPtr =(*testFunctionIdentifierList)[i];
    testFuncVar = snnPtr->GetName();
    sePtr->AddTestfuncStr( testFuncVar );
  }

  // Add Variables (Regional, boundary terms are treated in Neumann)
  listIterator <SNsolveWeq *>itrWQ(weqLst);

  list <string>testFuncLst;
  for(int i=0;i<testFunctionIdentifierList->GetNumberOfElements();i++) {
    snnPtr =(*testFunctionIdentifierList)[i];
    testFuncVar = snnPtr->GetName();
    testFuncLst.add(testFuncVar);
  }
  for(itrWQ.init(); !itrWQ ; ++itrWQ) {
    itrWQ()->AddVariablePtr_Regional( sePtr, testFuncLst );
  }

  // List-up quadratures
  list <string> quadratureMethodsLst;
  for(itrWQ.init(); !itrWQ ; ++itrWQ) {
    itrWQ()->ListUpQuadrature_Regional( quadratureMethodsLst );
  }

  sePtr->SetMainQuadratureName( quadratureMethod );
  listIterator <string> itrQ(quadratureMethodsLst);
  for(itrQ.init(); !itrQ ; ++itrQ ) {
    sePtr->AddQuadratureName( itrQ() );
  }

  // Generate Regional Integrand Lst (By quadrature)
  IntegrandSet *isetPtr;
  Quadrature *qPtr;

  // main part
  string quadName=DEFAULT_STRING;
  if(quadratureMethod == DEFAULT_STRING) {
    qPtr = feelfemconf.GetDefaultQuadraturePtrByEtype( refEtype );
  }
  else {
    qPtr = feelfemobj.GetQuadraturePtrByName( quadratureMethod );
  }
  isetPtr = GetIntegrandSetPtrByQuad_Region(quadName,qPtr);
  sePtr->AddIntegrandSetPtr(isetPtr);

  for(itrQ.init(); !itrQ ; ++itrQ ) {
    quadName = itrQ();
    qPtr = feelfemobj.GetQuadraturePtrByName( quadName );
    isetPtr = GetIntegrandSetPtrByQuad_Region( itrQ(), qPtr );
    sePtr->AddIntegrandSetPtr(isetPtr);
  }

  // Generate IENP and IEDP
  sePtr->MakeElementNodePattern();
  sePtr->SetNENFRE();
  sePtr->SetIENPIEDP();

  return;
}
