/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : TermConvert_ewise.cpp
 *  Date     : 2002/07/23
 *  Modified : 
 *  
 *  Purpose  : TermConvert series for ewise-quad evaluation formulas
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

#include "EwiseQuadTC.hpp"

// for user function exchange symbol tables
#include "Object.hpp"
#include "Function.hpp"
#include "feelfuncs.hpp"

//  Make TermConvert data for **all known** variable,
//  evaluated at each quadrature point.
//
//
//

void EwiseQuadTC::AddVariable(Variable *vPtr)
{
  StoreVariableList( vPtr );

  switch(vPtr->GetType()) {
  case VAR_FEM:
  case VAR_VFEM:

    AddVariableFEM( vPtr );
    break;
    

  case VAR_EWISE_A:
    if(vPtr->GetEwiseType() == EWISE_TYPE_GAUSSPOINT) {
      AddVariableEWISEquad( vPtr );
    }
    else {
      AddVariableFEM( vPtr );
    }
    break;

  case VAR_EWISE:
    AddVariableEWISEmaterial( vPtr );
    break;
    
  case VAR_DOUBLE:
  case VAR_INT:
  case VAR_CONST:
    AddVariableScalar( vPtr );
    break;

  case VAR_MATERIAL:
    AddVariableMaterial( vPtr );
    break;

  default:
    assert(1==0);
  }

  return;
}

void EwiseQuadTC::AddVariableFEM( Variable *vPtr)
{
  // set startingFuncNo
  
  char buf[BUFSIZ];
  sprintf(buf,"_n%d(x,y,z)%c",startingFuncNo,'\0');
  vPtr->SetFunctionTCNo( startingFuncNo);
  startingFuncNo++;

  storeConvertPair( vPtr->GetName(), buf );
  
  return;
}

void EwiseQuadTC::ReverseAddVariableFEM( Variable *vPtr)
{
  // set startingSblNo
  int funcNo;
  funcNo = vPtr->GetFunctionTCNo();

  char nbuf[BUFSIZ],buf[BUFSIZ];

  // function itself
  sprintf(nbuf,"_n%d%c",funcNo,'\0');
  // to fem_, ew_ etc.
  switch(vPtr->GetType()) {
  case VAR_FEM:
    sprintf(buf,"qfem_%s%c",vPtr->GetName(),'\0');
    break;

  case VAR_VFEM:
    sprintf(buf,"qvfem_%s%c",vPtr->GetName(),'\0');
    break;

  case VAR_EWISE_A:
    sprintf(buf,"qew_%s%c",vPtr->GetName(),'\0');
    break;

  default:
    assert(1==0);
  }
  reverseTC->storeConvertPair( nbuf,buf );


  //  X derivative
  sprintf(nbuf,"_n%d_dx%c",funcNo,'\0');
  // to fem_, ew_ etc.
  switch(vPtr->GetType()) {
  case VAR_FEM:
    sprintf(buf,"qfem_%s_x%c",vPtr->GetName(),'\0');
    break;

  case VAR_VFEM:
    sprintf(buf,"qvfem_%s_x%c",vPtr->GetName(),'\0');
    break;

  case VAR_EWISE_A:
    sprintf(buf,"qew_%s_x%c",vPtr->GetName(),'\0');
    break;

  default:
    assert(1==0);
  }
  reverseTC->storeConvertPair( nbuf,buf );


  //  Y derivative
  sprintf(nbuf,"_n%d_dy%c",funcNo,'\0');
  // to fem_, ew_ etc.
  switch(vPtr->GetType()) {
  case VAR_FEM:
    sprintf(buf,"qfem_%s_y%c",vPtr->GetName(),'\0');
    break;

  case VAR_VFEM:
    sprintf(buf,"qvfem_%s_y%c",vPtr->GetName(),'\0');
    break;

  case VAR_EWISE_A:
    sprintf(buf,"qew_%s_y%c",vPtr->GetName(),'\0');
    break;

  default:
    assert(1==0);
  }
  reverseTC->storeConvertPair( nbuf,buf );

  //  z derivative
  sprintf(nbuf,"_n%d_dz%c",funcNo,'\0');
  // to fem_, ew_ etc.
  switch(vPtr->GetType()) {
  case VAR_FEM:
    sprintf(buf,"qfem_%s_z%c",vPtr->GetName(),'\0');
    break;

  case VAR_VFEM:
    sprintf(buf,"qvfem_%s_z%c",vPtr->GetName(),'\0');
    break;

  case VAR_EWISE_A:
    sprintf(buf,"qew_%s_z%c",vPtr->GetName(),'\0');
    break;

  default:
    assert(1==0);
  }
  reverseTC->storeConvertPair( nbuf,buf );

  return;
}

void EwiseQuadTC::AddUserFunctionSymbol(void)
{
  listIterator <Function *>itr(feelfemobj.GetUserFunctionList());

  char buf[BUFSIZ];
  char nbuf[BUFSIZ];
  for(itr.init();!itr;++itr) {
    Function *ptr = itr();

    sprintf( buf,"%s%c",ptr->GetName(),'\0');
    sprintf(nbuf,"_fn%d",ptr->GetFunctionTCno());

    // in order to ignore  (for making converted identifer list)
    StoreIgnoreSymbolLstForConvertedStrLst( buf );

    storeConvertPair(buf,nbuf);
    reverseTC->storeConvertPair( nbuf,buf );
  }
  return;
}
  
