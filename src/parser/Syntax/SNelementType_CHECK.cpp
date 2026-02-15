/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNelementType_CHECK.cpp
 *  Date     : 2002/11/06
 *  Modified : 
 *  
 *  Purpose  : check specified identifiers are element type name
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

#include "SNelementType.hpp"
#include "../../check/check_funcs.hpp"

int SNelementType::IsValidElementTypeName(void)
{
  int errors = 0;
  
  int components = etypeIdentifierLst->GetNumberOfElements();
  for(int i=0;i<components;i++) {
    SNname *snnPtr;

    snnPtr     = (*etypeIdentifierLst)[i];
    string str = snnPtr->GetName();

    if(!isEtypeName( str )) {

      SystemErrorStrA(this,str," is not a valid element type name.");
      errors++;

    }
  }

  return(errors);
}

