/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNweqTerms_WEAKEQ.cpp
 *  Date     : 2002/01/30
 *  Modified : 2002/03/27 (add boundary part)
 *  
 *  Purpose  :
 *
 *
 *  feelfem2 (modernized/ported)
 *  Copyright (C) 2025-2026 Hidehiro Fujio and contributors
 *  SPDX-License-Identifier: BSD-3-Clause
 *  Repository: https://github.com/oimokoimo/feelfem2
 *
 *
 *  Notes:
 *  
 */

#include "SNweqTerms.hpp"

// Regional part
void SNweqTerms::WriteRegionWeakEqStrByQuad(int flag, 
					    string &quadName, 
					    char *exprBUF,int &exprBUFptr,
					    int maxBUFlen)
{
  listIterator <SNweqTerm *>itr(weqTermPtrLst);
  listIterator <int> itrFlag(weqTermFlagLst);

  itrFlag.init();
  for(itr.init();!itr;++itr) {

    itr()->WriteRegionWeqEqStrByQuad( flag * itrFlag(),
				      quadName,
				      exprBUF,exprBUFptr,maxBUFlen);
    ++itrFlag;
  }
  return;
}


void SNweqTerms::MakeRegionIntegrandSetInfoByQuad(string &quadName, 
						  IntegrandSet *isetPtr,
						  list<string> &tLst    )
{
  listIterator <SNweqTerm *>itr(weqTermPtrLst);

  for(itr.init();!itr;++itr) {
    itr()->MakeRegionIntegrandSetInfoByQuad( quadName, isetPtr ,tLst );
  }
  return;
}

// Boundary part
void SNweqTerms::WriteBoundaryWeakEqStr(int flag, 
					char *exprBUF,int &exprBUFptr,
					int maxBUFlen)
{
  listIterator <SNweqTerm *>itr(weqTermPtrLst);
  listIterator <int> itrFlag(weqTermFlagLst);

  itrFlag.init();
  for(itr.init();!itr;++itr) {

    itr()->WriteBoundaryWeqEqStr( flag * itrFlag(),
				  exprBUF,exprBUFptr,maxBUFlen);
    ++itrFlag;
  }
  return;
}

void SNweqTerms::MakeBoundaryIntegrandSetInfo(  BoundaryIntegrandSet *bisetPtr,
						list<string> &tLst    )
{
  listIterator <SNweqTerm *>itr(weqTermPtrLst);

  for(itr.init();!itr;++itr) {
    itr()->MakeBoundaryIntegrandSetInfo( bisetPtr ,tLst );
  }
  return;
}

