/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : isIntrinsicFunction.cpp
 *  Date     : 2001/03/20
 *  Modified : 
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
#include "feeldef.hpp"
#include "string.hpp"

#include "feelfuncs.hpp"
#include "Object.hpp"

int isIntrinsicFunction(string &name)
{
  string small=name;

  small.lower();   // make lower letter

  if(small == "sin") return(YES);
  if(small == "cos") return(YES);
  if(small == "tan") return(YES);
  if(small == "sqrt") return(YES);
  if(small == "abs") return(YES);
  if(small == "atan") return(YES);
  if(small == "dsqrt") return(YES);
  //  if(small == "pow") return(YES);
  if(small == "exp") return(YES);

  //  cerr << small << " is not Intrinsic function (isIntrinsicFunction.cpp)\n";
  
  return(NO);
}


int isDifferentialOperator1(string &name)    // 1 means first order
{
  int dim;

  dim = feelfemobj.GetSpaceDimension();

  if(name == "dx"           ) return(YES);
  if(name == "dy" && dim > 1) return(YES);
  if(name == "dz" && dim > 2) return(YES);
  
  return(NO);
}

