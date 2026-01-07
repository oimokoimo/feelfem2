/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : exprAnalysis.cpp
 *  Date     : 2001/02/27
 *  Modified : 
 *  
 *  Purpose  : Make mathematical object for expression.
 *  
 */

// #include "MathObject.hpp"

// Expression Syntax classes

#include "../parser/Syntax/SNunit.hpp"

#include "../parser/Syntax/SNand.hpp"
#include "../parser/Syntax/SNor.hpp"
#include "../parser/Syntax/SNxor.hpp"

#include "../parser/Syntax/SNequal.hpp"
#include "../parser/Syntax/SNnequal.hpp"

#include "../parser/Syntax/SNgt.hpp"
#include "../parser/Syntax/SNge.hpp"
#include "../parser/Syntax/SNlt.hpp"
#include "../parser/Syntax/SNle.hpp"

#include "../parser/Syntax/SNplus.hpp"     // +
#include "../parser/Syntax/SNsub.hpp"      // -
#include "../parser/Syntax/SNmul.hpp"      // *
#include "../parser/Syntax/SNdiv.hpp"      // /

#include "../parser/Syntax/SNminus.hpp"    // - (single op)
#include "../parser/Syntax/SNname.hpp"
#include "../parser/Syntax/SNsymbol.hpp"
#include "../parser/Syntax/SNint.hpp"
#include "../parser/Syntax/SNdouble.hpp"
#include "../parser/Syntax/SNfunction.hpp"
#include "../parser/Syntax/SNbracket.hpp"

#include "../parser/Syntax/SNexprlist.hpp"

#include "Expression.hpp"


void exprAnalysis(Expression *exprPtr, SNunit *snPtr)
{

  switch(snPtr->GetType()) {

  case SN_DOUBLE:
    exprPtr->doubleNumbers ++;
    break;

  case SN_INT:
    exprPtr->intNumbers ++;
    break;


  case SN_SYMBOL:
    if(!exprPtr->identifierLst.includes(((SNsymbol *)snPtr)->val)) {
      exprPtr->identifiers ++;
    }
    exprPtr->identifierLst.adduniq(((SNsymbol *)snPtr)->val);
    break;

  case SN_FUNCTION:
    if(!exprPtr->functionLst.includes(((SNfunction *)snPtr)->val)) {
      exprPtr->functions ++;
    }
    exprPtr->functionLst.adduniq(((SNfunction *)snPtr)->val);
    
    exprAnalysis(exprPtr, (SNunit *)((SNfunction *)snPtr)->exprlst);
    break;

  case SN_EXPRLIST:

    for(int i=0;i<((SNexprlist *)snPtr)->elements;i++) {
      //      cout << "Exprlist no=" << i+1 << "\n";
      exprAnalysis(exprPtr, *(((SNexprlist *)snPtr)->contents+i));
    }
    break;
    
    
  case SN_AND:
    exprPtr->andOperators++;
    exprAnalysis(exprPtr,(SNunit *)((SNand *)snPtr)->arg1);
    exprAnalysis(exprPtr,(SNunit *)((SNand *)snPtr)->arg2);
    break;


  case SN_PLUS:
    exprPtr->plusOperators++;
    exprAnalysis(exprPtr,(SNunit *)((SNplus *)snPtr)->arg1);
    exprAnalysis(exprPtr,(SNunit *)((SNplus *)snPtr)->arg2);
    break;

  case SN_SUB:
    exprPtr->subOperators++;
    exprAnalysis(exprPtr,(SNunit *)((SNsub *)snPtr)->arg1);
    exprAnalysis(exprPtr,(SNunit *)((SNsub *)snPtr)->arg2);
    break;

  case SN_MUL:
    exprPtr->mulOperators++;
    exprAnalysis(exprPtr,(SNunit *)((SNmul *)snPtr)->arg1);
    exprAnalysis(exprPtr,(SNunit *)((SNmul *)snPtr)->arg2);
    break;

  case SN_DIV:
    exprPtr->divOperators++;
    exprAnalysis(exprPtr,(SNunit *)((SNdiv *)snPtr)->arg1);
    exprAnalysis(exprPtr,(SNunit *)((SNdiv *)snPtr)->arg2);
    break;

  case SN_MINUS:
    exprPtr->minusOperators++;
    exprAnalysis(exprPtr,(SNunit *)((SNminus *)snPtr)->arg);
    break;

  case SN_BRACKET:
    exprPtr->brackets++;
    exprAnalysis(exprPtr,((SNbracket *)snPtr)->expr);
    break;


  case SN_EQUAL:
    exprPtr->equalOperators++;
    exprAnalysis(exprPtr,(SNunit *)((SNequal *)snPtr)->arg1);
    exprAnalysis(exprPtr,(SNunit *)((SNequal *)snPtr)->arg2);
    break;

  case SN_NEQUAL:
    exprPtr->nequalOperators++;
    exprAnalysis(exprPtr,(SNunit *)((SNnequal *)snPtr)->arg1);
    exprAnalysis(exprPtr,(SNunit *)((SNnequal *)snPtr)->arg2);
    break;

  case SN_GT:
    exprPtr->gtOperators++;
    exprAnalysis(exprPtr,(SNunit *)((SNgt *)snPtr)->arg1);
    exprAnalysis(exprPtr,(SNunit *)((SNgt *)snPtr)->arg2);
    break;

  case SN_GE:
    exprPtr->geOperators++;
    exprAnalysis(exprPtr,(SNunit *)((SNge *)snPtr)->arg1);
    exprAnalysis(exprPtr,(SNunit *)((SNge *)snPtr)->arg2);
    break;

  case SN_LT:
    exprPtr->ltOperators++;
    exprAnalysis(exprPtr,(SNunit *)((SNlt *)snPtr)->arg1);
    exprAnalysis(exprPtr,(SNunit *)((SNlt *)snPtr)->arg2);
    break;

  case SN_LE:
    exprPtr->leOperators++;
    exprAnalysis(exprPtr,(SNunit *)((SNle *)snPtr)->arg1);
    exprAnalysis(exprPtr,(SNunit *)((SNle *)snPtr)->arg2);
    break;


  default:
    cerr << "exprAnalysis Unknown SNcode " << snPtr->GetType()
	 << "[" ;
    snPtr->print(cerr); cerr <<"]\n";

    break;
  }


  return;

}
