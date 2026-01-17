/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : MakeBoundaryElement_tri.cpp
 *  Date     : 2002/03/26
 *  Modified : 
 *  
 *  Purpose  : Boundary element for triangle element
 *  
 */

#include <stdio.h>

#include "feelfuncs.hpp"  // for abortExit

#include "Element.hpp"
#include "TermConvert.hpp"

#include "ginac_funcs.hpp"

void Element::MakeBoundaryElement_tri(TermConvert &tc)
{
  int boundaryElementType    = ELEMENT_TYPE_LINE;     // tri dependent
  int originalInterpolations = numberOfFreedom;

  bElementPtr = new Element;
  bElementPtr->boundaryElementFlag   = YES;
  bElementPtr->numberOfRegionFreedom = originalInterpolations;
  bElementPtr->rElementPtr           = this;   // parent element
                                               // (used for error check)
  
  bElementPtr->SetEtype( boundaryElementType );
  
  //  char namebuf[BUFSIZ];                // boundary element name = b+name
  //  sprintf(namebuf,"b_%s%c",(char *)name,'\0');
  bElementPtr->SetName( name );   // same name

  // r,s,t
  tc.storeConvertPair("r","a01");
  tc.storeConvertPair("s","a02");
  tc.storeConvertPair("t","a03");

  int dof = 0;

  int totalInterp    = interpPtrLst.getNumberOfElements();
  bInterpolationFlag = new int [ totalInterp ];
  for(int i=0;i<totalInterp;i++) {
        bInterpolationFlag[i] = 0;
  }

  listIterator <Interpolation *>itrP(interpPtrLst);
  int ptr = 0;
  for(itrP.init(); !itrP ; ++itrP ) {

    //    string exprG = tc.convertExpressionString(itrP()->GetExprString());
    string exprG;

    char *exprBufPtr = tc.convertExpressionString(itrP()->GetExprString());

    // set ginac buffer
    //    setExprGinacEvaluate( (char *)exprG );
    setExprGinacEvaluate( exprBufPtr );

    // restrict to x-axis
    subsExprGinacEvaluate( 1, 0.0);  // s == 0

    // coordinate transfer
    subsExprGinacEvaluate( 0, "(a01+1.0)/2.0");

    // get ginac 
    char buf[BUFSIZ];
    setGinacExprToCharBuf(buf,BUFSIZ);
    exprG = buf;

    exprG = tc.SimpleReverseConvertExpressionString( exprG );

    // Make Boundary Interpolation
    Node *org_ndPtr = itrP()->GetNodePtr();

    // TRI dependent  (TRI->LINE)  with transformation 
    Node *new_ndPtr = new Node(boundaryElementType,     
			       2.0 * org_ndPtr->GetXi() - 1.0    );

    // Add Node
    if(bElementPtr->HasAlreadyDefinedNode( new_ndPtr )== YES) {
      ;
    }
    else {
      bElementPtr->AddNodePtr(new_ndPtr);
    }

    // Add interpolation
    Interpolation *newIPtr = new Interpolation();

    newIPtr->SetType( itrP()->GetType() );
    newIPtr->SetExprStr( (char *)exprG);

    newIPtr->SetNodePtr( org_ndPtr ); 
    newIPtr->SetBoundaryNodePtr( new_ndPtr );  // boundary node
    
    bElementPtr->AddInterpolationPtr( newIPtr );

    if(exprG != "0.0" && exprG != "0") {
      dof++;
      bInterpolationFlag[ptr] = 1;
    } // oimo oimo oimo

    ptr++;
  }

  bElementPtr->SetNumberOfFreedom( dof );

  // copy bInterpolationFlag to Boundary element area
  bElementPtr->bInterpolationFlag = new int [totalInterp];
  for(int i=0;i<totalInterp;i++) {
    (bElementPtr->bInterpolationFlag)[i] = bInterpolationFlag[i];
  }

  return;
}
