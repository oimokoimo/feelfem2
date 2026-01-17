/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNintVar.cpp
 *  Date     : 2001/03/29
 *  Modified : 
 *  
 *  Purpose  : create Variable pointer
 *  
 */

#include "feelfuncs.hpp"
#include "Object.hpp"

#include "Variable.hpp"
#include "SNintVar.hpp"

Variable * SNintVar::CreateVariablePtr(void)
{
  Variable *newVarPtr = new Variable(name,VAR_INT);

  if(initialExprPtr != 0) {
    feelfemobj.StoreInitialInteger(newVarPtr);
    newVarPtr->SetInitialFlag();
    newVarPtr->SetIntInitialValue(initialValue);
  }

  return( newVarPtr );
}

