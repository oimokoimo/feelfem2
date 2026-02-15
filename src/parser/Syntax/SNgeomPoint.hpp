/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNgeomPoint.hpp
 *  Date     : 2001/02/23
 *  Modified : 
 *  
 *  Purpose  : geomPoint class for parser  (reference aumc)
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

#ifndef FEM_SYNTAX_GEOMPOINT
#define FEM_SYNTAX_GEOMPOINT

#include "SNunit.hpp"
#include "SNidentifierlist.hpp"
#include "string.hpp"


class SNgeomPoint : public SNunit {
public:
  SNgeomPoint( SNidentifierlist *ptr) : SNunit("geomPoint",SN_GEOMPOINT) {
    identifierLst = ptr;
    return;
  }

  void print(std::ostream & ost) {
    ost << "geomPoint ";
    identifierLst->print(ost);
  }

  virtual int Check(void);
  virtual int InfoGenerate();

private:
  SNidentifierlist *identifierLst;
};

#endif
