/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNsolveDirichlet_CHECK.cpp
 *  Date     : 2002/02/04
 *  Modified : 2002/03/22 Geometry check
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

#include "SNsolveDirichlet.hpp"

#include "feelfuncs.hpp"
#include "GeometryObject.hpp"

#include "../../check/check_funcs.hpp"

int SNsolveDirichlet::VariableDefinedCheck_Dirichlet(list <string>&unknownLst)
{
  int ret;
  ret = 0;

  // check unknown variable is used or not.
  if(!unknownLst.includes(varName)) {
    SystemErrorStrA((SNunit *)this,varName," is not unknown variable.");
    ret++;
  }

  // check right hand side consists of valid variables
  ret += dExprPtr->checkDefinedVariable_DirichletSN((SNunit *)this,unknownLst);

  return(ret);
}

int SNsolveDirichlet::GeometryCheck()
{
  int errors = 0;
  
  // 
  for(int i=0;i<dBoundaryLst->GetNumberOfElements();i++) {
    string nm = (*dBoundaryLst)[i]->GetName();

    if( feelfemgeomobj.IsUsedName(nm) == NO) {
      SystemErrorStrA(this,nm," is undefined geometry name.");
      errors++;
      continue;
    }
    //  int type = feelfemgeomobj.GetGeomTypeByName( nm );
  }
  
  return(errors);
}
  
