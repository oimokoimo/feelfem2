/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : Configure.cpp
 *  Date     : 2001/08/20
 *  Modified : 
 *  
 *  Purpose  : Initialization of configuration
 *  
 *             This Configure class is the database for
 *             name-code correspondance.
 *  
 *             Configure feelfemconf is declared in Configure/initConfigure.cpp
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

#include "feeldef.hpp"
#include "Configure.hpp"
#include <cstdlib>

void Configure::StorePM_LIB(const char *pgName,const char *libName,int type)
{
  StrStrIntPair *pg_libPairPtr = new StrStrIntPair( pgName, libName , type);
  
  if(pglibPairLst.includes( pg_libPairPtr ) ) {
    std::cerr << "PG-LIB pair " << pgName << " and " << libName << " [type=";
    std::cerr << type <<"] is multiply registered.\n";
    exit(1);   // Initialize routine abnormal exit
  }

  pglibPairLst.addlast( pg_libPairPtr );


  // make solver name list
  if(solverNameLst.includes( libName )) {
    ; // do nothing
  }
  else {
    solverNameLst.addlast( libName );
  }

  return;
}


void Configure::StoreDefaultPM_LIB(const char *pgName,const char *libName)
{
  StrStrPair *pg_libPairPtr = new StrStrPair( pgName, libName);
  
  if(pglibDefaultPairLst.includes( pg_libPairPtr ) ) {
    std::cerr << "PG-LIB pair " << pgName << " and " << libName;
    std::cerr << " is multiply registered.\n";
    exit(1);   // Initialize routine abnormal exit
  }

  pglibDefaultPairLst.addlast( pg_libPairPtr );

  return;
}


void Configure::StoreProgramModelNames(const char *pgName, int pgCode)
{
  StrIntPair *pModelNamePtr = new StrIntPair( pgName, pgCode );

  // unique check

  if(programModelLst.includes( pModelNamePtr) ) { 
    std::cerr << "program model name " << pgName << " multiply registered.\n";
    std::cerr << "Configure::StoreProgramModelNames\n";
    exit(1);  // Initialize routine abnormal exit
  }


  programModelLst.addlast( pModelNamePtr );
  
  return;
}


void Configure::SetProgramModelNameFromCode(int no, string &retString)
{
  StrIntPair *siPtr;

  listIterator <StrIntPair *> itr(programModelLst);
  
  for(itr.init(); !itr ; ++itr ) {
    
    siPtr = itr();
    
    if(siPtr->getCode() == no) {  // found
      
      siPtr->setName( retString );
      return;

    }
  }

  std::cerr << "Cannot find in Configure::SetProgramModelNameFromCode\n";
  
  exit(1);
}

      
