/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : debug_execute.cpp
 *  Date     : 2001/02/19
 *  Modified : 
 *  
 *  Purpose  : check writer
 *  
 */

#include "../class/list.hpp"
#include "Syntax/SNname.hpp"
#include "Syntax/SNprogramModel.hpp"

#include "../class/parseExternals.hpp"

void debug_execute( void )
		    
{
  int i;

  // mesh parse tree
  listIterator <void *>itrMesh(parseMeshLst);
  i = 0;
  cout << "\n[MESH BLOCK (display mesh parse list)]\n";
  for(itrMesh.init(); !itrMesh; ++itrMesh) {
    i++;
    cout << "No." << i <<": ";
    ((SNunit *)itrMesh())->print(cout);
    cout << "\n";
  }


  // var parse tree
  listIterator <void *>itrVar(parseVarLst);
  i = 0;
  cout << "\n[VAR BLOCK]\n";
  for(itrVar.init(); !itrVar; ++itrVar) {
    i++;
    cout << "No." << i <<": ";
    ((SNunit *)itrVar())->print(cout);
    cout << "\n";
  }


  //  listIterator <void *>itrScheme(parseSchemeLst);
  //  i = 0;
  //  cout << "\n[SCHEME BLOCK]\n";
  //  for(itrScheme.init(); !itrScheme; ++itrScheme) {
  //    i++;
  //    cout << "No." << i <<": ";
  //    ((SNunit *)itrScheme())->print(cout);
  //    cout << "\n";
  //  }
}

