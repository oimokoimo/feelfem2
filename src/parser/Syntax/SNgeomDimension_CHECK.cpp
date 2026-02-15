/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNgeomDimension_Check.cpp
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

#include "../../check/check_funcs.hpp"
#include "Object.hpp"

#include "SNunit.hpp"
#include "SNgeomDimension.hpp"

int SNgeomDimension::Check()
{
  if(dim < 2 || dim >3) {
    SystemErrorA((SNunit *)this,"Dimension error.");
    return(1); // error
  }

  int currentDimension = feelfemobj.GetSpaceDimension();
  
  feelfemobj.SetSpaceDimension( dim );
  return(0);   // no error
}

