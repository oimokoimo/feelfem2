/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNconstVar.cpp
 *  Date     : 2001/03/29
 *  Modified : 
 *  
 *  Purpose  : create Variable poconster
 *  
 */

#include "../../class/Variable.hpp"
#include "SNconstVar.hpp"

SNconstVar::SNconstVar( char *nm, Expression *ptr) 
  : SNunit("constVar",SN_CONSTVAR) 
{
    name           = nm ;
    initialExprPtr = ptr;
    return;
}

Variable * SNconstVar::CreateVariablePtr(void)
{
  Variable *newVarPtr = new Variable(name,VAR_CONST);

  newVarPtr->SetInitialValue(initialValue);

  return( newVarPtr );
}

