/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SolveElement_discretize.cpp
 *  Date     : 2002/02/07
 *  Modified : 
 *  
 *  Purpose  : ApplyGerlerkinMethod()
 *              constuct discretizedCompPtrLst
 *  
 *             SolveElement::GenerateEcalInfo  called from discretizedSolve.cpp
 *             SolveElement::GenerateEsetInfo  called from discretizedSolve.cpp
 *
 */

#include "SolveElement.hpp"
#include "GalerkinMethod.hpp"

#include "IntegrandSet.hpp"
#include "Quadrature.hpp"
#include "Variable.hpp"

#include "DiscretizedComponent.hpp"
#include "EcalInfo.hpp"

void SolveElement::ApplyGalerkinMethod(void)
{
  GalerkinMethod *gPtr;

  // unknown, test func variable pointer list
  listIterator<Variable *>itrUN(unknownVarPtrLst);
  listIterator<string    >itrTS(testfuncSymbolLst);

  // For each Quadrature....
  listIterator <IntegrandSet *>itrIS(integrandSetLst);
  int quadNo = 0;
  for(itrIS.init(); !itrIS ; ++itrIS ) {

    quadNo++;
    gPtr = new GalerkinMethod;

    gPtr->SetNumberOfUnknowns(unknowns);
    gPtr->SetIntegrandSetPtr( itrIS() );
    gPtr->SetParametricElementPtr( parametricElementPtr );

    // unknown Variable pointer    
    for(itrUN.init(); !itrUN; ++itrUN) {
      gPtr->AddUnknownVariablePtr( itrUN() );
    }

    // test func str
    for(itrTS.init(); !itrTS; ++itrTS) {
      gPtr->AddTestfuncStr( itrTS() );
    }

    DiscretizedComponent *dcPtr;
    dcPtr = gPtr->Discretize();

    dcPtr->SetNumbers(solveNo,elemNo,quadNo);
    
    discretizedCompPtrLst.addlast(dcPtr);   // 

    gPtr->~GalerkinMethod();
  }

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


void SolveElement::GenerateEcalInfo()
{
  listIterator<DiscretizedComponent *>itrDC(discretizedCompPtrLst);
  listIterator <IntegrandSet *>itrIS(integrandSetLst);

  itrIS.init();
  for(itrDC.init(); !itrDC; ++itrDC ) {
    
    EcalInfo *eiPtr;

    eiPtr = itrDC()->GenerateEcalInfo(spaceDim, parametricElementPtr ,itrIS());
    
    ecalInfoPtrLst.addlast(eiPtr);   // 

    eiPtr->SumUpIntegrandTerm( ecalIntegrandTermLst );

    ++itrIS;
  }
  return;
}


void SolveElement::GenerateEsetInfo()
{
  listIterator<DiscretizedComponent *>itrDC(discretizedCompPtrLst);

  for(itrDC.init(); !itrDC; ++itrDC ) {
    
    EsetInfo *esetInfoPtr;

    // reason of sending 'this' also is the vertex coordinate
    // index depends on the total combination of elements.
    // necessary to use GetNodePatternForEcal...
    esetInfoPtr=itrDC()->GenerateEsetInfo(this,parametricElementPtr);
    
    esetInfoPtrLst.addlast(esetInfoPtr);   // 
  }
  return;
}
