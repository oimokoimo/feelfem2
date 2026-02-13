/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNedge.hpp
 *  Date     : 2001/02/23
 *  Modified : 
 *  
 *  Purpose  : edge class for parser  (reference aumc)
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

#ifndef FEM_SYNTAX_EDGE
#define FEM_SYNTAX_EDGE

#include "SNunit.hpp"
#include "SNexprlist.hpp"
#include "../../class/string.hpp"

class Edge;

class SNedge : public SNunit {
public:
  SNedge( char *nm, SNunit *ptr) : name(nm),SNunit("edge",SN_EDGE) {
    identifierLst = ptr;
    return;
  }

  void print(std::ostream & ost) {
    ost << "edge ";
    ost <<  name;
    identifierLst->print(ost);
  }

  void errWrtName(std::ostream &ost ) {
    ost << name;
    return;
  }

  int isAlreadyUsedName( list <string> &strLst) {
    if(strLst.includes(name)) {
      return(YES);
    }
    else {
      strLst.addlast(name);
      return(NO);
    }
  }

  Edge *MakeEdgeObj();    // used in geometry_generate.cpp
  

private:
  string  name;
  SNunit *identifierLst;

};


#endif
