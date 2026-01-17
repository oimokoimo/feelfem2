/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : MakeBoundaryElement_rect.cpp
 *  Date     : 2002/04/01
 *  Modified : 
 *  
 *  Purpose  : Boundary element for rectangle element
 *  
 */

#include <stdio.h>

#include "Element.hpp"
#include "TermConvert.hpp"

#include "ginac_funcs.hpp"

void Element::MakeBoundaryElement_rect(TermConvert &tc)
{
  bElementPtr = new Element;
  bElementPtr->boundaryElementFlag = YES;
   
  bElementPtr->SetEtype( ELEMENT_TYPE_LINE );
  
  char namebuf[BUFSIZ];                      // boundary element name = b+name
  sprintf(namebuf,"b%s%c",(char *)name,'\0');
  bElementPtr->SetName( namebuf );


  // r,s
  tc.storeConvertPair("r","a01");
  tc.storeConvertPair("s","a02");

  int dof = 0;

  listIterator <Interpolation *>itrP(interpPtrLst);
  for(itrP.init(); !itrP ; ++itrP ) {
    string exprG = tc.convertExpressionString(itrP()->GetExprString());

    setExprGinacEvaluate( exprG );
    subsExprGinacEvaluate( 1, -1.0);  // s == 0

    char buf[BUFSIZ];
    setGinacExprToCharBuf(buf,BUFSIZ);
    exprG = buf;

    exprG = tc.SimpleReverseConvertExpressionString( exprG );
    cerr << "expr[bintp-rect] = " << exprG << endl;

    if(exprG == "0.0" || exprG == "0") continue;
    
    dof++;
  }

  cerr << "boundary dof = " << dof << endl;

  bElementPtr->SetNumberOfFreedom( dof );

  return;
}
