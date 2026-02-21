/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : quadrature_check.cpp
 *  Date     : 2001/03/27
 *  Modified : 2001/12/11
 *  
 *  Purpose  : check quadrature definitions
 *  
 *  
 *     
 *             SNquadrature::EvalExpressions()    evaluate...
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
 *  
 */
#include <iostream>

#include "check_funcs.hpp"

#include "../parser/Syntax/SNunit.hpp"
#include "../parser/Syntax/SNquadrature.hpp"
#include "../parser/Syntax/SNquadratureDoubleVar.hpp"
#include "../parser/Syntax/SNquadratureAssignment.hpp"
#include "../parser/Syntax/SNquadratureGaussP.hpp"

int quadrature_check(list <void *>&parseQuadratureLst)
{
  int errors;  
  errors = 0;

  listIterator <void *>itr(parseQuadratureLst);

  for(itr.init(); !itr ; ++itr) {

    int ret;
    SNquadrature *snqPtr = (SNquadrature*)itr();

    // set element type
    ret = snqPtr->SetEtype();    // set SNquadrature::etype, dimension
    if(ret != 0) {
      SystemErrorANameA(snqPtr,"quadrature ",
			" has illegal element shape specification.");
      errors++;
      continue;
    }

    // set number of gauss points
    ret = snqPtr->SetGaussPoints();
    if(ret != 0) {
      SystemErrorNameA(snqPtr," has no gauss Point.");
      errors++;
      continue;
    }

    // check every quadrature point has consistent dimension.
    ret = snqPtr->CheckGaussPDimension();
    errors+= ret;

  }

  // evaluate coordinates and weight value

  // Even if there is different dimension in quadrature point,
  // evaluate!  (CheckGaussPDimension does not stop the processing)

  int ret;

  ret = 0;

  for(itr.init(); !itr ; ++itr) {
    
    int iterRetVal;

    SNquadrature *snqPtr = (SNquadrature*)itr();

    iterRetVal = snqPtr->EvalExpressions();  // in SNquadrature_CHECK.cpp
                                             // this calls quadratureEval funcs
    ret +=  iterRetVal;
    if(iterRetVal) continue;  // skip if error

    iterRetVal = snqPtr->CheckGaussPRange(); // check integration points are
                                             // inside of refference element,

    //    cerr << "OIMO iterRetVal = " << iterRetVal << endl;
    ret +=  iterRetVal;

    iterRetVal = snqPtr->CheckConsistency(); // check integration weights are
                                             // consistent
    if(iterRetVal==YA) {
      SystemWarningANameA((SNunit *)itr(),"The sum of weight for quadrature ",
			  " is not consistent.");
    }
  } // iteration of quadrature pointers

  errors += ret;

  return(errors);
}
