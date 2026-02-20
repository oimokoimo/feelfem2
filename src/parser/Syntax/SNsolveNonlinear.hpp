/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNsolveNonlinear.hpp
 *  Date     : 2001/03/05
 *  Modified : 
 *  
 *  Purpose  : solveNonlinear class for parser  (reference aumc)
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

#ifndef FEM_SYNTAX_SOLVENONLINEAR
#define FEM_SYNTAX_SOLVENONLINEAR

#include "SNunit.hpp"
#include "../../class/string.hpp"

class SNsolveNonlinear : public SNunit {
public:
  SNsolveNonlinear( const char *nm ) :
    SNunit("solveNonlinear",SN_SOLVENONLINEAR) 
  { nonlinearMethod = nm; }

  void print(std::ostream & ost) { ost << "solveNonlinear="
                                  <<  nonlinearMethod
				  << "\n";            }

  const string getName(void) {
    return( nonlinearMethod );
  }


private:
  string nonlinearMethod;

};


#endif
