/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNgeomRegion_check.cpp
 *  Date     : 2002/03/18
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

#include "SNgeomRegion.hpp"
#include "SNidentifierlist.hpp"
#include "SNname.hpp"

#include "../../check/check_funcs.hpp"

#include "Configure.hpp"
#include "GeometryObject.hpp"
#include "feelfuncs.hpp"
#include "string.hpp"

int SNgeomRegion::Check()
{
  int errors;

  errors = 0;

  for(int i=0;i<identifierLst->GetNumberOfElements(); i++) {
    string nm = (*identifierLst)[i]->GetName();

    int ret;
    ret = feelfemgeomobj.IsUsedName( nm );
    
    if(ret == YES) {
      SystemErrorStrA((SNunit *)this,nm," is used already.");
      errors++;
    }
    else {
      feelfemgeomobj.AddUsedNameLst( nm );
    }
  }

  return(errors);
}
