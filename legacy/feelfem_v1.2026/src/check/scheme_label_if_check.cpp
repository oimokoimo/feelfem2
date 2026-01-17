/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : 
 *  Date     : 2002/07/17
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
#include "../parser/Syntax/SNlabel.hpp"
#include "../parser/Syntax/SNif.hpp"

int scheme_label_if_check(list <void *>&parseSchemeLst)
{
  int ret,errors;

  int pm_sentences;

  errors = 0;

  list <string>labelCheckLst;

  listIterator <void *>itr(parseSchemeLst);
  for(itr.init(); !itr ; ++itr) {
    SNlabel *snPtr;
    SNunit *uPtr =(SNunit *)itr();
    switch(uPtr->GetType()) {

    case SN_LABEL:
      snPtr = (SNlabel *)uPtr;
      errors += snPtr->duplicate_check(labelCheckLst);
      break;

    default:
      break;
    }
  }

  // is defined check for if
  for(itr.init(); !itr ; ++itr) {

    SNunit *uPtr =(SNunit *)itr();
    SNif   *snPtr;
    switch(uPtr->GetType()) {

    case SN_IF:
      snPtr = (SNif *)uPtr;
      errors += snPtr->labelDefined_check(labelCheckLst);
      errors += snPtr->checkValidExpr();
      break;

    default:
      break;
    }
  }

  return(errors);
}

