/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : ElementNodePattern_print.cpp
 *  Date     : 2002/02/01
 *  Modified : 
 *  
 *  Purpose  : debug routine for ElementNodePattern
 *  
 */
#include <iostream.h>
#include <assert.h>

#include "ElementNodePattern.hpp"

void ElementNodePattern::print(ostream &ost)
{
  ost << "Element node pattern" << endl;
  ost << "FEM variable   " << numberOfFEMVariables << endl;
  ost << "VFEM variable  " << numberOfVFEMVariables << endl;
  ost << "EWISE variable " << numberOfEWISEVariables << endl;
  ost << "nodes = " << nodes << endl;
  ost << "totalFreedom = "<< totalFreedom << endl;
  ost << "ewiseFreedom = "<< ewiseFreedom << endl;
  
  ost << endl;


  listIterator <Node *>itr(nodeOrderedPtrLst);
  int no=0;
  for(itr.init(); !itr; ++itr ) {
    no++;
    ost << "[" << no << "] ";
    itr()->print(ost);
    ost << endl;
  }
  ost << "******\n";

  assert(ienp != 0 && iedp != 0);

  ost << "IENP ";
  for(int i=0;i<totalFreedom;i++) {
    if(i!=0) ost << ",";
    ost << *(ienp+i);
  }
  ost << endl;

  ost << "IEDP ";
  for(int i=0;i<totalFreedom;i++) {
    if(i!=0) ost << ",";
    ost << *(iedp+i);
  }
  ost << endl;
  
  ost << "--------------------------------------------------\n";
  
  return;
}
    

