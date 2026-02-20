/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNvertices.hpp
 *  Date     : 2001/02/23
 *  Modified : 
 *  
 *  Purpose  : vertices class for parser  (reference aumc)
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

#ifndef FEM_SYNTAX_VERTICES
#define FEM_SYNTAX_VERTICES

#include "SNunit.hpp"

class SNvertices : public SNunit {
public:
  SNvertices( int vs) : vertices(vs),SNunit("vertices",SN_VERTICES) {
    return;
  }

  void print(std::ostream & ost) {
    ost << "vertices ";
    ost << vertices;
  }

  int getVertices() {
    return(vertices);
  }
  

private:
  int vertices;

};


#endif
