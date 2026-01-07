/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : Neumann_discretize.cpp
 *  Date     : 2002/03/28
 *  Modified : 
 *  
 *  Purpose  :
 *  
 */

#include "feelfuncs.hpp"

#include "Neumann.hpp"
#include "BoundaryGalerkinMethod.hpp"

#include "IntegrandSet.hpp"
#include "Quadrature.hpp"
#include "Variable.hpp"

#include "DiscretizedComponent.hpp"
#include "EcalInfo.hpp"

#include "TermConvert.hpp"

void Neumann::ApplyGalerkinMethod(void)
{
  BoundaryGalerkinMethod *bgPtr;

  // unknown, test func variable pointer list
  listIterator<Variable *>itrUN(unknownVarPtrLst);    // SNsolve_IG_N.cpp
  listIterator<string    >itrTS(testfuncSymbolLst);   // SNsolve_IG_N.cpp

  // Quadrature is only one for boundary integration

  //  bIntegrandSetPtr->print(cerr) ;

  // Neumann data check
  //  print(cerr);

  // Replace Neumann data for boundary temporary variable

  // modify bIntegrandSetPtr
  TermConvert tc;

  listIterator <StrStrPair *>itrssp(neumannPairDataPtrLst);
  for(itrssp.init();!itrssp;++itrssp) {
    char buf[MAX_EXPRPRINT_BUF];
    sprintf(buf,"(%s)%c",(char *)(itrssp()->GetSecond()),'\0');
    tc.storeConvertPair( itrssp()->GetFirst(), buf );
  }

  BoundaryIntegrandSet *newBisetPtr =
    bIntegrandSetPtr->GetNewByTC( tc );
  listIterator <Variable *>itrNV(varPtrLst);
  for(itrNV.init(); !itrNV ; ++itrNV) {
    newBisetPtr->AddVariablePtr( itrNV() );
  }

  bgPtr = new BoundaryGalerkinMethod;

  bgPtr->SetNumberOfUnknowns       ( unknowns             );
  bgPtr->SetBoundaryIntegrandSetPtr( newBisetPtr          );
  bgPtr->SetParametricElementPtr   ( parametricElementPtr );

  if(nxFlag==YES) { bgPtr->UseNX(); }
  if(nyFlag==YES) { bgPtr->UseNY(); }
  if(nzFlag==YES) { bgPtr->UseNZ(); }
    

  // unknown Variable pointer
  for(itrUN.init(); !itrUN; ++itrUN) {
    bgPtr->AddUnknownVariablePtr( itrUN() );
  }

  // test func str
  for(itrTS.init(); !itrTS; ++itrTS) {
    bgPtr->AddTestfuncStr( itrTS() );
  }

  // Get Discretized component
  dcPtr = bgPtr->Discretize();


  dcPtr->SetNumbers(solveNo, ncondNo);
    
  // destructor for BoundaryGalerkinMethod
  bgPtr->~BoundaryGalerkinMethod();

  // check writes

  //  cerr << "#######################################\n";
  //  cerr << "## SolveElement::ApplyGalerkinMethod ##\n";
  //  cerr << "#######################################\n";
  //  cerr << "number of quads = " << quadratures << endl;
  //  listIterator <Quadrature *>itrQ(quadraturePtrLst);
  //  int j = 1;
  //  for(itrQ.init();!itrQ;++itrQ) {
  //    cerr << "No." << j << " : " << itrQ()->GetName() << endl;
  //    j++;
  //  }
  //  cerr << endl;

  // integrand set
  //  for(itrIS.init(); !itrIS ; ++itrIS ) {
  //    itrIS()->print(cerr);
  //  }
  //  cerr << "#######################################\n";

  return;
}

void Neumann::GenerateEcalInfo()    // boundary
{
  ecalInfoPtr = dcPtr
    ->GenerateBoundaryEcalInfo(spaceDim, 
			       parametricElementPtr,
			       bIntegrandSetPtr      );

  ecalInfoPtr->SumUpIntegrandTerm( ecalIntegrandTermLst );

  // set UseX,UseY,UseZ etc.  ( It is unnecessary, because done in
  // SNsolveNeumannPair_InfoGenerate.cpp
  if(ecalInfoPtr->IsUseX())  { UseX(); }
  if(ecalInfoPtr->IsUseY())  { UseY(); }
  if(ecalInfoPtr->IsUseZ())  { UseZ(); }
  if(ecalInfoPtr->IsUseNX()) { UseNX(); }
  if(ecalInfoPtr->IsUseNY()) { UseNY(); }
  if(ecalInfoPtr->IsUseNZ()) { UseNZ(); }

  return;
}

void Neumann::GenerateEsetInfo()
{
  // reason of sending 'this' is the vertex coordinate
  // index depends on the total combination of elements.
  // necessary to use GetNodePatternForEcal...
  esetInfoPtr=dcPtr
    ->GenerateBoundaryEsetInfo(this,parametricElementPtr);

  return;
}
