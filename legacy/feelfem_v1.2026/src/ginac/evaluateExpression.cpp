/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : evaluateExpression.cpp
 *  Date     : 2001/03/12
 *  Modified : 2001/03/19
 *  
 *  Purpose  :

 *  
 */


//#include "Expression.hpp"
#include "feeldef.hpp"
#include "feelfuncs.hpp"             // abortExit
#include "evalPair.hpp"
#include "ptrList.hpp"

double evaluateBufGinac( char *buf    ,ptrList<evalPair *> *evalPairPtrLst, 
			 int  &errFlag                                  )
{
  // MAX_GINAC_VARIABLES is 12 now

  //  cerr << "dbg: eval buf= " << buf << " = ";

  setExprGinacEvaluate( buf );

  listIterator <evalPair *> itr(*evalPairPtrLst);
  int i;
  i = 0;

  for(itr.init(); !itr ; ++itr) {
    if(i >= MAX_GINAC_VARIABLES) {
      abortExit("Too many variables in evaluateExpression.cpp");
    }
    if(itr()->isNumber() != YES) {
      //      cerr << "SKIP substract ";
      //      itr()->print(cerr);
      //      cerr << " (because of not assigned value, and necessary)\n";
      ;
    }
    else {
      subsExprGinacEvaluate(i,itr()->getValue());
    }
    i++;
  }

  if(isExprGinacNumeric()) {
    double ret;

    ret = getDoubleExprGinac();

    //    cerr << ret << endl;  //dbg:

    errFlag = NO;

    return(ret);
  }

  //  cerr << "dbg:  ERROR" << endl;

  errFlag = YES;
  return(ERROR_EVALVAL);
}
