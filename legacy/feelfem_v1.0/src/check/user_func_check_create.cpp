/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : user_func_check_create.cpp
 *  Date     : 2002/09/13
 *  Modified : 2002/09/17  check number of argumens in formulas
 *  
 *  Purpose  :
 *  
 */

#include <iostream.h>
#include <assert.h>

#include "list.hpp"
#include "string.hpp"
#include "feelfuncs.hpp"

#include "check_funcs.hpp"

#include "../parser/Syntax/SNunit.hpp"
#include "../parser/Syntax/SNfunctionDef.hpp"

#include "../parser/Syntax/SNfunction.hpp"  // this is one of expression 
                                            // components


int user_func_check_create( list <void *>&parseVarLst)
{
  int errors,ret;
  list <string> checkConflict;

  errors    = 0;

  int funcs_arg1 = 0;
  int funcs_arg2 = 0;
  int funcs_arg3 = 0;
  
  listIterator <void *>itrVar(parseVarLst);
  for(itrVar.init(); !itrVar; ++itrVar) {
 
    if(((SNunit *)itrVar())->GetType() != SN_FUNCTIONDEF) continue;
    
    SNfunctionDef *ptr = (SNfunctionDef *)itrVar();

    if(ptr->Check()) errors++;

    // check number of functions for each arguments no.  (ginac)
    switch(ptr->GetNumberOfArgs()) {
    case 1:
      funcs_arg1++;
      break;

    case 2:
      funcs_arg2++;
      break;

    case 3:
      funcs_arg3++;
      break;

    default:
      SystemErrorANameA((SNunit*)itrVar(),"function ",
			 " has an illegal number of arguments.");
      errors++;
    }

    if(ptr->isAlreadyUsedName(checkConflict)) {
      SystemErrorANameA((SNunit*)itrVar(),"function "," is already declared.");
      errors++; 
    }
    
  }
  // check number of user functions for each arguments
  if( funcs_arg1 > MAX_USER_FUNCTIONS1) {
    SystemError_A("Too Many user functions having 1 argument.");
    errors++;
  }
  if( funcs_arg2 > MAX_USER_FUNCTIONS2) {
    SystemError_A("Too Many user functions having 2 arguments.");
    errors++;
  }
  if( funcs_arg3 > MAX_USER_FUNCTIONS3) {
    SystemError_A("Too Many user functions having 3 arguments.");
    errors++;
  }

  if(errors) return(errors);       // if there is an error, just return


  // Create function definition
  for(itrVar.init(); !itrVar; ++itrVar) {
 
    if(((SNunit *)itrVar())->GetType() != SN_FUNCTIONDEF) continue;

    SNfunctionDef *ptr = (SNfunctionDef *)itrVar();

    int ret;
    ret = ptr->InfoGenerate();
  }
  return(0);

}
