/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : codeGenerateSubroutines.cpp
 *  Date     : 2001/05/09
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

#include <iostream>

#include "list.hpp"
#include "parseExternals.hpp"

#include "../parser/Syntax/SNunit.hpp"
#include "../parser/Syntax/SNname.hpp"
//#include "Syntax/SNprogramModel.hpp"

#include "cg_functions.hpp"


class SNsolve;
void SolveGenerateMain(SNsolve *);


void codeGenerateSubroutines()
{
  int i= 0;

  listIterator <void *>itrScheme(parseSchemeLst);
  for(itrScheme.init(); !itrScheme; ++itrScheme) {
    i++;
    //    cout << "No." << i <<": ";
    //    ((SNunit *)itrScheme())->print(cout);
    //    cout << "\n";

    SNunit *snuPtr;

    snuPtr = (SNunit *)itrScheme();

    snuPtr->CodeGenerate();

    //    switch(((SNunit *)itrScheme())->GetType()) {
    //
    //    case SN_SOLVE:
    //      ((SNunit *)itrScheme())->CodeGenerate();
    //      
    //      break;
    //
    //    case SN_ASSIGNMENT:
    //
    //
    //    default:
    //      break;
    //    }

  }

  return;
}
