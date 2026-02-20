/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNsolveQuadrature.hpp
 *  Date     : 2001/03/05
 *  Modified : 
 *  
 *  Purpose  : solveQuadrature class for parser  (reference aumc)
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

#ifndef FEM_SYNTAX_SOLVEQUADRATURE
#define FEM_SYNTAX_SOLVEQUADRATURE

#include "SNunit.hpp"
#include "../../class/string.hpp"


class SNsolveQuadrature : public SNunit {
public:
  SNsolveQuadrature(const char *nm) :
    SNunit("solveQuadrature",SN_SOLVEQUADRATURE) 
  { quadName = nm; }

  void print(std::ostream & ost ) { ost << "solveQuadrature="
                                  << quadName 
                		  << "\n";              }
  const string getName(void) {
    return( quadName );
  }
		

private:
  string quadName;

};


#endif
