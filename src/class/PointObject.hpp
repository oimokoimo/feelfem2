/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : PointObject.hpp
 *  Date     : 2002/03/14
 *  Modified : 
 *  
 *  Purpose  : Point
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

#ifndef FEM_CLASS_POINTOBJECT
#define FEM_CLASS_POINTOBJECT

#include "string.hpp"
#include "GeomObj.hpp"

class Point;

class PointObject : public GeomObj {
public:
  PointObject(const char *nm); 
  PointObject(Point *);

  ~PointObject();
  
  const char *GetName() {
    return(name);
  }

private:
  int    no  ;    // used in generated program

  static int pointNo;

  Point *pPtr;    // if Geometry is defined inside

};
#endif
