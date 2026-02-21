/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : var_create.cpp
 *  Date     : 2001/03/29
 *  Modified : 
 *  
 *  Purpose  :
 *  
 */


#include "../parser/Syntax/SNunit.hpp"
#include "../parser/Syntax/SNfemVar.hpp"
#include "../parser/Syntax/SNewiseVar.hpp"
#include "../parser/Syntax/SNconstVar.hpp"
#include "../parser/Syntax/SNdoubleVar.hpp"
#include "../parser/Syntax/SNintVar.hpp"

#include "feelfuncs.hpp"
#include "Object.hpp"
#include "Variable.hpp"

int var_create(list <void *>&parseVariableLst)
{

  listIterator <void *>itr(parseVariableLst);
  for(itr.init(); !itr ; ++itr) {
    Variable *newVarPtr;
    SNunit *uPtr =(SNunit *)itr();

    if(uPtr->GetType() == SN_FUNCTIONDEF) continue;  // function def

    newVarPtr = uPtr->CreateVariablePtr();
    feelfemobj.StoreVariable( newVarPtr );
  }

  return(0);
}
