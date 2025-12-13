/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNbracket.hpp
 *  Date     : 2001/02/14
 *  Modified : 
 *  
 *  Purpose  : Bracket for parser
 *  
 */

#ifndef FEM_SYNTAX_BRACKET
#define FEM_SYNTAX_BRACKET

#include "../../class/string.hpp"
#include "SNunit.hpp"

class SNbracket : public SNunit {
public:
  SNbracket(SNunit *a) : SNunit("bracket",SN_BRACKET),expr(a) 
  {  }

  int  howManyNotDefinedVariable( int flag,void *ptr1,void *ptr2);
  int  howManyNotDefinedFunction( int flag,void *ptr1,void *ptr2);
  int  howManyNotAssignedVariable( int flag,void *ptr1,void *ptr2);

  void exprPrint( char *buf, int flag,void *ptr1,void *ptr2);

  void print(ostream & ost) { 
    ost << "(";
    expr->print(ost);
    ost <<  ")";
  }

#include "expr_friend.def"

private:
  SNunit *expr;

};


#endif
