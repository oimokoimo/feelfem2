/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNweqTerms.cpp
 *  Date     : 2001/07/19
 *  Modified : 
 *  
 *  Purpose  :
 *  
 */
#include <iostream.h>

#include "feeldef.hpp"
#include "SNweqTerms.hpp"

void SNweqTerms::print(ostream &ost)
{
  listIterator<int>        itrF(weqTermFlagLst);
  listIterator<SNweqTerm *>itrT(weqTermPtrLst);

  itrF.init();
  int first = 0;

  for(itrT.init();!itrT;++itrT) {

    if(itrF() == -1) {
      ost << "-";
    }
    else {
      if(first != 0) {
	ost << "+";
      }
      first = 1;
    }
    itrT()->print(ost);
    
    ++itrF;
  }
  return;
}

int SNweqTerms::HasBoundaryTerm(void)
{

  listIterator<SNweqTerm *>itr(weqTermPtrLst);

  for(itr.init();!itr;++itr) {
    if(itr()->IsBoundaryTerm() == YES) return(YES);
  }

  return(NO);
}

