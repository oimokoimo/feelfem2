/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNsolveParametric.hpp
 *  Date     : 2002/02/19
 *  Modified : 
 *  
 *  Purpose  : solveParametric class for parser  (reference aumc)
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

#ifndef FEM_SYNTAX_SOLVEPARAMETRIC
#define FEM_SYNTAX_SOLVEPARAMETRIC

#include "SNunit.hpp"
#include "../../class/string.hpp"

class SNsolveParametric : public SNunit {
public:
  SNsolveParametric( char *nm ) :
    SNunit("solveParametric",SN_SOLVEPARAMETRIC) 
  { parametricName = nm; }

  void print(std::ostream & ost) { ost << "solveParametric="
                                  <<  parametricName
				  << "\n";            }

  const string getName(void) {
    return( parametricName );
  }

  // for error message
  void errWrtName(std::ostream &ost ) {
    ost << parametricName;
    return;
  }


private:
  string parametricName;

};


#endif
