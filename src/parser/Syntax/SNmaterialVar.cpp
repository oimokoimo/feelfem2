/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNmaterialVar.cpp
 *  Date     : 2002/08/29        (Copy from SNoutput.cpp)
 *  Modified : 
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

#include "string.hpp"
#include "Expression.hpp"

#include "SNmaterialVar.hpp"
#include "SNexprlist.hpp"
#include "SNoption.hpp"

#include "Variable.hpp"

#include "Object.hpp"
#include "feelfuncs.hpp"


SNmaterialVar::SNmaterialVar(const char *nm,stack <SNunit *> &parseOptionStack )
  : SNunit("materialVar",SN_MATERIALVAR)
{
  name = nm;

  // options
  options = 0;

  while( !parseOptionStack.isEmpty()) {
    SNunit   *unitPtr;
    SNoption *optPtr;

    unitPtr = parseOptionStack.pop();
    
    optPtr  = (SNoption *)unitPtr;

    optionLst.add(optPtr);
    options++;
  }
  return;
}


void SNmaterialVar::print(std::ostream &ost)
{
  ost << "material "<< name << " ";
  
  listIterator <SNoption *>itr(optionLst);

  for(itr.init(); !itr ; ++itr) {
    itr()->print(ost);
  }
  ost << std::endl;

  return;
}

Variable * SNmaterialVar::CreateVariablePtr(void)
{
  Variable *newVarPtr;

  newVarPtr = new Variable(name,VAR_MATERIAL);

  feelfemobj.StoreMaterialVar( newVarPtr );

  // set material value properties
  newVarPtr->SetMaterialKinds(pairs);         // allocation will be done here

  listIterator <SNoption *>itrOpt(optionLst);

  int ctr = 0;
  for(itrOpt.init(); !itrOpt ; ++itrOpt ) {
    string      matname = itrOpt()->GetOptionName();
    newVarPtr->SetMaterialValuePair( matname, *(values+ctr));
    ctr++;
  }

  return( newVarPtr );
}

