/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNgeomDimension_InfoGenerate.cpp
 *  Date     : 2002/03/18
 *  Modified : 
 *  
 *  Purpose  :
 *  
 */

#include "feelfuncs.hpp"
#include "SNgeomDimension.hpp"
#include "GeometryObject.hpp"

int SNgeomDimension::InfoGenerate()
{
  feelfemgeomobj.SetSpaceDimension( dim );
  return(0);
}


