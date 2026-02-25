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

#include <iostream>
#include "TermConvert.hpp"

void TermConvert::rev_print(std::ostream &ost)
{
  reverseTC->print(ost);
  return;
}

void TermConvert::print(std::ostream &ost)
{

  listIterator<StrStrPair *>itr(ssPairPtrLst);

  ost << "TermConvert list============" << std::endl;

  int length = ssPairPtrLst.getNumberOfElements();
  ost << "pair lists = "<< length << std::endl;

  int no = 0;
  for(itr.init(); !itr ; ++itr) {

    no++;
    ost << "No." << no<< "  ";

    itr()->print(ost);
    
    ost << std::endl;
  }

  ost << "==================" << std::endl;
  return;
}

