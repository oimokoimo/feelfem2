/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : DiscretizedComponent_EcalInfo.cpp
 *  Date     : 2002/02/26
 *  Modified : 2002/07/11  if differential, all differential necessary
 *  
 *  Purpose  : Generate EcalInfo class data from DiscretizedComonent class
 *  
 */

#include <stdio.h>

#include "feeldef.hpp"

#include "list.hpp"
#include "string.hpp"
#include "DiscretizedComponent.hpp"
#include "EcalInfo.hpp"
#include "Element.hpp"
#include "IntegrandSet.hpp"


// called from SolveElement_discretize.cpp 
// void SolveElement::GenerateEcalInfo()

EcalInfo *DiscretizedComponent::GenerateEcalInfo(int spaceDim, 
						 Element *parametricElemPtr,
						 IntegrandSet *isPtr)
{
  int freedom;
  EcalInfo *eiPtr = new EcalInfo;

  eiPtr->SetNumbers(solveNo,solveElementNo,quadNo);

  // set use X,Y,Z
  eiPtr->SetUseXYZ(isPtr->GetUseX(),isPtr->GetUseY(),isPtr->GetUseZ());

  // add parametric Element  (add the func and its first derivatives)
  freedom = parametricElemPtr -> GetElementFreedom();
  
  char buf[TERM_LENGTH];

  // function itself

  // for eset
  eiPtr->AddUniqEcalEvalPair( parametricElemPtr,TYPE_DIFF_ZERO);
  for(int i=0;i<freedom;i++) {
    sprintf(buf,"r%s_%d_%d%c",parametricElemPtr->GetName(),i+1,quadNo,'\0');
    eiPtr->AddUniqTermCommon( buf );


  }
  
  // derivative of X for parametric element

  // for eset
  eiPtr->AddUniqEcalEvalPair( parametricElemPtr,TYPE_DIFF_X );
  for(int i=0;i<freedom;i++) {
    sprintf(buf,"r%s_%d_x_%d%c",parametricElemPtr->GetName(),i+1,quadNo,'\0');
    eiPtr->AddUniqTermCommon( buf );
  }

  // derivative of y for parametric element
  if(spaceDim >1) {

    // for eset
    eiPtr->AddUniqEcalEvalPair( parametricElemPtr,TYPE_DIFF_Y);
    for(int i=0;i<freedom;i++) {
      sprintf(buf,"r%s_%d_y_%d%c",parametricElemPtr->GetName(),i+1,quadNo,'\0');
      eiPtr->AddUniqTermCommon( buf );
    }    
  }

  // derivative of z for parametric element
  if(spaceDim >2) {

    // for eset
    eiPtr->AddUniqEcalEvalPair( parametricElemPtr, TYPE_DIFF_Z );
    for(int i=0;i<freedom;i++) {
      sprintf(buf,"r%s_%d_z_%d%c",parametricElemPtr->GetName(),i+1,quadNo,
	      '\0');
      eiPtr->AddUniqTermCommon( buf );
    }    
  }


  // Add appeared in Integrand                       (2nd Order PDE)
  listIterator <Element *>itrE(elementPtrLst);
  
  for(itrE.init();!itrE;++itrE) {
    
    string term;

    freedom = itrE()->GetElementFreedom();

    for(int i=0;i<freedom;i++) {
      
      // function itself
      sprintf(buf,"q%s_%d%c",itrE()->GetName(),i+1,'\0');
      term=buf;
      if(identifierLst.includes(term)) {

	// for eset
	eiPtr->AddUniqEcalEvalPair( itrE(),TYPE_DIFF_ZERO);


	sprintf(buf,"r%s_%d_%d%c",itrE()->GetName(),i+1,quadNo,'\0');
	eiPtr->AddUniqTermCommon( buf );

	sprintf(buf,"q%s_%d%c",itrE()->GetName(),i+1,'\0');
	eiPtr->AddUniqTermIntegrand( buf );
      }

      // function x derivative
      sprintf(buf,"q%s_%d_x%c",itrE()->GetName(),i+1,'\0');
      term=buf;
      if(identifierLst.includes(term)) {

	// for eset
	eiPtr->AddUniqEcalEvalPair( itrE(),TYPE_DIFF_X );

	sprintf(buf,"r%s_%d_x_%d%c",itrE()->GetName(),i+1,quadNo,'\0');
	eiPtr->AddUniqTermCommon( buf );

	sprintf(buf,"q%s_%d_x%c",itrE()->GetName(),i+1,'\0');
	eiPtr->AddUniqTermIntegrand( buf );

	// for Y derivative(02/07/11)
	if(spaceDim > 1) {
	  eiPtr->AddUniqEcalEvalPair( itrE(),TYPE_DIFF_Y );

	  sprintf(buf,"r%s_%d_y_%d%c",itrE()->GetName(),i+1,quadNo,'\0');
	  eiPtr->AddUniqTermCommon( buf );
	  
	  sprintf(buf,"q%s_%d_y%c",itrE()->GetName(),i+1,'\0');
	  eiPtr->AddUniqTermIntegrand( buf );
	}

	// for Z derivative(02/07/11)
	if(spaceDim > 2) {
	  eiPtr->AddUniqEcalEvalPair( itrE(),TYPE_DIFF_Z );

	  sprintf(buf,"r%s_%d_z_%d%c",itrE()->GetName(),i+1,quadNo,'\0');
	  eiPtr->AddUniqTermCommon( buf );
	  
	  sprintf(buf,"q%s_%d_z%c",itrE()->GetName(),i+1,'\0');
	  eiPtr->AddUniqTermIntegrand( buf );
	}

      }

      // function y derivative
      if(spaceDim >1) {
	sprintf(buf,"q%s_%d_y%c",itrE()->GetName(),i+1,'\0');
	term=buf;
	if(identifierLst.includes(term)) {
	  
	  // for eset
	  eiPtr->AddUniqEcalEvalPair( itrE(),TYPE_DIFF_X );

	  sprintf(buf,"r%s_%d_x_%d%c",itrE()->GetName(),i+1,quadNo,'\0');
	  eiPtr->AddUniqTermCommon( buf );

	  sprintf(buf,"q%s_%d_x%c",itrE()->GetName(),i+1,'\0');
	  eiPtr->AddUniqTermIntegrand( buf );

	  // for Y derivative(02/07/11)
	  if(spaceDim > 1) {
	    eiPtr->AddUniqEcalEvalPair( itrE(),TYPE_DIFF_Y );

	    sprintf(buf,"r%s_%d_y_%d%c",itrE()->GetName(),i+1,quadNo,'\0');
	    eiPtr->AddUniqTermCommon( buf );
	  
	    sprintf(buf,"q%s_%d_y%c",itrE()->GetName(),i+1,'\0');
	    eiPtr->AddUniqTermIntegrand( buf );
	  }

	  // for Z derivative(02/07/11)
	  if(spaceDim > 2) {
	    eiPtr->AddUniqEcalEvalPair( itrE(),TYPE_DIFF_Z );

	    sprintf(buf,"r%s_%d_z_%d%c",itrE()->GetName(),i+1,quadNo,'\0');
	    eiPtr->AddUniqTermCommon( buf );
	  
	    sprintf(buf,"q%s_%d_z%c",itrE()->GetName(),i+1,'\0');
	    eiPtr->AddUniqTermIntegrand( buf );
	  }
	}
      }

      if(spaceDim >2) {
	// function z derivative
	sprintf(buf,"q%s_%d_z%c",itrE()->GetName(),i+1,'\0');
	term=buf;
	if(identifierLst.includes(term)) {


	  // for eset
	  eiPtr->AddUniqEcalEvalPair( itrE(),TYPE_DIFF_X );

	  sprintf(buf,"r%s_%d_x_%d%c",itrE()->GetName(),i+1,quadNo,'\0');
	  eiPtr->AddUniqTermCommon( buf );

	  sprintf(buf,"q%s_%d_x%c",itrE()->GetName(),i+1,'\0');
	  eiPtr->AddUniqTermIntegrand( buf );

	  // for Y derivative(02/07/11)
	  if(spaceDim > 1) {
	    eiPtr->AddUniqEcalEvalPair( itrE(),TYPE_DIFF_Y );

	    sprintf(buf,"r%s_%d_y_%d%c",itrE()->GetName(),i+1,quadNo,'\0');
	    eiPtr->AddUniqTermCommon( buf );
	  
	    sprintf(buf,"q%s_%d_y%c",itrE()->GetName(),i+1,'\0');
	    eiPtr->AddUniqTermIntegrand( buf );
	  }

	  // for Z derivative(02/07/11)
	  if(spaceDim > 2) {
	    eiPtr->AddUniqEcalEvalPair( itrE(),TYPE_DIFF_Z );

	    sprintf(buf,"r%s_%d_z_%d%c",itrE()->GetName(),i+1,quadNo,'\0');
	    eiPtr->AddUniqTermCommon( buf );
	  
	    sprintf(buf,"q%s_%d_z%c",itrE()->GetName(),i+1,'\0');
	    eiPtr->AddUniqTermIntegrand( buf );
	  }
	}
      }
    }
  }

  return(eiPtr);
}
