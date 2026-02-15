/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNgeomEdge.hpp
 *  Date     : 2001/02/23
 *  Modified : 
 *  
 *  Purpose  : geomEdge class for parser  (reference aumc)
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

#ifndef FEM_SYNTAX_GEOMEDGE
#define FEM_SYNTAX_GEOMEDGE

#include "SNunit.hpp"
#include "SNidentifierlist.hpp"
#include "string.hpp"


class SNgeomEdge : public SNunit {
public:
  SNgeomEdge( SNidentifierlist *ptr) : SNunit("geomEdge",SN_GEOMEDGE) {
    identifierLst = ptr;
    return;
  }

  void print(std::ostream & ost) {
    ost << "geomEdge ";
    identifierLst->print(ost);
  }

  virtual int Check(void);
  virtual int InfoGenerate();

private:
  SNidentifierlist *identifierLst;

};


#endif
