/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999,2000
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : MainOperation.cpp
 *  Date     : 2000/04/25
 *  Modified : 2000/04/25
 *  
 *  Purpose  : Functions on Main class
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

#include "Main.hpp"
#include "Procedure.hpp"

#include "feelfuncs.hpp"
#include "Object.hpp"

Main::Main()
{
  programModelType = feelfemproc.GetProgramModel();

  // make variable list
  feelfemobj.MakeVarLstForMain( this );

  return;
}



Main::~Main()
{
  // do nothing;
  return;
}


void Main::AddVariablePtr( Variable *vPtr )
{
  if(mainVarPtrLst.includes(vPtr)) return;

  mainVarPtrLst.add(vPtr);
 
  return;
}


//void Main::AddScheme( Scheme *schemePtr)
//{
// schemePtrLst.addlast(schemePtr);
//
//  return;
//}
