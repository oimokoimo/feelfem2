/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNgt.hpp
 *  Date     : 2001/02/20
 *  Modified : 
 *  
 *  Purpose  :
 *  
 */

#ifndef FEM_SYNTAX_GT
#define FEM_SYNTAX_GT

#include "../../class/string.hpp"
#include "SNunit.hpp"

class SNgt : public SNunit {
public:
  SNgt(SNunit *a1,SNunit *a2) : SNunit("gt",SN_GT),arg1(a1),arg2(a2)
  {}

  int  howManyNotDefinedVariable( int flag,void *ptr1,void *ptr2);
  int  howManyNotDefinedFunction( int flag,void *ptr1,void *ptr2);
  int  howManyNotAssignedVariable( int flag,void *ptr1,void *ptr2);

  void exprPrint( char *buf, int flag,void *ptr1,void *ptr2);

  void print(ostream & ost) { 
    arg1->print(ost);
    ost << ">";
    arg2->print(ost);
  }

#include "expr_friend.def"

private:
  SNunit *arg1;
  SNunit *arg2;
};


#endif
