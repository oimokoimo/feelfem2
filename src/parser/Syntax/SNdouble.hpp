/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNdouble.hpp
 *  Date     : 2001/02/14
 *  Modified : 
 *  
 *  Purpose  : double class for parser  (reference aumc)
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

#ifndef FEM_SYNTAX_DOUBLE
#define FEM_SYNTAX_DOUBLE

#include "SNunit.hpp"

class SNdouble : public SNunit {
public:
  SNdouble( double & d) : SNunit("double",SN_DOUBLE) { val = d; }


  int  howManyNotDefinedVariable( int flag,void *ptr1,void *ptr2)
  {
    return(0);
  }
  int  howManyNotDefinedFunction( int flag,void *ptr1,void *ptr2)
  {
    return(0);
  }
  int  howManyNotAssignedVariable( int flag,void *ptr1,void *ptr2)
  {
    return(0);
  }

  void exprPrint( char *buf, int flag,void *ptr1,void *ptr2);


  void print(std::ostream & ost) { ost <<  val ; }


#include "expr_friend.def"

private:
  double val;

};


#endif
