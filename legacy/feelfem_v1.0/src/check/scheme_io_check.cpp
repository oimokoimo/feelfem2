/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : scheme_io_check.cpp
 *  Date     : 2002/01/21
 *  Modified : 
 *  
 *  Purpose  : io related routine check
 *  
 */
#include <iostream.h>

#include "feeldef.hpp"
#include "check_funcs.hpp"

#include "parseExternals.hpp"       // for parser  trees

#include "../parser/Syntax/SNunit.hpp"
#include "../parser/Syntax/SNperspect.hpp"
#include "../parser/Syntax/SNoutput.hpp"


// output
static int check_output (SNoutput *oPtr)
{
  int errors = 0;

  // variables are defined or not
  errors += oPtr->checkIdentifierWellDefined();

  //  // expression is valid?
  //  errors += oPtr->checkValidExpr();

  // Options are correct
  errors += oPtr->checkOptions();

  return(errors);
}


// perspect
static int check_perspect( SNperspect *pPtr )
{
  int ret;
  
  ret = pPtr->checkExprWellDefined();

  return(ret);
}


int scheme_io_check(list <void *>&parseSchemeLst)
{
  int ret,errors;

  errors = 0;

  listIterator <void *>itr(parseSchemeLst);
  for(itr.init(); !itr ; ++itr) {

    SNunit *uPtr =(SNunit *)itr();

    switch(uPtr->GetType()) {


    case SN_PERSPECT:
      ret = check_perspect( (SNperspect *)itr());
      errors += ret;
      break;


    case SN_OUTPUT:
      ret = check_output( (SNoutput *)itr());
      errors += ret;
      break;


    default:
      break;
    }
  }
  return(errors);
}
