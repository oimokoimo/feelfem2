/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNfunction.hpp
 *  Date     : 2001/02/14
 *  Modified : 2001/03/16  exprPrint
 *  
 *  Purpose  : Function for parser
 *  
 */

#ifndef FEM_SYNTAX_FUNCTION
#define FEM_SYNTAX_FUNCTION

#include "../../class/string.hpp"
#include "SNunit.hpp"
#include "SNexprlist.hpp"

class SNfunction : public SNunit {
public:
  SNfunction(char *name,SNunit *a) ;

  int  howManyNotDefinedVariable( int flag,void *ptr1,void *ptr2);
  int  howManyNotDefinedFunction( int flag,void *ptr1,void *ptr2);
  int  howManyNotAssignedVariable( int flag,void *ptr1,void *ptr2);

  void exprPrint( char *buf, int flag,void *ptr1,void *ptr2);

  // for checking at scheme_userfunc_arg_check.cpp
  const char *GetName();
  int  HowManyArguments(void) {
    return arguments;
  }

  void print(ostream & ost) { 
    ost <<  val ;                 // "(" contains in exprlst
    exprlst->print(ost);
                                  //    ost <<  ")"; contains in expr list
  }

#include "expr_friend.def"

private:
  string  val;   // function name
  int     arguments;
  SNunit *exprlst;

};


#endif
