/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : TermConvert_print.cpp
 *  Date     : 2002/02/18
 *  Modified : 
 *  
 *  Purpose  : error check 
 *  
 */

#include <iostream.h>
#include "TermConvert.hpp"

void TermConvert::rev_print(ostream &ost)
{
  reverseTC->print(ost);
  return;
}

void TermConvert::print(ostream &ost)
{

  listIterator<StrStrPair *>itr(ssPairPtrLst);

  ost << "TermConvert list============" << endl;

  int length = ssPairPtrLst.getNumberOfElements();
  ost << "pair lists = "<< length << endl;

  int no = 0;
  for(itr.init(); !itr ; ++itr) {

    no++;
    ost << "No." << no<< "  ";

    itr()->print(ost);
    
    ost << endl;
  }

  ost << "==================" << endl;
  return;
}

