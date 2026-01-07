/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : scheme_assign_create.cpp
 *  Date     : 2002/04/15 (BCN)
 *  Modified : 
 *  
 *  Purpose  :
 *  
 */

#include <iostream.h>
#include "feelfem.hpp"              // for command options
#include "check_funcs.hpp"          // for error messages

#include "parseExternals.hpp"       // for parser  treesn


#include "../parser/Syntax/SNunit.hpp"
#include "../parser/Syntax/SNassignment.hpp"


int scheme_assign_create(list <void *>&parseSchemeLst)
{
  int ret,errors;

  errors = 0;

  listIterator <void *>itr(parseSchemeLst);
  for(itr.init(); !itr ; ++itr) {

    SNunit *suPtr =(SNunit *)itr();

    SNassignment *snaPtr;

    switch(suPtr->GetType()) {


    case SN_ASSIGNMENT:

      // confirm all variables appear in expression is defined
      suPtr->InfoGenerate();
      break;

    default:
      break;
    }
  }
  return(errors);
}

    

    
