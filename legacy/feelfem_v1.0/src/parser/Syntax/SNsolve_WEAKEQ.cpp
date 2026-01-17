/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNsolve_WEAKEQ.cpp
 *  Date     : 2002/01/30
 *  Modified : 2002/03/27 (add boundary part)
 *  
 *  Purpose  : processing connecting weak formulation
 *  
 *  First      GetRegionWeakEqStrByQuad   call with DEFAULT_STRING for primal 
 *  
 *  
 */

#include <stdio.h>

#include "SNsolve.hpp"
#include "SNsolveWeq.hpp"
#include "IntegrandSet.hpp"

#include "feelfuncs.hpp"    // for default boundary qPtr from regional etype
#include "Configure.hpp"

// for the main part, quadName should be DEFAULT_STRING, and
// qPtr has real Quadrature pointer

IntegrandSet *SNsolve::GetIntegrandSetPtrByQuad_Region(string quadName,
						       Quadrature *qPtr )

{
  char exprBUF[BUFSIZ];
  int  exprBUFptr;

  string weqStr;

  IntegrandSet *isetPtr = new IntegrandSet;

  isetPtr->SetEquations(weakEquations);
  isetPtr->SetQuadraturePtr( qPtr );

  // make test function string list
  SNname *snnPtr;
  string testFuncVar;
  list <string>testFuncLst;
  for(int i=0;i<testFunctionIdentifierList->GetNumberOfElements();i++) {
    snnPtr =(*testFunctionIdentifierList)[i];
    testFuncVar = snnPtr->GetName();
    testFuncLst.add(testFuncVar);
  }

  // loop for weak terms
  listIterator <SNsolveWeq *>itr(weqLst);

  for(itr.init(); !itr ; ++itr ) {
    exprBUFptr = 0;
    
    // Make expression in string form
    itr()->WriteRegionWeakEqStrByQuad(quadName,exprBUF,exprBUFptr,BUFSIZ);
    
    // Make Variable list
    itr()->MakeRegionIntegrandSetInfoByQuad(quadName, isetPtr ,testFuncLst);

    if(exprBUFptr == 0) {
       exprBUF[0] = '0';
       exprBUFptr =  1 ;
    }

    exprBUF[exprBUFptr] = '\0';
    weqStr = exprBUF;
    
    isetPtr->SetIntegrandStr( weqStr );
  }
  return(isetPtr);
}

// boundary part
BoundaryIntegrandSet *SNsolve::GetBoundaryIntegrandSetPtr(void)
{
  char exprBUF[BUFSIZ];
  int  exprBUFptr;

  string weqStr;

  BoundaryIntegrandSet *bisetPtr = new BoundaryIntegrandSet;

  bisetPtr->SetEquations(weakEquations);

  // Set Default quadrature
  Quadrature *qPtr;
  qPtr = feelfemconf.GetDefaultBoundaryQuadFromRegionEtype(refEtype);
  bisetPtr->SetQuadraturePtr( qPtr );


  // make test function string list
  SNname *snnPtr;
  string testFuncVar;
  list <string>testFuncLst;
  for(int i=0;i<testFunctionIdentifierList->GetNumberOfElements();i++) {
    snnPtr =(*testFunctionIdentifierList)[i];
    testFuncVar = snnPtr->GetName();
    testFuncLst.add(testFuncVar);
  }

  // Add Neumann temporary variable also
  listIterator <SNsolveNeumann *>itrN(ncondLst);
  for(itrN.init(); !itrN ; ++itrN) {
    itrN()->AddTVarStrToList( testFuncLst );
  }

  // loop for weak terms
  listIterator <SNsolveWeq *>itr(weqLst);
  for(itr.init(); !itr ; ++itr ) {
    exprBUFptr = 0;
    
    // Make expression in string form
    itr()->WriteBoundaryWeakEqStr(exprBUF,exprBUFptr,BUFSIZ);
    
    // Make Variable list
    itr()->MakeBoundaryIntegrandSetInfo(bisetPtr ,testFuncLst);

    if(exprBUFptr == 0) {
       exprBUF[0] = '0';
       exprBUFptr =  1 ;
    }

    exprBUF[exprBUFptr] = '\0';
    weqStr = exprBUF;
    
    bisetPtr->SetIntegrandStr( weqStr );
  }

  return(bisetPtr);
}
