/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNparametric.hpp
 *  Date     : 2002/07/11
 *  Modified : 
 *  
 *  Purpose  : programmodel class for parser  (reference aumc)
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

#ifndef FEM_SYNTAX_PARAMETRIC
#define FEM_SYNTAX_PARAMETRIC

#include "SNunit.hpp"
#include "SNname.hpp"

class SNparametric : public SNunit {
public:
  SNparametric(const char *nm);
  ~SNparametric() { // do nothing 
    ;}
  // print
  void print(std::ostream & ost) { ost << "parametric=" 
				  <<  parametricName
				  << "\n";            }

  // check functions
  int  IsValidParametricName(void);      // in SNparametric_CHECK.cpp
  //  void set_feelfemobj(void);         // (included in above function)
                                         // set feelfemobj

  // Code generate functions  (ProgramModel has no instance.)
  void CodeGenerate(void);
  void CodeGenerateMain(void *p,Main *m);

  // for SystemError functions
  void errWrtName(std::ostream &ost ) {
    ost << parametricName;
    return;
  }
 
private:
  string elementShapeName;    // line,tri,quad,tetra,quad
  string parametricName;      // Element Name
};


#endif
