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

