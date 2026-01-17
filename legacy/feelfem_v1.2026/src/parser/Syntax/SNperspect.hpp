/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNperspect.hpp
 *  Date     : 2002/01/18
 *  Modified : 
 *  
 *  Purpose  : parse data for perspect
 *  
 */

#ifndef FEM_SYNTAX_PERSPECT
#define FEM_SYNTAX_PERSPECT

#include <iostream.h>

#include "stack.hpp"         // use stack (list)
#include "string.hpp"

#include "SNunit.hpp"

class SNoption;
class Expression;

class SNperspect : public SNunit {
public:
  SNperspect(Expression * );
  SNperspect(Expression *,stack <SNunit *> &) ;

  void print(ostream & ) ;

  // check functions
  int checkExprWellDefined(void);

  // InfoGenerate
  int InfoGenerate() {
    cerr << "INFOGENERATE OF PERSPECT\n";
    return(1);
  }

private:

  Expression *exprPtr;

  int         options;
  list <SNoption *>optionLst;

};

#endif
