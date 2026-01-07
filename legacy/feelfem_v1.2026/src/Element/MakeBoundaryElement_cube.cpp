/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : MakeBoundaryElement_cube.cpp
 *  Date     : 2002/04/01
 *  Modified : 
 *  
 *  Purpose  : Boundary element for hexahedra element
 *  
 */

#include <stdio.h>

#include "Element.hpp"
#include "TermConvert.hpp"

#include "ginac_funcs.hpp"

void Element::MakeBoundaryElement_cube(TermConvert &tc)
{
  bElementPtr = new Element;
  bElementPtr->boundaryElementFlag = YES;
  
  bElementPtr->SetEtype( ELEMENT_TYPE_RECT );
  
  char namebuf[BUFSIZ];                      // boundary element name = b+name
  sprintf(namebuf,"b%s%c",(char *)name,'\0');
  bElementPtr->SetName( namebuf );


  // r,s
  tc.storeConvertPair("r","a01");
  tc.storeConvertPair("s","a02");
  tc.storeConvertPair("t","a03");


  int dof = 0;

  listIterator <Interpolation *>itrP(interpPtrLst);
  for(itrP.init(); !itrP ; ++itrP ) {
    string exprG = tc.convertExpressionString(itrP()->GetExprString());

    // set ginac buffer
    setExprGinacEvaluate( exprG );

    // restrict to plane t=-1
    subsExprGinacEvaluate( 2, -1.0);  // t == -1

    // get expression
    char buf[BUFSIZ];
    setGinacExprToCharBuf(buf,BUFSIZ);
    exprG = buf;

    exprG = tc.SimpleReverseConvertExpressionString( exprG );
    cerr << "expr[bintp-cube] = " << exprG << endl;

    // make node

    if(exprG == "0.0" || exprG == "0") continue;
    
    dof++;
  }

  cerr << "boundary dof = " << dof << endl;

  bElementPtr->SetNumberOfFreedom( dof );

  return;
}
