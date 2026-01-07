/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : Assign_print.cpp
 *  Date     : 2002/04/15 (BCN)
 *  Modified : 
 *   
 *  Purpose  : check write routines for Assign
 *  
 */

#include <iostream.h>

#include "Assign.hpp"

void Assign::print(ostream &ost)
{
  ost << "Assign No." << assignNo <<"  ";
  ost << leftVarPtr->GetName();
  ost << " = ( ";
  listIterator <Variable *>itr(varPtrLst);
  for(itr.init(); !itr ; ++itr) {
    ost << itr()->GetName() << " ";
  }
  ost << ")  [" << expr << "]" << endl;

  return;
}
