/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNoption.hpp
 *  Date     : 2002/01/18
 *  Modified : 
 *  
 *  Purpose  : option parser
 *  
 */

#ifndef FEM_SYNTAX_OPTION
#define FEM_SYNTAX_OPTION

#include "feeldef.hpp"

#include "SNunit.hpp"
#include "string.hpp"
#include "Expression.hpp"

class SNmaterialVar;

class SNoption : public SNunit {
public:
  SNoption( char *nm, Expression *ptr);    // with expression
  SNoption( char *nm, char       *opt);    // with string

  // check print routine
  void print(ostream & ost);

  friend class SNmaterialVar;

  string &GetOptionName(void) { return optionIdentifier; }
  void    GetValueAsString(string &);

  Expression *GetExprPtr(void);

private:
  string  optionIdentifier;
  string  optionString;

  Expression *exprPtr;

};


#endif
