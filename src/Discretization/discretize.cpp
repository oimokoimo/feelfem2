/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : discretize.cpp
 *  Date     : 2001/05/09
 *  Modified : 2001/07/26
 *  
 *  Purpose  : main routine for making mathematical components of the FEM
 *             calculations
 *  
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

#include "list.hpp"
#include "parseExternals.hpp"

#include "feelfem.hpp"
#include "../parser/Syntax/SNunit.hpp"
//#include "../parser/Syntax/SNname.hpp"
//#include "Syntax/SNprogramModel.hpp"

class SNsolve;
class SNassignment;

void discretizeSolve(SNsolve *);
void discretizeAssignment(SNassignment *);

void discretize()
{
  listIterator <void *>itrScheme(parseSchemeLst);

  for(itrScheme.init(); !itrScheme; ++itrScheme) {

    switch(((SNunit *)itrScheme())->GetType()) {
      
    case SN_SOLVE:
      NOTE("goto discretizeSolve() in discretize.cpp");
      discretizeSolve( (SNsolve *)itrScheme() );
      break;

    case SN_ASSIGNMENT:
      NOTE("goto discretizeAssignment() in discretize.cpp");
      discretizeAssignment( (SNassignment *)itrScheme() );
      break;      

    default:
      break;

    }
  }

}
