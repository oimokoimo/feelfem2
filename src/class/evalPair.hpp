/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : evalPair.hpp
 *  Date     : 2001/03/15
 *  Modified : 2001/03/26  name change (from ginacInFeelfem.hpp)
 *  
 *  Purpose  : Ginac interface functions
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

#ifndef FEM_CLASS_EVALPAIR
#define FEM_CLASS_EVALPAIR

#include <iostream>

#include "feeldef.hpp"
#include "string.hpp"
#include "ginac_funcs.hpp"

class meshEvalGinac;
class quadratureEvalGinac;
class elementEvalGinac;

class evalPair {
public:

  // constructor without value
  evalPair(string nm) {
    varName  =  nm;
    evalFlag =  NO;
    value    = -999.0;
  }
  
  evalPair(const char *nm) {
    varName  = nm;
    evalFlag = NO;
    value    = -999.0;
  }
  
  // constructor with value
  evalPair(string nm, double initialValue) {
    varName  = nm;
    evalFlag = YES;
    value    = initialValue;
    return;
  }

  evalPair(const char *nm, double initialValue) {
    varName  = nm;
    evalFlag = YES;
    value    = initialValue;
    return;
  }


  ~evalPair() = default;

  void setValue( double val )
  {
    value    = val;
    evalFlag = YES;
    return;
  }
  
  int isNumber(void) 
  {
    if(evalFlag) return (YES);
    else         return (NO);
  }

  double getValue(void)
  {
    return(value);
  }

  int isNameIs(string &nm) {
    return(nm == varName);
  }

  friend int operator == (const evalPair & left, const evalPair &right);

  void print(std::ostream &ost) {
    ost << varName;
  }


  friend meshEvalGinac;         // to access varName
  friend quadratureEvalGinac;   // to access varName
  friend elementEvalGinac;

private:
  string      varName;
  int         evalFlag;
  double      value;
};

#endif
