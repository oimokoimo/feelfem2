/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNdoubleVar.cpp
 *  Date     : 2001/03/29
 *  Modified : 
 *  
 *  Purpose  : create Variable pointer
 *  
 */

#include "feelfuncs.hpp"
#include "Object.hpp"

#include "Variable.hpp"
#include "SNdoubleVar.hpp"

Variable * SNdoubleVar::CreateVariablePtr(void)
{
  Variable *newVarPtr = new Variable(name,VAR_DOUBLE);

  if(initialExprPtr != 0) {
    feelfemobj.StoreInitialDouble(newVarPtr);
    newVarPtr->SetInitialFlag();
    newVarPtr->SetInitialValue(initialValue);
  }

  return( newVarPtr );
}
