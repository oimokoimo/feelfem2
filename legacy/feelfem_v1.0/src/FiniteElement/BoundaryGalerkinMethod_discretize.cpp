/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : BoundaryGalerkinMethod_discretize.cpp
 *  Date     : 2002/03/29 (copy of GalerkinMethod_discretize.cpp)
 *  Modified : 
 *  
 *  Purpose  : Discretization
 *  
 */

#include <assert.h>
#include <iostream.h>

#include "BoundaryGalerkinMethod.hpp"
#include "DiscretizedComponent.hpp"
#include "IntegrandSet.hpp"

#include "Variable.hpp"
#include "Element.hpp"

#include "feeldef.hpp"
#include "feelfuncs.hpp"
#include "Object.hpp"

#include "TermConvert.hpp"

DiscretizedComponent *BoundaryGalerkinMethod::Discretize(void)
{
  CalculateTotalDOF();  // set totalDOF

  DiscretizedComponent *dcPtr = new DiscretizedComponent(totalDOF,
							 totalDOF );

  dcPtr->SetParametricElementPtr(parametricElemPtr);  // for ecal 020226

  Make_ElementInfo();   // make element function list (B)
  
  //  Make_VariableInfo();  // basic information for termconvert

  Make_TermConvert();   // Term convert for Variables

  ApplyGalerkin( dcPtr );


  // check write
  //  for(int i=0;i<elements;i++) {
  //    cerr << "ELEMENT No." << i << "  " << elementDOF[i] << endl;
  //  }

  tcPtr->~TermConvert(); // delete 
  
  VarPtr_ElementPtr_TC_init();  //

  //  abortExit(" var ptr element ptr tc init finish");

  //  dcPtr->print(cerr);

  return(dcPtr);
}


void BoundaryGalerkinMethod::Make_ElementInfo(void)
{
  // Element for test function  // this is pure Galerkin NOT Petrov-Galerkin
  listIterator <Variable *>itrUN(unknownVarPtrLst);
  for(itrUN.init(); !itrUN ; ++itrUN ) {
    Element *ePtr = itrUN()->GetElementPtr();
    assert(ePtr != 0);
    AddUniqElementPtr( ePtr );                   // region element ptr
  }

  // varialbes in integrands
  listIterator <Variable *>itrV(weakIntegrandPtr->varPtrLst);
  for(itrV.init(); !itrV; ++itrV ) {
    if(itrV()->GetType() == VAR_FEM ||
       itrV()->GetType() == VAR_VFEM   ) {
      Element *ePtr = itrV()->GetElementPtr();
      assert(ePtr != 0);
      AddUniqElementPtr( ePtr );                 // region element ptr
    }
  }

  assert(elements>0);

  elementDOF = new int[elements];            // assign memory 

  listIterator <Element *>itrE(elementPtrLst);
  int i = 0;
  for(itrE.init(); !itrE ; ++ itrE ) {
    
    // boundary element
    Element *bdElementPtr;
    bdElementPtr = itrE()->AcquireBoundaryElementPtr();

    *(elementDOF+i) = bdElementPtr->GetElementFreedom();
    i++;
  }

  assert(i == elementPtrLst.getNumberOfElements());

  return;
}

void BoundaryGalerkinMethod::AddUniqElementPtr( Element *ePtr)
{
  if(elementPtrLst.includes(ePtr)) return;

  elements++;
  elementPtrLst.addlast(ePtr);

  return;
}

// not use
// void BoundaryGalerkinMethod::Make_VariableInfo(void)
// {
//   variables = weakIntegrandPtr->varPtrLst.getNumberOfElements();
// 
//   assert(variables > 0);
// 
//   elementNo     = new int[variables];
//   degOfFreedom  = new int[variables];
//   startingSblNo = new int[variables];
//   varType       = new int[variables];
//   ewiseType     = new int[variables];
// 
//   for(int i=0;i<variables;i++) {
//     elementNo[i]     = -1;
//     degOfFreedom[i]  = 0;
//     startingSblNo[i] = 0;
//     varType[i]       = -1;
//     ewiseType[i]     = 0;
//   }
// 
//   int no = 0;
//   int startingNo = 1;
//   
//   Element *ePtr;
// 
//   listIterator <Variable *>itrV(weakIntegrandPtr->varPtrLst);
//   for(itrV.init(); !itrV; ++itrV ){
// 
//     //    cerr << "name = " << itrV()->GetName() << endl;
// 
//     varType[no] = itrV()->GetType();
//     switch(itrV()->GetType()) {
// 
//     case VAR_EWISE_A:
//       if(itrV()->GetEwiseType() == EWISE_TYPE_GAUSSPOINT) {
// 
// 	ewiseType[no] = EWISE_TYPE_GAUSSPOINT;
// 	degOfFreedom[no] = 1;                     // value at quadrature point
// 	startingSblNo[no] = startingNo;
// 	startingNo += degOfFreedom[no];
// 	break;
//       }
//       else {
// 	ePtr = itrV()->GetElementPtr();
// 
// 	elementNo[no] = elementPtrLst.getPosition(ePtr);
// 
// 	ewiseType[no] = EWISE_TYPE_INTERPOLATION;
// 	degOfFreedom[no] = ePtr->GetElementFreedom();
// 	startingSblNo[no] = startingNo;
// 	startingNo += degOfFreedom[no];
// 	break;
//       }
// 
//     case VAR_FEM:
//     case VAR_VFEM:
// 	ePtr = itrV()->GetElementPtr();
// 
// 	elementNo[no] = elementPtrLst.getPosition(ePtr);
// 
// 	degOfFreedom[no]   = ePtr->GetElementFreedom();
// 	startingSblNo[no]  = startingNo;
// 	startingNo        += degOfFreedom[no];
// 
//       break;
//       
//       // scalar variables
//     case VAR_EWISE:
//     case VAR_DOUBLE:
//     case VAR_INT:
//     case VAR_CONST:
//       degOfFreedom[no] = 1;
//       //elementNo[no]  = -1;   // already initialized by -1
//       startingSblNo[no] = startingNo;
//       startingNo += degOfFreedom[no];
//       break;
//     }
//     no++;
//   }
// 
//   //  for(int i=0;i<variables;i++) {
//   //    cerr << "No."<< i+1 << " degfre=" << degOfFreedom[i] <<" start="
//   //	 << startingSblNo[i] << " type=" << varType[i] << endl;
//   //  }
// 
//   return;
// }

void BoundaryGalerkinMethod::Make_TermConvert(void)  // for boundary
{
  tcPtr = new TermConvert;

  assert(tcPtr != 0);

  listIterator <Variable *>itrV(weakIntegrandPtr->varPtrLst);

  // for normal component
  if(nxFlag == YES) {
    tcPtr->UseNX();
  }
  if(nyFlag == YES) {
    tcPtr->UseNY();
  }
  if(nzFlag == YES) {
    tcPtr->UseNZ();
  }
  tcPtr->SetNormalComponent_boundary();

  // for variables
  for(itrV.init(); !itrV; ++itrV ){
    tcPtr->AddVariableBoundary(itrV());
  }

  //  unknown variable must be added if it is not included
  listIterator <Variable *>itrUV(unknownVarPtrLst);
  for(itrUV.init(); !itrUV; ++itrUV) {
    if( weakIntegrandPtr->varPtrLst.includes( itrUV() )) continue;
    tcPtr->AddVariableBoundary(itrUV());
  }

  // reverse TermConvert
  tcPtr->MakeReverseTC_boundary();

  return;
}

void BoundaryGalerkinMethod::VarPtr_ElementPtr_TC_init()
{
  listIterator <Variable *>itrV(weakIntegrandPtr->varPtrLst);

  for(itrV.init(); !itrV; ++itrV ){
    itrV()->initWorkTC();
    
    if(itrV()->IsElementPtrReady() ) {
      Element *ePtr = itrV()->GetElementPtr();
      ePtr->initWorkTC();
    }
  }
    
  // UNKNOWNk variable must be added if it is not included
  listIterator <Variable *>itrUV(unknownVarPtrLst);
  for(itrUV.init(); !itrUV; ++itrUV) {
    itrUV()->initWorkTC();

    Element *ePtr = itrUV()->GetElementPtr();
    ePtr->initWorkTC();
  }
  return;
}

void BoundaryGalerkinMethod::CalculateTotalDOF()  // boundary
{
  // calculate total freedom for element stiffeness
  listIterator <Variable *>itrUNV(unknownVarPtrLst);

  totalDOF = 0;
  for(itrUNV.init();!itrUNV; ++itrUNV) {

    // calculate element degree of freedom
    Element *ePtr  = itrUNV()->GetElementPtr();
    Element *bePtr = ePtr->AcquireBoundaryElementPtr();

    totalDOF += bePtr->GetElementFreedom();
  }

  return;
}


// apply galerkin method for boundary
void BoundaryGalerkinMethod::ApplyGalerkin(DiscretizedComponent *dcPtr)
{
  listIterator <string>itrWeq(weakIntegrandPtr->integrandLst);
  listIterator <string>itrTfc(testfuncStrLst);
  listIterator <Variable *>itrUNV(unknownVarPtrLst);

  // totalDOF is already calculated  

  assert(totalDOF > 0);
  int *coeffSblNoVec = new int [totalDOF];
  int iptr = 0;
  for(itrUNV.init();!itrUNV; ++itrUNV) {

    int stno      = itrUNV()->GetSblNo();
    Element *ePtr = itrUNV()->GetElementPtr();
    // oimo koimo 020405
    //    int dof       = ePtr->GetElementFreedom();
    Element *bePtr = ePtr ->AcquireBoundaryElementPtr();
    int dof        = bePtr->GetElementFreedom();

    for(int i=0;i<dof;i++) {
      coeffSblNoVec[iptr] = stno + i;
      iptr++;
    }
  }

  itrTfc.init();
  itrUNV.init();

  int freedomAdd = 0;
  for(itrWeq.init(); !itrWeq ; ++itrWeq) {
    
    // boundary
    Element *ePtr  = itrUNV()->GetElementPtr();
    Element *bePtr = ePtr->AcquireBoundaryElementPtr();

    // for each integrand,

    GalerkinTestFunction(dcPtr,itrWeq(),itrTfc(),ePtr,bePtr,
			 freedomAdd,coeffSblNoVec);

    // boundary
    freedomAdd += bePtr->GetElementFreedom();
    ++itrTfc;
    ++itrUNV;
  }

  delete []coeffSblNoVec;

  return;
}

void BoundaryGalerkinMethod::GalerkinTestFunction(DiscretizedComponent *dcPtr,
					  string weqIntegrandStr,
					  string testFunctionStr,
					  Element *ePtr         ,
					  Element *bePtr        ,
					  int      freedomAdd   ,
					  int     *coeffSblNoVec )
  // coeffSblNoVec has array for unknowns symbol number
  // _m2 _m3 _m4 -> 2 3 4
{
  int freedom = bePtr->GetElementFreedom();
  void integrandDerivative(char *,int , char *, int);


  for(int i=0;i<freedom;i++) {
    
    int testFuncNo = ePtr->GetEstNo()+i;   // use Regional

    //    tcPtr->print(cerr);

    tcPtr->SetTestFunctionSymbol_boundary( testFunctionStr, testFuncNo );

    char *ret = tcPtr->convertExpressionString( weqIntegrandStr );

    for(int j=0;j<totalDOF;j++) {

      void integrandEval(char *);   // ginac/integrandEval.cpp
      char cformula[MAX_FORMULA_BUF];  // = 8192

      integrandDerivative( ret ,coeffSblNoVec[j], cformula,MAX_FORMULA_BUF);

      char *rev_ret = tcPtr->ReverseConvertExpressionString( cformula );

      dcPtr->SetCoefficient(i+freedomAdd,j,rev_ret);
    }
    
    char cformula[MAX_FORMULA_BUF];
    void GetRightHandSide(char *, int , int * , char *, int);

    GetRightHandSide(ret,totalDOF,coeffSblNoVec,cformula,MAX_FORMULA_BUF);

    char *rev_ret = tcPtr->ReverseConvertExpressionString(cformula);

    dcPtr->SetRHS( i+freedomAdd, rev_ret);
    
  }

  // 2002-02-21  make identifier list  (for ecal generation)
  //  cerr << "goto dcPtr->setIdentifierList\n";  // oimo

  dcPtr->SetIdentifierList(tcPtr);

  //  cerr << "goto dcPtr->setElementPtrList\n";  // oimo
  dcPtr->SetElementPtrList(tcPtr);

  //  discretized component check write
  //  dcPtr->print(cerr);

  return;
}
