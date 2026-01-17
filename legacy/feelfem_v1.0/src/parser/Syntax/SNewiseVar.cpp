/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNewiseVar.cpp
 *  Date     : 2001/03/29
 *  Modified : 
 *  
 *  Purpose  : create Variable poewiseer
 *  
 */

#include "Variable.hpp"
#include "SNewiseVar.hpp"

Variable * SNewiseVar::CreateVariablePtr(void)
{
  Variable *newVarPtr;
  if(isAttribute == YES) {
    newVarPtr = new Variable(name,VAR_EWISE_A);
    newVarPtr->SetFunctionName(attributeName);
    newVarPtr->SetParameters();
  }
  else {
    newVarPtr = new Variable(name,VAR_EWISE);
    newVarPtr->SetParameters();    
  }
  return( newVarPtr );

}

