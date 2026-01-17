/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNgeomMaterialRegion.cpp
 *  Date     : 2002/08/30
 *  Modified : 
 *  
 *  Purpose  :
 *  
 */

#include "SNgeomMaterialRegion.hpp"

SNgeomMaterialRegion::SNgeomMaterialRegion(char *nm,SNidentifierlist *ptr) 
    : SNunit("geomMaterialRegion",SN_GEOMMATERIALREGION)
{
  name = nm;
  identifierLst = ptr;
  return;
}

SNgeomMaterialRegion::~SNgeomMaterialRegion()
{
  // do nothing
  return;
}
