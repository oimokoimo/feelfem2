/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNsolveSolver.hpp
 *  Date     : 2001/03/05
 *  Modified : 
 *  
 *  Purpose  : solveSolver class for parser  (reference aumc)
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

#ifndef FEM_SYNTAX_SOLVESOLVER
#define FEM_SYNTAX_SOLVESOLVER

#include "SNunit.hpp"
#include "../../class/string.hpp"

class SNsolveSolver : public SNunit {
public:
  SNsolveSolver( const char *nm ) :
    SNunit("solveSolver",SN_SOLVESOLVER) 
  { solverName = nm; }

  void print(std::ostream & ost) { ost << "solveSolver="
                                  <<  solverName
				  << "\n";            }

  const string getName(void) {
    return( solverName );
  }


private:
  string solverName;

};


#endif
