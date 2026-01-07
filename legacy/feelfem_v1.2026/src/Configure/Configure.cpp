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
 */

#include "feeldef.hpp"
#include "Configure.hpp"
#include <stdlib.h>        // for exit(1);

void Configure::StorePM_LIB(const char *pgName,const char *libName,int type)
{
  StrStrIntPair *pg_libPairPtr = new StrStrIntPair( pgName, libName , type);
  
  if(pglibPairLst.includes( pg_libPairPtr ) ) {
    cerr << "PG-LIB pair " << pgName << " and " << libName << " [type=";
    cerr << type <<"] is multiply registered.\n";
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
    cerr << "PG-LIB pair " << pgName << " and " << libName;
    cerr << " is multiply registered.\n";
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
    cerr << "program model name " << pgName << " multiply registered.\n";
    cerr << "Configure::StoreProgramModelNames\n";
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

  cerr << "Cannot find in Configure::SetProgramModelNameFromCode\n";
  
  exit(1);
}

      
