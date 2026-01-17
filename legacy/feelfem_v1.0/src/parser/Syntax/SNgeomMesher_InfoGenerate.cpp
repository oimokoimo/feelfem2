/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNgeomMesher_InfoGenerate.cpp
 *  Date     : 2002/03/18
 *  Modified : 
 *  
 *  Purpose  :
 *  
 */

#include "feelfuncs.hpp"
#include "SNgeomMesher.hpp"

#include "GeometryObject.hpp"

#include "Object.hpp"
#include "Configure.hpp"

int SNgeomMesher::InfoGenerate(void)
{
  feelfemgeomobj.SetMesherName( mesherName );

  int code = feelfemconf.GetMesherCodeByName( mesherName );

  feelfemobj.SetMesherCode( code );
  
  return(0);
}

  
