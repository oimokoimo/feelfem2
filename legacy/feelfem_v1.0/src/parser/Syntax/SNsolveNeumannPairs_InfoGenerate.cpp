/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNsolveNeumannPairs_InfoGenerate.cpp
 *  Date     : 2002/04/02
 *  Modified : 
 *  
 *  Purpose  :
 *  
 */

#include <iostream.h>

#include "feeldef.hpp"

#include "SNsolveNeumann.hpp"
#include "Neumann.hpp"

#include "string.hpp"
#include "pairClass.hpp"

void SNsolveNeumannPairs::AddNeumannDataPairs( Neumann *nPtr )
{
  listIterator <string> itrArg(neumannArgumentLst);
  listIterator <Expression *>itrExpr(neumannExpressionLst);

  itrExpr.init();
  for(itrArg.init(); !itrArg ; ++itrArg) {

    // check x,y,z,nx,ny,nz are used
    itrExpr()->CheckXYZNXNYNZ_Neumann(nPtr);


    char buf[MAX_EXPRPRINT_BUF];
    buf[0] = '\0';
    itrExpr()->exprPrint(buf,EXPRPRINT_SIMPLE,0,0);
    
    StrStrPair *ssPairPtr = new StrStrPair( itrArg() , buf );
    
    nPtr->AddNeumannDataSSPairPtr( ssPairPtr );

    ++itrExpr;
  }
  return;
}
