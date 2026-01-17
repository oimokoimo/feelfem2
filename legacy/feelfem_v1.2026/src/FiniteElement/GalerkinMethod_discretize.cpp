/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : GalerkinMethod_discretize.cpp
 *  Date     : 2002/02/12
 *  Modified : 
 *  
 *  Purpose  : Discretization
 *  
 */
#include <iostream.h>


#include "GalerkinMethod.hpp"
#include "DiscretizedComponent.hpp"
#include "IntegrandSet.hpp"

#include "Variable.hpp"
#include "Element.hpp"

#include "feeldef.hpp"
#include "feelfuncs.hpp"
#include "Object.hpp"

#include "TermConvert.hpp"

DiscretizedComponent *GalerkinMethod::Discretize(void)
{
  CalculateTotalDOF();  // set totalDOF

  DiscretizedComponent *dcPtr = new DiscretizedComponent(totalDOF,
							 totalDOF );

  dcPtr->SetParametricElementPtr(parametricElemPtr);  // for ecal 020226

  Make_ElementInfo();   // make element function list
  
  //  Make_VariableInfo();  // basic information for termconvert

  Make_TermConvert();   // Term convert for Variables

  ApplyGalerkin( dcPtr );


  // check write
  //  for(int i=0;i<elements;i++) {
  //    cerr << "ELEMENT No." << i << "  " << elementDOF[i] << endl;
  //  }

  tcPtr->~TermConvert(); // delete 
  
  VarPtr_ElementPtr_TC_init();  //

  //  dcPtr->print(cerr);

  return(dcPtr);
}


void GalerkinMethod::Make_ElementInfo(void)
{
  // Element for test function  // this is pure Galerkin NOT Petrov-Galerkin
  listIterator <Variable *>itrUN(unknownVarPtrLst);
  for(itrUN.init(); !itrUN ; ++itrUN ) {
    Element *ePtr = itrUN()->GetElementPtr();
    assert(ePtr != 0);
    AddUniqElementPtr( ePtr );
  }
  

  // varialbes in integrands
  listIterator <Variable *>itrV(weakIntegrandPtr->varPtrLst);
  for(itrV.init(); !itrV; ++itrV ) {
    if(itrV()->GetType() == VAR_FEM ||
       itrV()->GetType() == VAR_VFEM   ) {
      Element *ePtr = itrV()->GetElementPtr();
      assert(ePtr != 0);
      AddUniqElementPtr( ePtr );
    }
  }

  assert(elements>0);

  elementDOF = new int[elements];            // assign memory 

  listIterator <Element *>itrE(elementPtrLst);
  int i = 0;
  for(itrE.init(); !itrE ; ++ itrE ) {
    *(elementDOF+i) = itrE()->GetElementFreedom();
    i++;
  }

  assert(i == elementPtrLst.getNumberOfElements());

  return;
}

void GalerkinMethod::AddUniqElementPtr( Element *ePtr)
{
  if(elementPtrLst.includes(ePtr)) return;

  elements++;
  elementPtrLst.addlast(ePtr);

  return;
}

//
void GalerkinMethod::Make_VariableInfo(void)
{
  variables = weakIntegrandPtr->varPtrLst.getNumberOfElements();

  assert(variables > 0);

  elementNo     = new int[variables];
  degOfFreedom  = new int[variables];
  startingSblNo = new int[variables];
  varType       = new int[variables];
  ewiseType     = new int[variables];

  for(int i=0;i<variables;i++) {
    elementNo[i]     = -1;
    degOfFreedom[i]  = 0;
    startingSblNo[i] = 0;
    varType[i]       = -1;
    ewiseType[i]     = 0;
  }

  int no = 0;
  int startingNo = 1;
  
  Element *ePtr;

  listIterator <Variable *>itrV(weakIntegrandPtr->varPtrLst);
  for(itrV.init(); !itrV; ++itrV ){

    varType[no] = itrV()->GetType();
    switch(itrV()->GetType()) {

    case VAR_EWISE_A:
      if(itrV()->GetEwiseType() == EWISE_TYPE_GAUSSPOINT) {

	ewiseType[no] = EWISE_TYPE_GAUSSPOINT;
	degOfFreedom[no] = 1;                     // value at quadrature point
	startingSblNo[no] = startingNo;
	startingNo += degOfFreedom[no];
	break;
      }
      else {
	ePtr = itrV()->GetElementPtr();

	elementNo[no] = elementPtrLst.getPosition(ePtr);

	ewiseType[no] = EWISE_TYPE_INTERPOLATION;
	degOfFreedom[no] = ePtr->GetElementFreedom();
	startingSblNo[no] = startingNo;
	startingNo += degOfFreedom[no];
	break;
      }

    case VAR_FEM:
    case VAR_VFEM:
	ePtr = itrV()->GetElementPtr();

	elementNo[no] = elementPtrLst.getPosition(ePtr);

	degOfFreedom[no]   = ePtr->GetElementFreedom();
	startingSblNo[no]  = startingNo;
	startingNo        += degOfFreedom[no];

      break;
      
      // scalar variables
    case VAR_EWISE:
    case VAR_DOUBLE:
    case VAR_INT:
    case VAR_CONST:
      degOfFreedom[no] = 1;
      //elementNo[no]  = -1;   // already initialized by -1
      startingSblNo[no] = startingNo;
      startingNo += degOfFreedom[no];
      break;
    }
    no++;
  }

  return;
}

void GalerkinMethod::Make_TermConvert(void)
{
  tcPtr = new TermConvert;

  listIterator <Variable *>itrV(weakIntegrandPtr->varPtrLst);

  for(itrV.init(); !itrV; ++itrV ){
    tcPtr->AddVariable(itrV());
  }

  //  unknown variable must be added if it is not included
  listIterator <Variable *>itrUV(unknownVarPtrLst);
  for(itrUV.init(); !itrUV; ++itrUV) {
    if( weakIntegrandPtr->varPtrLst.includes( itrUV() )) continue;
    tcPtr->AddVariable(itrUV());
  }

  // reverse TermConvert
  tcPtr->MakeReverseTC();

  return;
}

void GalerkinMethod::VarPtr_ElementPtr_TC_init()
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

void GalerkinMethod::CalculateTotalDOF()
{
  // calculate total freedom for element stiffeness
  listIterator <Variable *>itrUNV(unknownVarPtrLst);

  totalDOF = 0;
  for(itrUNV.init();!itrUNV; ++itrUNV) {

    // calculate element degree of freedom
    Element *ePtr = itrUNV()->GetElementPtr();
    totalDOF += ePtr->GetElementFreedom();
  }

  return;
}


// apply galerkin method.
void GalerkinMethod::ApplyGalerkin(DiscretizedComponent *dcPtr)
{
  listIterator <string>itrWeq(weakIntegrandPtr->integrandLst);
  listIterator <string>itrTfc(testfuncStrLst);
  listIterator <Variable *>itrUNV(unknownVarPtrLst);
  
  int *coeffSblNoVec = new int [totalDOF];
  int iptr = 0;
  for(itrUNV.init();!itrUNV; ++itrUNV) {

    int stno      = itrUNV()->GetSblNo();
    Element *ePtr = itrUNV()->GetElementPtr();
    int dof       = ePtr->GetElementFreedom();

    for(int i=0;i<dof;i++) {
      coeffSblNoVec[iptr] = stno + i;
      iptr++;
    }
  }

  itrTfc.init();
  itrUNV.init();

  int freedomAdd = 0;
  for(itrWeq.init(); !itrWeq ; ++itrWeq) {
    
    Element *ePtr = itrUNV()->GetElementPtr();

    // for each integrand,
    GalerkinTestFunction(dcPtr,itrWeq(),itrTfc(),ePtr,
			 freedomAdd,coeffSblNoVec);

    freedomAdd += ePtr->GetElementFreedom();
    ++itrTfc;
    ++itrUNV;
  }

  delete []coeffSblNoVec;
  return;
}

void GalerkinMethod::GalerkinTestFunction(DiscretizedComponent *dcPtr,
					  string weqIntegrandStr,
					  string testFunctionStr,
					  Element *ePtr         ,
					  int      freedomAdd   ,
					  int     *coeffSblNoVec )
  // coeffSblNoVec has array for unknowns symbol number
  // _m2 _m3 _m4 -> 2 3 4
{
  int freedom = ePtr->GetElementFreedom();
  void integrandDerivative(char *,int , char *, int);

  for(int i=0;i<freedom;i++) {
    
    int testFuncNo = ePtr->GetEstNo()+i;
    
    tcPtr->SetTestFunctionSymbol( testFunctionStr, testFuncNo );

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


    //    cerr << "coeff ("<<totalDOF <<") =";
    //    for(int ii=0;ii<totalDOF;ii++) {
    //      cerr << " " << coeffSblNoVec[ii] ;
    //    }
    //    cerr << endl;


    GetRightHandSide(ret,totalDOF,coeffSblNoVec,cformula,MAX_FORMULA_BUF);

    char *rev_ret = tcPtr->ReverseConvertExpressionString(cformula);

    dcPtr->SetRHS( i+freedomAdd, rev_ret);
  }

  // 2002-02-21  make identifier list  (for ecal generation)
  dcPtr->SetIdentifierList(tcPtr);
  dcPtr->SetElementPtrList(tcPtr);
  
  return;
}
