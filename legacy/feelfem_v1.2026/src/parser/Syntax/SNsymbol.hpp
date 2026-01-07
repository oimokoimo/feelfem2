/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNsymbol.hpp
 *  Date     : 2001/02/14
 *  Modified : 
 *  
 *  Purpose  : Symbol for parser
 *  
 */

#ifndef FEM_SYNTAX_SYMBOL
#define FEM_SYNTAX_SYMBOL

#include "../../class/string.hpp"
#include "../../class/feeldef.hpp"     // MAX_EXPRPRINT_BUF
#include "SNunit.hpp"

class SNsymbol : public SNunit {
public:
  SNsymbol(char *name) : SNunit("symbol",SN_SYMBOL) { val = name; }

  int  howManyNotDefinedVariable( int flag,void *ptr1,void *ptr2);
  int  howManyNotDefinedFunction( int flag,void *ptr1,void *ptr2);
  int  howManyNotAssignedVariable( int flag,void *ptr1,void *ptr2);

  void exprPrint( char *buf, int flag,void *ptr1,void *ptr2);

  void print(ostream & ost) { ost <<  val ; }

#include "expr_friend.def"

private:
  string val;

};

#endif
