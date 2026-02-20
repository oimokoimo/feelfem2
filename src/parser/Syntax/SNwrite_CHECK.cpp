/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNwrite_CHECK.cpp
 *  Date     : 2002/11/22
 *  Modified : 
 *  
 *  Purpose  : check write statement
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

#include "SNwrite.hpp"
#include "list.hpp"

#include "SNunit.hpp"
#include "SNstring.hpp"
#include "SNexpr.hpp"

int SNwrite::checkItems()
{
  int errors = 0;
  listIterator <SNunit *>itr( writeSNunitPtrLst );
  for(itr.init(); !itr ; ++itr){

    switch(itr()->GetType()) {
    case SN_STRING:
      break;

    case SN_EXPR:
      SNexpr *ptr = (SNexpr *)itr();
      errors += ptr->checkOnlyGlobalScalar();
      break;
    }
  }
  return(errors);
}



