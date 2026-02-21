/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : scheme_label_create.cpp
 *  Date     : 2002/07/18
 *  Modified : 
 *  
 *  Purpose  :
 *
 *
 *  feelfem2 (modernized/ported)
 *  Copyright (C) 2025-2026 Hidehiro Fujio and contributors
 *  SPDX-License-Identifier: BSD-3-Clause
 *  Repository: https://github.com/oimokoimo/feelfem2
 *
 *
 *  Notes:
 *  
 */

#include "feelfem.hpp"              // for command options
#include "check_funcs.hpp"          // for error messages

#include "parseExternals.hpp"       // for parser  treesn


#include "../parser/Syntax/SNunit.hpp"
#include "../parser/Syntax/SNlabel.hpp"
#include "../parser/Syntax/SNif.hpp"

int scheme_label_if_create(list <void *>&parseSchemeLst)
{
  int ret,errors;

  errors = 0;

  listIterator <void *>itr(parseSchemeLst);

  // label InfoGenerate
  for(itr.init(); !itr ; ++itr) {

    SNunit *suPtr =(SNunit *)itr();

    switch(suPtr->GetType()) {

    case SN_LABEL:
      errors += suPtr->InfoGenerate();
      break;

    default:
      break;
    }
  }

  // if  InfoGenerate
  for(itr.init(); !itr ; ++itr) {

    SNunit *suPtr =(SNunit *)itr();

    switch(suPtr->GetType()) {

    case SN_IF:
      errors += suPtr->InfoGenerate();
      break;

    default:
      break;
    }
  }

  return(errors);
}
