/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNequal.hpp
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
 */

#ifndef FEM_SYNTAX_EQUAL
#define FEM_SYNTAX_EQUAL

#include "../../class/string.hpp"
#include "SNunit.hpp"

class SNequal : public SNunit {
public:
  SNequal(SNunit *a1,SNunit *a2) : SNunit("equal",SN_EQUAL),arg1(a1),arg2(a2)
  {}

  int  howManyNotDefinedVariable( int flag,void *ptr1,void *ptr2);
  int  howManyNotDefinedFunction( int flag,void *ptr1,void *ptr2);
  int  howManyNotAssignedVariable( int flag,void *ptr1,void *ptr2);

  void exprPrint( char *buf, int flag,void *ptr1,void *ptr2);


  void print(std::ostream & ost) { 
    arg1->print(ost);
    ost << "==";
    arg2->print(ost);
  }

#include "expr_friend.def"

private:
  SNunit *arg1;
  SNunit *arg2;
};


#endif
