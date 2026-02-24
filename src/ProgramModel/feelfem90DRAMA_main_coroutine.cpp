/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : feelfem90DRAMA_main_coroutine.cpp
 *  Date     : 2002/09/03
 *  Modified : 
 *  
 *  Purpose  : co routine for main program
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

#include "feeldef.hpp"
#include "PM_feelfem90DRAMA.hpp"
#include "Object.hpp"
#include "feelfuncs.hpp"
#include "Main.hpp"

void PM_feelfem90DRAMA::GenerateMainCoRoutine(Main *mainPtr)
{

  if(feelfemobj.HowManyMaterialVars() > 0 ) {
    GenerateMaterialVarInitializeRoutine();
  }

  return;
}

void PM_feelfem90DRAMA::GenerateMaterialVarInitializeRoutine(void)
{
  char  hereRoutineName[BUFSIZ];
  const char *hereSourceName;

  sprintf(hereRoutineName,"initmatvar%c",'\0');
  hereSourceName = GetSourceName(hereRoutineName);
  OpenSource(hereSourceName,LINKLEVEL_COROUTINE_MAIN);  // main coroutine

  pushSource("module mod_initmatvar");
  pushSource("contains");
  com();

  pushSource("subroutine ");
  pushSource(hereRoutineName);
  pushSource("(meshDat,firstEdatPtr,matData");
  listIterator <Variable *>itrMatV(feelfemobj.GetMaterialVarList());
  for(itrMatV.init(); !itrMatV ; ++itrMatV ){
    pushSource(",");
    pushVariableNameInMain( itrMatV() );
  }
  pushSource(")");
  flushSource();








  CloseSource();
  return;
}



