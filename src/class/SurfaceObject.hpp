/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SurfaceObject.hpp
 *  Date     : 2002/03/14
 *  Modified : 
 *  
 *  Purpose  :
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

#ifndef FEM_CLASS_SURFACEOBJECT
#define FEM_CLASS_SURFACEOBJECT

#include "feeldef.hpp"
#include "GeomObj.hpp"
#include "string.hpp"

class SurfaceObject : public GeomObj {

public:
  SurfaceObject(const char *nm);
  // SurfaceObject(Surface *);   // no

  ~SurfaceObject();

  const char *GetName() {
    return(name);
  }

private:
  static int surfaceNo;
  int no;

  // Surface *surfPtr;
};

#endif
