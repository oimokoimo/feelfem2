/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNint.hpp
 *  Date     : 2001/02/14
 *  Modified : 
 *  
 *  Purpose  : int class for parser  (reference aumc)
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

#ifndef FEM_SYNTAX_INT
#define FEM_SYNTAX_INT

#include "SNunit.hpp"

class SNint : public SNunit {
public:
  SNint(long int & i) : SNunit("int",SN_INT) { val = i; }

  int  howManyNotDefinedVariable( int flag,void *ptr1,void *ptr2) {
    return(0);
  }
  int  howManyNotDefinedFunction( int flag,void *ptr1,void *ptr2) {
    return(0);
  }
  int  howManyNotAssignedVariable( int flag,void *ptr1,void *ptr2) {
    return(0);
  }


  void exprPrint( char *buf, int flag,void *ptr1,void *ptr2);

  void print(std::ostream & ost) { ost <<  val ; }


#include "expr_friend.def"

private:
  int val;

};


#endif
