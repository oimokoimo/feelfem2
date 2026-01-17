/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : scheme_pm_check.cpp
 *  Date     : 2001/10/26
 *  Modified : 
 *  
 *  Purpose  : program model check
 *  
 */

#include <iostream.h>
#include "feelfem.hpp"              // for command options
#include "feelfuncs.hpp"
#include "check_funcs.hpp"          // for error messages

#include "parseExternals.hpp"       // for parser  trees


#include "../parser/Syntax/SNunit.hpp"
#include "../parser/Syntax/SNprogramModel.hpp"



static int check_pm(SNprogramModel *snProgramModelPtr)
{
  if(snProgramModelPtr->IsDefinedProgramModelName()) {

    snProgramModelPtr->set_feelfemproc();

    return( 0 );  // name is defined, no error
  }
  else {

    SystemErrorNameA((SNunit *)snProgramModelPtr,
		     " is not valid ProgramModel name.");

    return( 1 );  // name is undefined, error
  }
  
}


int scheme_pm_check(list <void *>&parseSchemeLst)
{
  int ret,errors;

  int pm_sentences;

  errors = 0;
  pm_sentences = 0;   // programModel must be only one.

  listIterator <void *>itr(parseSchemeLst);
  for(itr.init(); !itr ; ++itr) {

    SNunit *uPtr =(SNunit *)itr();

    switch(uPtr->GetType()) {
    case SN_PROGRAMMODEL:
      pm_sentences++;
      
      if(pm_sentences != 1) {
	SystemErrorA(uPtr,"another ProgramModel statement is found.");
	errors++;
      }
      ret = check_pm( (SNprogramModel *)(itr()) );  // function in the top
      errors += ret;

      break;

    default:
      break;
    }

  }



  return(errors);
}
