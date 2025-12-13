/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SolveElement_print.cpp
 *  Date     : 2002/02/01
 *  Modified : 
 *  
 *  Purpose  : error check print
 *  
 */

#include <iostream.h>

#include "SolveElement.hpp"
#include "ElementNodePattern.hpp"

void SolveElement::print(ostream &ost)
{
  ost << "-----------------------------------------------" << endl;
  ost << "[SolveElement]"<<endl;
  ost << "unknowns ";
  listIterator <Variable *> itr(unknownVarPtrLst);
  for(itr.init();!itr;++itr) {
    ost << "  ";
    itr()->print(ost);
  }
  ost << endl;
  
  listIterator <Variable *>itrV(varPtrLst);
  ost << "Used variables ";
  for(itrV.init(); !itrV ; ++itrV) {
    ost << " ";
    itrV()->print(ost);
  }
  ost << endl;
  

  ost << "ElementNodePattern (SolveElement)" << endl;
  seENPPtr->print(ost);

  ost << "-----------------------------------------------" << endl;

  return;
}
  
