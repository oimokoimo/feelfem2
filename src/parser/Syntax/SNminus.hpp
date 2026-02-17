/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNminus.hpp
 *  Date     : 2001/02/20
 *  Modified : 
 *  
 *  Purpose  : single operator -
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

#ifndef FEM_SYNTAX_MINUS
#define FEM_SYNTAX_MINUS

#include "../../class/string.hpp"
#include "SNunit.hpp"

class SNminus : public SNunit {
public:
  SNminus(SNunit *a) : SNunit("minus",SN_MINUS),arg(a)
  {}

  int  howManyNotDefinedVariable( int flag,void *ptr1,void *ptr2);
  int  howManyNotDefinedFunction( int flag,void *ptr1,void *ptr2);
  int  howManyNotAssignedVariable( int flag,void *ptr1,void *ptr2);

  void exprPrint( char *buf, int flag,void *ptr1,void *ptr2);

  void print(std::ostream & ost) { 
    ost << "-";
    arg->print(ost);
  }

#include "expr_friend.def"


private:
  SNunit *arg;
};

#endif
