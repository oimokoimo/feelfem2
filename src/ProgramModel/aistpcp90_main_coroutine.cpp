/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : aistpcp90_main_coroutine.cpp
 *  Date     : 2002/09/30  (copied from feelfem90_main_coroutine)
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
#include "PM_aistpcp90.hpp"
#include "Object.hpp"
#include "GeometryObject.hpp"
#include "RegionObject.hpp"
#include "feelfuncs.hpp"
#include "Main.hpp"

#include "Function.hpp"   // for user function in makefile (02/09/19)

void PM_aistpcp90::GenerateMainCoRoutine(Main *mainPtr)
{

  if(feelfemobj.HowManyMaterialVars() > 0 ) {
    GenerateMaterialVarInitializeRoutine();
  }

  if(feelfemobj.HowManyUserFunctions() > 0) {
    GenerateMakefileForUserFunction();
  }

  return;
}

void PM_aistpcp90::GenerateMakefileForUserFunction()
{
  listIterator <Function *>itr(feelfemobj.GetUserFunctionList());
  for(itr.init();!itr ;++itr) {
    const char *sourceName = GetSourceName( itr()->GetName());
    StoreSourceUniq(sourceName, LINKLEVEL_USERFUNC);
  }
  return;
}

void PM_aistpcp90::GenerateMaterialVarInitializeRoutine(void)
{
  char  hereRoutineName[BUFSIZ];
  const char *hereSourceName;

  sprintf(hereRoutineName,"initmatvar%c",'\0');
  hereSourceName = GetSourceName(hereRoutineName);
  OpenSource(hereSourceName,LINKLEVEL_COROUTINE_MAIN);  // main coroutine

  writeSource("module mod_initmatvar");
  writeSource("contains");
  com();

  pushSource("subroutine ");
  pushSource(hereRoutineName);
  pushSource("(meshDat,firstEdatPtr,matData");
  listIterator <Variable *>itrMatV(feelfemobj.GetMaterialVarList());
  for(itrMatV.init(); !itrMatV ; ++itrMatV ){
    pushSource(",");
    pushVariableInCalled( itrMatV() );
  }
  pushSource(")");
  flushSource();


  com();
  writeSource("use femDataType");
  writeSource("use feelP2data");
  writeSource("use numeric");
  com();

  writeSource("implicit none");
  com();
  
  writeSource("type(meshInformation)                   :: meshDat  ");
  writeSource("type(edatList),pointer                  :: firstEdatPtr");
  writeSource("type(matdat)  ,pointer                  :: matData");
  com();

  for(itrMatV.init(); !itrMatV ; ++itrMatV ){
    pushReal8Ptr1();
    pushVariableInCalled( itrMatV() );
    flushSource();
  }
  com();

  writeInteger4sc("edatno");
  writeInteger4sc("nelem,np,netype");
  writeInteger4Ptr2("ielem");
  writeInteger4Ptr1("matno");
  com();

  writeInteger4sc("i,j");
  writeInteger4sc("mno");
  writeInteger4sc("ierror");
  com();


  writeSource("edatno = meshDat%mainEdatNo");
  writeSource("call setP2edat(edatno,firstEdatPtr,nelem,np,netype,ielem,matno)");
  com();

  writeSource("ierror = 0");
  com();

  writeSource("do i=1,nelem");
  writeSource(" if(matno(i) == 0) ierror = ierror+1");
  writeSource("end do");
  com();

  writeSource("if(ierror >0) then");
  writeSource(" write(*,*) 'Some regions have 0 matno attributes.'");
  writeSource(" write(*,*) '(with material variable, all regions'");
  writeSource(" write(*,*) ' must be labeled. ',ierror,' elements has 0 matno.'");
  writeSource(" stop 'module initmatvar'");
  writeSource("end if");
  com();

  listIterator <RegionObject *> itrReg(feelfemgeomobj.GetRegionObjectPtrList());
  
  for(itrMatV.init(); !itrMatV ; ++itrMatV ){
    Variable *vPtr = itrMatV();

    com();
    writeSource("! --------------------------------------------------------");
    pushSource("! material var ");
    pushSource(itrMatV()->GetName());
    flushSource();
    writeSource("! --------------------------------------------------------");
    com();

    for(itrReg.init(); !itrReg ; ++itrReg ) {

      string regName = itrReg()->GetName();

      pushSource("mno = matData%regmat(");
      pushSourceInt(itrReg()->GetPropertyNo());
      pushSource(")      ! region ");
      pushSource(regName);
      flushSource();
      
      pushSource("m_");
      pushSource(itrMatV()->GetName());
      pushSource("(mno) = ");
      pushSourceDbl( itrMatV()->GetMaterialValueByRegionName(regName));
      pushSource("   ! region ");
      pushSource(regName);
      pushSource(" [");

      string matName;
      itrMatV()->GetMaterialNameByRegionName(regName,matName);
      pushSource(matName);
      pushSource("]");
      flushSource();
      com();
    }
    writeSource("! --------------------------------------------------------");
    com();
    com();
  }

  writeSource("return");
  com();

  pushSource("end subroutine ");
  pushSource(hereRoutineName);
  flushSource();

  pushSource("end module mod_");
  pushSource(hereRoutineName);
  flushSource();

  CloseSource();
  return;
}



