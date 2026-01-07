/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : geometry_scheme_elementEtype_create.cpp
 *  Date     : 2002/11/07
 *  Modified : 
 *  
 *  Purpose  :
 *  
 */

#include <iostream.h>

#include "feeldef.hpp"
#include "feelfem.hpp"              // for command options
#include "feelfuncs.hpp"
#include "check_funcs.hpp"          // for error messages

#include "parseExternals.hpp"       // for parser  trees


#include "../parser/Syntax/SNunit.hpp"
#include "../parser/Syntax/SNelementType.hpp"



void scheme_elementType_create(list <void *>&parseSchemeLst)
{
  int ret; // no use

  listIterator <void *>itr(parseSchemeLst);
  for(itr.init(); !itr ; ++itr) {

    SNunit *uPtr =(SNunit *)itr();

    switch(uPtr->GetType()) {
    case SN_ELEMENTTYPE:
      ret = ((SNelementType *)uPtr)->InfoGenerate();

      break;

    default:
      break;
    }
  }
  return;
}
