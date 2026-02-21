/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : element_quadrature_check_conflict.cpp
 *  Date     : 2001/03/27
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

#include "../parser/Syntax/SNunit.hpp"
#include "../parser/Syntax/SNelement.hpp"
#include "../parser/Syntax/SNquadrature.hpp"

#include "check_funcs.hpp"

int element_quadrature_check_conflict(list <void *>&parseElementLst,
				      list <void *>&parseQuadratureLst)
{
  list <string> checkConflict;

  int errors;
  errors = 0;

  listIterator <void *>itr(parseElementLst);
  for(itr.init(); !itr ; ++itr) {
    SNelement *ePtr = (SNelement*)itr();
    if(ePtr->isAlreadyUsedName(checkConflict)) {
      SystemErrorANameA((SNunit *)ePtr,"Name "," is already used.");
      errors++;
    }
  }

  listIterator <void *>itr2(parseQuadratureLst);
  for(itr2.init(); !itr2 ; ++itr2) {
    SNquadrature *qPtr = (SNquadrature*)itr2();
    if(qPtr->isAlreadyUsedName(checkConflict)) {
      SystemErrorANameA((SNunit *)qPtr,"Name "," is already used.");
      errors++;
    }
  }

  return(errors);
}
