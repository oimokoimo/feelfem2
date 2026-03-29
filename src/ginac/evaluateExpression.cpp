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


//#include "Expression.hpp"
#include "feeldef.hpp"
#include "feelfuncs.hpp"             // abortExit
#include "evalPair.hpp"
#include "ptrList.hpp"

double evaluateBufGinac( char *buf    ,ptrList<evalPair *> *evalPairPtrLst, 
			 int  &errFlag                                  )
{
  // MAX_GINAC_VARIABLES is 12 now

  
//	std::cerr << "evaluateBufGinac\n" ;
//	std::cerr << "dbg: eval buf= " << buf << " = ";

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

//    std::cerr << ret << std::endl;  //dbg:

    errFlag = NO;

    return(ret);
  }

  std::cerr << "dbg:  ERROR" << std::endl;

  errFlag = YES;
  return(ERROR_EVALVAL);
}
