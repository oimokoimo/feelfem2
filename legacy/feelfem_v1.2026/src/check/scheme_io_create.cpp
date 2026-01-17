/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : scheme_io_create.cpp
 *  Date     : 2002/04/23 (BCN)
 *  Modified : 
 *  
 *  Purpose  :
 *  
 */

#include <iostream.h>

#include "feeldef.hpp"
#include "check_funcs.hpp"

#include "parseExternals.hpp"       // for parser  trees

#include "../parser/Syntax/SNunit.hpp"
#include "../parser/Syntax/SNperspect.hpp"
#include "../parser/Syntax/SNoutput.hpp"



int scheme_io_create(list <void *>&parseSchemeLst)
{
  int ret,errors;

  errors = 0;

  listIterator <void *>itr(parseSchemeLst);
  for(itr.init(); !itr ; ++itr) {

    SNunit *uPtr =(SNunit *)itr();

    switch(uPtr->GetType()) {


    case SN_PERSPECT:
    case SN_OUTPUT:
      errors += uPtr->InfoGenerate();
      break;


    default:
      break;
    }
  }
  return(errors);
}
