/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNgeomSurface.hpp
 *  Date     : 2001/02/23
 *  Modified : 
 *  
 *  Purpose  : geomSurface class for parser  (reference aumc)
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

#ifndef FEM_SYNTAX_GEOMSURFACE
#define FEM_SYNTAX_GEOMSURFACE

#include "SNunit.hpp"
#include "SNidentifierlist.hpp"
#include "string.hpp"


class SNgeomSurface : public SNunit {
public:
  SNgeomSurface( SNidentifierlist *ptr) : SNunit("geomSurface",SN_GEOMSURFACE){
    identifierLst = ptr;
    return;
  }

  void print(std::ostream & ost) {
    ost << "geomSurface ";
    identifierLst->print(ost);
  }

  virtual int Check();
  virtual int InfoGenerate();

private:
  SNidentifierlist *identifierLst;

};

#endif

