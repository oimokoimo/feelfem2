/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNweqTerms_Infogenerate.cpp
 *  Date     : 2002/01/31
 *  Modified : 
 *  
 *  Purpose  : check routines
 *  
 *             
 */

#include "SNweqTerms.hpp"

void SNweqTerms::AddVariablePtr_Regional(SolveElement *sePtr,
					 list <string>&testFuncLst)
{
  listIterator<SNweqTerm *>itr(weqTermPtrLst);

  for(itr.init();!itr;++itr) {
    itr()->AddVariablePtr_Regional(sePtr,testFuncLst);
  }
  return;
}

void SNweqTerms::ListUpQuadrature_Regional(list <string>&quadNameLst)
{
  listIterator<SNweqTerm *>itr(weqTermPtrLst);

  for(itr.init();!itr;++itr) {
    itr()->ListUpQuadrature_Regional( quadNameLst );
  }
  return;
}

void SNweqTerms::AddVariablePtr_Boundary(Neumann *nPtr,
					 list <string>&testFuncLst,
					 list <string>&nTVarLst)
{
  listIterator<SNweqTerm *>itr(weqTermPtrLst);

  for(itr.init();!itr;++itr) {
    itr()->AddVariablePtr_Boundary(nPtr,testFuncLst,nTVarLst);
  }
  return;
}
