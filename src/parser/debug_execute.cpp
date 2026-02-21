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

#include <iostream>
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
  std::cout << "\n[MESH BLOCK (display mesh parse list)]\n";
  for(itrMesh.init(); !itrMesh; ++itrMesh) {
    i++;
    std::cout << "No." << i <<": ";
    ((SNunit *)itrMesh())->print(std::cout);
    std::cout << "\n";
  }


  // var parse tree
  listIterator <void *>itrVar(parseVarLst);
  i = 0;
  std::cout << "\n[VAR BLOCK]\n";
  for(itrVar.init(); !itrVar; ++itrVar) {
    i++;
    std::cout << "No." << i <<": ";
    ((SNunit *)itrVar())->print(std::cout);
    std::cout << "\n";
  }


  //  listIterator <void *>itrScheme(parseSchemeLst);
  //  i = 0;
  //  std::cout << "\n[SCHEME BLOCK]\n";
  //  for(itrScheme.init(); !itrScheme; ++itrScheme) {
  //    i++;
  //    cout << "No." << i <<": ";
  //    ((SNunit *)itrScheme())->print(std::cout);
  //    std::cout << "\n";
  //  }
}

