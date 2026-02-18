/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNor.hpp
 *  Date     : 2001/02/20
 *  Modified : 
 *  
 *  Purpose  :
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

#ifndef FEM_SYNTAX_OR
#define FEM_SYNTAX_OR

#include "../../class/string.hpp"
#include "SNunit.hpp"

class SNor : public SNunit {
public:
  SNor(SNunit *a1,SNunit *a2) : SNunit("or",SN_OR),arg1(a1),arg2(a2)
  {}

  void print(std::ostream & ost) { 
    arg1->print(ost);
    ost << " or ";
    arg2->print(ost);
  }

private:
  SNunit *arg1;
  SNunit *arg2;
};


#endif
