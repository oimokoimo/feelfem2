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
 */

#include <iostream.h>

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
