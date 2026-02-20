/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNweqTerms_CHECK.cpp
 *  Date     : 2002/01/29
 *  Modified : 
 *  
 *  Purpose  : check routines
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
 *             
 */

#include "SNweqTerms.hpp"

int SNweqTerms::VariableDefinedCheck_Regional(list <string>&testFuncLst)
{
  int ret;

  listIterator<SNweqTerm *>itr(weqTermPtrLst);
  ret = 0;

  for(itr.init();!itr;++itr) {
    ret+= itr()->VariableDefinedCheck_Regional(testFuncLst);
  }
  return(ret);
}

int SNweqTerms::VariableDefinedCheck_Boundary(list <string>&tLst,
					      SNsolveNeumann *snSNPtr,
					      list <string>&apLst)
{
  int ret;

  listIterator<SNweqTerm *>itr(weqTermPtrLst);
  ret = 0;

  for(itr.init();!itr;++itr) {
    ret+= itr()->VariableDefinedCheck_Boundary(tLst,snSNPtr,apLst);
  }
  return(ret);
}


int SNweqTerms::EtypeConsistencyCheck(int refEtype,
				      list <string>&testFuncLst,
				      list <string>&nVarLst)
{
  int ret;

  listIterator<SNweqTerm *>itr(weqTermPtrLst);
  ret = 0;

  for(itr.init();!itr;++itr) {
    ret+= itr()->EtypeConsistencyCheck(refEtype,testFuncLst,nVarLst);
  }

  return(ret);
}

int SNweqTerms::QuadratureConsistencyCheck(int refEtype,list <string>&tLst,
					   Quadrature *qPtr)
{
  int ret;

  listIterator<SNweqTerm *>itr(weqTermPtrLst);
  ret = 0;

  for(itr.init();!itr;++itr) {
    ret+= itr()->QuadratureConsistencyCheck(refEtype,tLst,qPtr);
  }
  return(ret);
}



    
