/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : RegionObject.hpp
 *  Date     : 2002/03/18
 *  Modified : 
 *  
 *  Purpose  : Region
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

#ifndef FEM_CLASS_REGIONOBJECT
#define FEM_CLASS_REGIONOBJECT

#include "string.hpp"
#include "GeomObj.hpp"
#include "list.hpp"

class PolygonalRegion;

class RegionObject  : public GeomObj {
public:
  RegionObject(const char *nm);
  RegionObject(PolygonalRegion *);

  ~RegionObject();

  int   GetPropertyNo(void);

  void AddMaterialAttribute( string &);
  int  HasMaterialAttribute( string &);

  const char *GetName() {
    return(name);
  }

private:
  int    no  ;    // used in generated program

  static int regionNo;

  PolygonalRegion *polygonalRegionPtr;

  list <string> materialAttributeStrLst;

};
#endif
