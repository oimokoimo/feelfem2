/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : scheme_write_check.cpp
 *  Date     : 2002/11/22
 *  Modified : 
 *  
 *  Purpose  :
 *  
 */

#include <iostream.h>
#include "feelfem.hpp"              // for command options
#include "feelfuncs.hpp"
#include "check_funcs.hpp"          // for error messages

#include "parseExternals.hpp"       // for parser  trees

#include "../parser/Syntax/SNunit.hpp"
#include "../parser/Syntax/SNwrite.hpp"


int scheme_write_check(list <void *>&parseSchemeLst)
{
  int ret,errors;

  errors = 0;

  listIterator <void *>itr(parseSchemeLst);
  for(itr.init(); !itr ; ++itr) {
    SNwrite *snPtr;
    SNunit *uPtr =(SNunit *)itr();
    switch(uPtr->GetType()) {

    case SN_WRITE:
      snPtr = (SNwrite *)uPtr;
      errors += snPtr->checkItems();
      break;

    default:
      break;
    }
  }
  return(errors);
}
