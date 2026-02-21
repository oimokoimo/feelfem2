/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : Configure_CHECK.cpp
 *  Date     : 2001/10/26
 *  Modified : 
 *  
 *  Purpose  : Check functions in Configure class
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

#include <cstdlib>

#include "feeldef.hpp"
#include "Configure.hpp"
#include "pairClass.hpp"

// for SNprogramModel
int Configure::GetProgramModelCodeFromName(string &nm)
{
  StrIntPair *ptr = new StrIntPair ( nm , DUMMY_CODE );

  int pos = programModelLst.getPosition (ptr);

  ptr -> ~StrIntPair();

  ptr = programModelLst.getNthElement( pos );

  return( ptr->getCode() );
}

int Configure::IsValidProgramModelName(string &nm)
{
  StrIntPair *ptr = new StrIntPair ( nm , DUMMY_CODE );
  
  if(programModelLst.includes( ptr ) ) {
    ptr -> ~StrIntPair();
    return(YES);
  }
  else {
    ptr -> ~StrIntPair();
    return( NO );
  }
}

////////////////////////////////////////////////////
// for SNsolve
////////////////////////////////////////////////////
int Configure::IsValidSolverName( string &nm )
{
  if(solverNameLst.includes( nm )) {
    return(YES);
  }
  else {
    return(NO);
  }
}

int Configure::IsValidPM_LIB( string &pmName, string &libName )
{
  StrStrIntPair *ssiPtr= new StrStrIntPair( pmName, libName, DUMMY_CODE);

  //  cerr << "CHECK(PM_LIB) " << pmName << " VS " << libName << endl;
  if(pglibPairLst.includes(ssiPtr)) {
    return(YES);
  }
  else {
    return(NO);
  }
}

// for SNsolve::CheckInit  (default solver)
void Configure::SetDefaultSolverName( string &pgName, string &solverName )
  // pgName is input, and solverName (output)
{
  listIterator <StrStrPair *>itr(pglibDefaultPairLst);

  for(itr.init(); !itr ; ++itr) {
    
    if(itr()->IsMatchFirstComponent( pgName ) ) {
      itr()->SetArgStringWithSecond( solverName );
      return;
    }
  }

  std::cerr << "In Configure::SetDefaultSolverName, can't find default solver for ";
  std::cerr << "ProgramModel " << pgName << std::endl;
  exit(1);
}


