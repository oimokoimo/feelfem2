/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : var_check_conflict.cpp
 *  Date     : 2001/03/26
 *  Modified : 
 *  
 *  Purpose  : name conflict check
 *  
 */

#include <stream.h>

#include "list.hpp"
#include "string.hpp"
#include "feelfuncs.hpp"

#include "check_funcs.hpp"

#include "../parser/Syntax/SNunit.hpp"


int var_check_conflict( list <void *>&parseVarLst )
{
  listIterator <void *>itrVar(parseVarLst);
  list <string> checkConflict;

  int errors;

  errors    = 0;
  
  for(itrVar.init(); !itrVar; ++itrVar) {

    if(((SNunit *)itrVar())->GetType() == SN_FUNCTIONDEF) continue;

    if(((SNunit *)itrVar())->isAlreadyUsedName(checkConflict)) {
      SystemErrorANameA((SNunit*)itrVar(),"Variable "," is already declared.");
      errors++;
    }
  }
  checkConflict.deleteAllValues();
  return(errors);
}
