/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNsolveInfoGenerate_Neumann.cpp
 *  Date     : 2002/02/05
 *  Modified : 
 *  
 *  Purpose  :
 *  
 */

#include "SNsolve.hpp"
#include "SNname.hpp"

#include "Object.hpp"
#include "feelfuncs.hpp"

#include "Solve.hpp"
#include "Variable.hpp"
#include "Neumann.hpp"

void SNsolve::MakeNeumannDataPtr(Solve *solvePtr,int sno)
{
  int ncond_no;

  ncond_no = 0;

  listIterator <SNsolveNeumann *>itrN(ncondLst);
  listIterator <SNsolveWeq *>itrWQ(weqLst);
  // make test function symbol list

  SNname *snnPtr;
  string testFuncVar;
  list <string>testFuncLst;
  for(int i=0;i<testFunctionIdentifierList->GetNumberOfElements();i++) {
    snnPtr =(*testFunctionIdentifierList)[i];
    testFuncVar = snnPtr->GetName();
    testFuncLst.add(testFuncVar);
  }

  // make neumann temporary variable symbol list
  string neumannTempVar;
  list <string>neumannTVarLst;
  for(itrN.init(); !itrN; ++itrN) {
    itrN()->AddTVarStrToList( neumannTVarLst );
  }

  // Make Boundary IntegrandSet
  BoundaryIntegrandSet *bisetPtr;
  bisetPtr = GetBoundaryIntegrandSetPtr();

  for(itrN.init(); !itrN ; ++itrN ) {
    Neumann *nPtr;

    nPtr = new Neumann;
    solvePtr -> AddNeumannDataPtr( nPtr );
    
    // set numbers
    nPtr -> SetSolveNo( sno );

    ncond_no++;
    nPtr -> SetNcondNo( ncond_no );

    nPtr -> SetSpaceDim( solvePtr->GetSpaceDim() );

    // set Boundary Integrand
    nPtr -> SetBoundaryIntegrandSetPtr( bisetPtr );

    // Add Variables in Boundary integrand
    // make neumann temporary variable list
    for(itrWQ.init(); !itrWQ ; ++itrWQ) {
      itrWQ()->AddVariablePtr_Boundary( nPtr, testFuncLst ,neumannTVarLst);
    }

    // Add Variables in Neumann data expression
    itrN()->AddVariablePtr_Neumann(nPtr);


    // For Discretization  (BoundaryGalerkin)

    // 1)Make unknown variable list
    Variable *varPtr;
    for(int i=0;i<unknownIdentifierList->GetNumberOfElements();i++) {
      snnPtr = (*unknownIdentifierList)[i];
      varPtr = feelfemobj.GetVariablePtrWithName(snnPtr->GetName());

      nPtr->AddUnknownVariablePtr( varPtr );
    }
    // CURRENTLY, NONLINER NEUMANN CONDITION IS NOT SUPPORTED
    // if nonlinear, unknown variables are also referenced variables
    //    if(nonlinearFlag == YES) {
    //      sePtr->AddVariablePtr_nonlinearCase( varPtr );
    //    }

    // Make testFuncSymbolLst (in addition)
    // string testFuncVar;  (defined already,use same one)

    for(int i=0;i<testFunctionIdentifierList->GetNumberOfElements();i++) {
      snnPtr =(*testFunctionIdentifierList)[i];
      testFuncVar = snnPtr->GetName();
      nPtr->AddTestfuncStr( testFuncVar );
    }

    // set parametric element
    nPtr->SetParametricElement( parametricName );

    // Set neumann data
    itrN()->AddNeumannDataPairs( nPtr );

  }

  return;
}
