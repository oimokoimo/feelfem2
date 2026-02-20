/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNsolveNeumann_CHECK.cpp
 *  Date     : 2002/02/04
 *  Modified : 
 *  
 *  Purpose  : VariableDefinedCheck_NeumannData
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
#include "feelfuncs.hpp"
#include "Object.hpp"
#include "GeometryObject.hpp"

#include "SNsolveNeumann.hpp"

#include "../../check/check_funcs.hpp"

// only check Neumann data
int SNsolveNeumann::VariableDefinedCheck_NeumannData(void)
{
  int ret;
  ret = 0;

  // check neumann temporary variable is not declared
  listIterator <string> itrNT(nPairsPtr->neumannArgumentLst);
  for(itrNT.init(); !itrNT ; ++itrNT ) {
    if(feelfemobj.IsDefinedVariable( itrNT() ) == YES) {
      ret++;
      string err; err  = itrNT();
      SystemErrorAStrA((SNunit *)this,"Used variable '", err,
		       "' cannot be a neumann temporary variable.");
    }
  }

  // check neumann expression data
  listIterator <Expression *>itr(nPairsPtr->neumannExpressionLst);
  for(itr.init(); !itr ; ++itr ) {
    ret += itr()->checkDefinedVariable_NeumannDataSN((SNunit *)this,
 			     nPairsPtr->neumannArgumentLst);
  }

  return(ret);
}

int SNsolveNeumann::IsTemporaryVariable(string &nm)
{
  if(nPairsPtr->neumannArgumentLst.includes(nm)) return(YES);
  else return(NO);
}

void SNsolveNeumann::AddTVarStrToList(list <string> &nLst)
{
  listIterator <string> itrNT(nPairsPtr->neumannArgumentLst);
  for(itrNT.init(); !itrNT ; ++itrNT ) {
    string addName; 
    addName  = itrNT();
      
    if(!nLst.includes(addName)) {
      nLst.add(addName);
    }
  }
  
  return;
}

// check all neumann temporary variables are used.
int SNsolveNeumann::CheckAllNTVarsAreUsed( list<string>&appearedVarLst)
{
  int ret;
  ret = 0;

  listIterator <string> itrNT(nPairsPtr->neumannArgumentLst);
  for(itrNT.init(); !itrNT ; ++itrNT ) {
    string nm; 
    nm = itrNT();
    
    if(appearedVarLst.includes(nm)) continue;

    ret++;
    SystemErrorAStrA((SNunit*)this,"Neumann temporary var '",nm,"' is not used.");
  }

  return(ret);
}

int SNsolveNeumann::GeometryCheck()
{
  int errors = 0;
  
  // 
  for(int i=0;i<nBoundaryLst->GetNumberOfElements();i++) {
    string nm = (*nBoundaryLst)[i]->GetName();

    if( feelfemgeomobj.IsUsedName(nm) == NO) {
      SystemErrorStrA(this,nm," is an undefined geometry name.");
      errors++;
      continue;
    }
    int type = feelfemgeomobj.GetGeomObjTypeByName( nm );

    if( feelfemgeomobj.IsValidNeumannBoundary(type) == YES) continue;
    
    errors++;
    SystemErrorStrA(this,nm, " is not a valid Neumann type boundary.");
  }
  return(errors);
}
