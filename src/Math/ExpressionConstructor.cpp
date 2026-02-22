/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : ExpressionConstructor.cpp
 *  Date     : 2001/03/06
 *  Modified : 
 *  
 *  Purpose  : Constructor for Expression class
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

#include <iostream>

#include "Expression.hpp"

#include "../parser/Syntax/SNunit.hpp"

void exprAnalysis(Expression *,SNunit *);

void Expression::print(std::ostream & ost) {
  snExprPtr->print(ost);


  ost << "[identifiers=" << identifiers << "]";   // for debug

  return;
}

Expression::Expression(SNunit *snPtr)
{

  snExprPtr  = snPtr;
  eval_flag  = NO;                 // evaluation flag
  evalValue  = 0.0;                // eval Value
  lineNumber = 0;                  // lineNumber will be set by LineNumber(int)

  identifiers     = 0;
  functions       = 0;

  andOperators    = 0;
  orOperators     = 0;
  xorOperators    = 0;
  
  equalOperators  = 0;
  nequalOperators = 0;
  gtOperators     = 0;
  geOperators     = 0;
  ltOperators     = 0;
  leOperators     = 0;

  plusOperators   = 0;
  subOperators    = 0;
  mulOperators    = 0;
  divOperators    = 0;
  minusOperators  = 0;

  intNumbers      = 0;
  doubleNumbers   = 0;

  brackets        = 0;

  exprAnalysis(this,snPtr);

  return;
}

Expression::~Expression() = default;
