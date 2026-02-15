/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNgeomMaterialRegion.hpp
 *  Date     : 2002/08/30    (copy from SNgeomSurface)
 *  Modified : 
 *  
 *  Purpose  : geomMaterialRegion class for parser  (reference aumc)
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

#ifndef FEM_SYNTAX_GEOMMATERIALREGION
#define FEM_SYNTAX_GEOMMATERIALREGION

#include "SNunit.hpp"
#include "SNidentifierlist.hpp"
#include "string.hpp"


class SNgeomMaterialRegion : public SNunit {
public:
  SNgeomMaterialRegion(const char *nm,SNidentifierlist *ptr) ;
  ~SNgeomMaterialRegion();


  void print(std::ostream & ost) {
    ost << "geomMaterialRegion " << name << " ";
    identifierLst->print(ost);
  }

  virtual int Check();
  virtual int InfoGenerate();

private:
  string name;
  SNidentifierlist *identifierLst;

};

#endif

