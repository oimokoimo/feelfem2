/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : init_StoreGeomObj.cpp
 *  Date     : 2002/03/18
 *  Modified : 
 *  
 *  Purpose  : GeometryObject related initializer
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
#include "Configure.hpp"

void Configure::init_StoreGeomObj()
{
  // Store mesher name
  StoreMesherCode( NAME_MESHER_BAMG, MESH_GENERATOR_BAMG);
  StoreMesherCode( NAME_MESHER_GID , MESH_GENERATOR_GID );

  return;
}
