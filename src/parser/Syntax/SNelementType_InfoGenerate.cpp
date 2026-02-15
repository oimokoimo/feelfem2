/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNelementType_InfoGenerate.cpp
 *  Date     : 2002/11/07
 *  Modified : 
 *  
 *  Purpose  :
 *
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
#include "GeometryObject.hpp"
#include "feelfuncs.hpp"

int SNelementType::InfoGenerate(void)
{
  int components = etypeIdentifierLst->GetNumberOfElements();
  for(int i=0;i<components;i++) {
    SNname *snnPtr;

    snnPtr     = (*etypeIdentifierLst)[i];
    string str = snnPtr->GetName();

    feelfemgeomobj.AddUniqEtypeStr(str);
  }
  return(0);
}

