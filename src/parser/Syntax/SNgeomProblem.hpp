/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNgeomProblem.hpp
 *  Date     : 2002/03/12
 *  Modified : 
 *  
 *  Purpose  : geom-problem class for parser  (for GiD interface)
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

#ifndef FEM_SYNTAX_GEOMPROBLEM
#define FEM_SYNTAX_GEOMPROBLEM

#include "feeldef.hpp"
#include "SNunit.hpp"
#include "string.hpp"

class SNgeomProblem : public SNunit {
public:
  SNgeomProblem(const char *nm) : SNunit("geomProblem",SN_GEOMPROBLEM) {
    problemName = nm;
    return;
  }

  void print(std::ostream & ost) { ost << "geomProblem "<< problemName ; }

  virtual int Check(void);
  virtual int InfoGenerate();
  
private:
  string problemName;

};

#endif
