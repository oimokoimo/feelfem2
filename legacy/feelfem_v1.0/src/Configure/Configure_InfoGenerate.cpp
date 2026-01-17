/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : Configure_InfoGenerate.cpp
 *  Date     : 2002/02/06
 *  Modified : 
 *  
 *  Purpose  :
 *  
 */
#include <assert.h>

#include "feeldef.hpp"
#include "pairClass.hpp"
#include "Configure.hpp"


int Configure::GetSolverLibraryCodeFromName(string &pm,string &lib)
{
  StrStrIntPair *ssiPtr= new StrStrIntPair( pm, lib, DUMMY_CODE);

  //  cerr << "CHECK(PM_LIB) " << pmName << " VS " << libName << endl;

  int no;
  no = pglibPairLst.getPosition(ssiPtr);

  assert(no>0);

  StrStrIntPair *ssiPairPtr = pglibPairLst.getNthElement(no);

  return(ssiPairPtr->GetCode());
}

