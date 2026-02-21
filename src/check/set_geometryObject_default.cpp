/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : set_geometryObject_default.cpp
 *  Date     : 2002/03/25
 *  Modified : 
 *  
 *  Purpose  : set dimension, bamg
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

#include "check_funcs.hpp"

#include "list.hpp"
#include "feelfuncs.hpp"
#include "Geometry.hpp"
#include "GeometryObject.hpp"
#include "Object.hpp"
#include "Configure.hpp"

class SNunit;
int set_geometryObject_default(list <void *>&pmeshLst,
				list <SNunit *>&pgeomLst)
{
  if(feelfemobj.GetMesherCode() == 0) {
    int linesOfMeshBlock = pmeshLst.getNumberOfElements();
    int linesOfGeomBlock = pgeomLst.getNumberOfElements();
    
    if(linesOfGeomBlock == 0) {  // maybe bamg
      string name = NAME_MESHER_BAMG;
      feelfemgeomobj.SetMesherName( name );
      int code = feelfemconf.GetMesherCodeByName( name );
      feelfemobj.SetMesherCode( code );

      return(0);
    }

    if(linesOfMeshBlock == 0) {
      string name = NAME_MESHER_GID;
      feelfemgeomobj.SetMesherName( name );
      int code = feelfemconf.GetMesherCodeByName( name );
      feelfemobj.SetMesherCode( code );

      return(0);
    }
    return(1);  // if both block exists, mesher must be explicitly specified.
  }
  return(0);
}
