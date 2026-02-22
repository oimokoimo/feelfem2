/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : DiscretizedComponent_EcalInfo_boundary.cpp
 *  Date     : 2002/04/01
 *  Modified : 2002/04/06
 *  
 *  Purpose  : Generate EcalInfo class data from DiscretizedComonent class
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
#include "feelfuncs.hpp"

#include "list.hpp"
#include "string.hpp"
#include "DiscretizedComponent.hpp"
#include "EcalInfo.hpp"
#include "Element.hpp"
#include "IntegrandSet.hpp"

// called from Neumann_discretize.cpp 
// void SolveElement::GenerateEcalInfo()

EcalInfo *DiscretizedComponent::
GenerateBoundaryEcalInfo(int spaceDim, 
			 Element *parametricElemPtr,
			 BoundaryIntegrandSet *isPtr)
{
  EcalInfo *eiPtr = new EcalInfo;
  assert(eiPtr != 0);

  int freedom;

  eiPtr->SetNumbers(solveNo,ncondNo);

  // set use X,Y,Z, use NX,NY,NZ (boundary)
  eiPtr->SetUseXYZ(isPtr->GetUseX(),isPtr->GetUseY(),isPtr->GetUseZ());
  eiPtr->SetUseNXNYNZ(isPtr->GetUseNX(),isPtr->GetUseNY(),isPtr->GetUseNZ());

  // add parametric Element  (add the func and its first derivatives)
  // boundary element

  Element  *bparaElemPtr = parametricElemPtr->AcquireBoundaryElementPtr();

  freedom = bparaElemPtr -> GetElementFreedom();  // boundary

  char buf[TERM_LENGTH];

  // function itself

  // for eset (boundary)
  eiPtr->AddUniqEcalEvalPair_boundary( bparaElemPtr,TYPE_DIFF_ZERO);

  for(int i=0;i<freedom;i++) {

    //boundary has no quad no
    int bno;
    bno = bparaElemPtr->GetIthOriginalIplus1(i);
    sprintf(buf,"r%s_%d%c",parametricElemPtr->GetName(),bno,'\0');
    eiPtr->AddUniqTermCommon( buf );
  }
  
  // derivative of X for parametric element

  // for eset
  eiPtr->AddUniqEcalEvalPair_boundary( bparaElemPtr,TYPE_DIFF_X );
  for(int i=0;i<freedom;i++) {

 //sprintf(buf,"r%s_%d_x_%d%c",parametricElemPtr->GetName(),i+1,quadNo,'\0');

    // boundary has no quad No.
    int bno;
    bno = bparaElemPtr->GetIthOriginalIplus1(i);
    sprintf(buf,"r%s_%d_x%c",parametricElemPtr->GetName(),bno,'\0');
    eiPtr->AddUniqTermCommon( buf );
  }

  // derivative of y for parametric element (boundary)
  if(spaceDim >1) {

    // for eset
    eiPtr->AddUniqEcalEvalPair_boundary( bparaElemPtr,TYPE_DIFF_Y);
    for(int i=0;i<freedom;i++) {

 //sprintf(buf,"r%s_%d_y_%d%c",parametricElemPtr->GetName(),i+1,quadNo,'\0');

      // boundary has no quadno
      int bno;
      bno = bparaElemPtr->GetIthOriginalIplus1(i);
      sprintf(buf,"r%s_%d_y%c",parametricElemPtr->GetName(),bno,'\0');
      eiPtr->AddUniqTermCommon( buf );
    }    
  }

  // derivative of z for parametric element (boundary)
  if(spaceDim >2) {

    // for eset
    eiPtr->AddUniqEcalEvalPair_boundary( bparaElemPtr, TYPE_DIFF_Z );
    for(int i=0;i<freedom;i++) {

      // boundary has no quadno
      int bno;
      bno = bparaElemPtr->GetIthOriginalIplus1(i);
      sprintf(buf,"r%s_%d_z%c",parametricElemPtr->GetName(),bno,'\0');
      eiPtr->AddUniqTermCommon( buf );
    }    
  }


  // Add appeared in Integrand                       (2nd Order PDE)
  listIterator <Element *>itrE(elementPtrLst);
  
  for(itrE.init();!itrE;++itrE) {
    
    string term;

    Element *bElemPtr;
    bElemPtr = itrE()->AcquireBoundaryElementPtr();

    freedom = bElemPtr->GetElementFreedom();     // boundary

    for(int i=0;i<freedom;i++) {
      
      int bno;
      bno = bElemPtr->GetIthOriginalIplus1(i);

      // function itself
      sprintf(buf,"q%s_%d%c",itrE()->GetName(),bno,'\0');
      term=buf;
      if(identifierLst.includes(term)) {

	// for eset
	eiPtr->AddUniqEcalEvalPair_boundary( bElemPtr,TYPE_DIFF_ZERO);

	//sprintf(buf,"r%s_%d_%d%c",itrE()->GetName(),i+1,quadNo,'\0');

	// one quadrature for boundary
	sprintf(buf,"r%s_%d%c",itrE()->GetName(),bno,'\0');
	eiPtr->AddUniqTermCommon( buf );

	sprintf(buf,"q%s_%d%c",itrE()->GetName(),bno,'\0');
	eiPtr->AddUniqTermIntegrand( buf );
      }

      // function x derivative
      sprintf(buf,"q%s_%d_x%c",itrE()->GetName(),bno,'\0');
      term=buf;
      if(identifierLst.includes(term)) {

	// for eset
	eiPtr->AddUniqEcalEvalPair_boundary( bElemPtr,TYPE_DIFF_X );

	//sprintf(buf,"r%s_%d_x_%d%c",itrE()->GetName(),i+1,quadNo,'\0');

	// boundary has one quadrature
	sprintf(buf,"r%s_%d_x%c",itrE()->GetName(),bno,'\0');

	eiPtr->AddUniqTermCommon( buf );

	sprintf(buf,"q%s_%d_x%c",itrE()->GetName(),bno,'\0');
	eiPtr->AddUniqTermIntegrand( buf );
      }

      // function y derivative
      if(spaceDim >1) {
	sprintf(buf,"q%s_%d_y%c",itrE()->GetName(),bno,'\0');
	term=buf;
	if(identifierLst.includes(term)) {
	  
	  // for eset (boundary)
	  eiPtr->AddUniqEcalEvalPair_boundary( bElemPtr,TYPE_DIFF_Y );

	  sprintf(buf,"r%s_%d_y%c",itrE()->GetName(),bno,'\0');
	  eiPtr->AddUniqTermCommon( buf );
	  
	  sprintf(buf,"q%s_%d_y%c",itrE()->GetName(),bno,'\0');
	  eiPtr->AddUniqTermIntegrand( buf );
	}
      }

      if(spaceDim >2) {
	// function z derivative
	sprintf(buf,"q%s_%d_z%c",itrE()->GetName(),bno,'\0');
	term=buf;
	if(identifierLst.includes(term)) {

	  // for eset
	  eiPtr->AddUniqEcalEvalPair_boundary(bElemPtr,TYPE_DIFF_Z );

	  //sprintf(buf,"r%s_%d_z_%d%c",itrE()->GetName(),i+1,quadNo,'\0');

	  // boundary has only one quadrature
	  sprintf(buf,"r%s_%d_z%c",itrE()->GetName(),bno,'\0');
	  eiPtr->AddUniqTermCommon( buf );
	  
	  sprintf(buf,"q%s_%d_z%c",itrE()->GetName(),bno,'\0');
	  eiPtr->AddUniqTermIntegrand( buf );
	}
      }
    }
  }

  return(eiPtr);
}
