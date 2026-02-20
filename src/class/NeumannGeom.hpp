/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : NeumannGeom.hpp
 *  Date     : 2002/03/22
 *  Modified : 2002/04/19 (BCN)
 *  
 *  Purpose  : Geometry object for Neumann conditions
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

#ifndef FEM_CLASS_NEUMANNGEOM
#define FEM_CLASS_NEUMANNGEOM

#include "BGeom.hpp"
#include "Neumann.hpp"
#include "list.hpp"

class GeomObj;


class NeumannGeom : public BGeom {
public:
  NeumannGeom(GeomObj *);
  ~NeumannGeom();

  int GetNeumannGeomNo(void) {
    return(no);
  }

  void StoreNeumannData(Neumann *);
  list <Neumann *>&GetNeumannDataPtrLst(void) {
    return(nDataPtrLst);
  }


private:
  static int ncondGeoms;
  int no;

  list <Neumann *>nDataPtrLst; // add in SNsolveNeumann_InfoGenerate.cpp
                               // used in GiD_cnd.cpp
};

#endif
