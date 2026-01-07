/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNexpr.hpp
 *  Date     : 2002/11/22
 *  Modified : 2002/11/22
 *  
 *  Purpose  :
 *  
 */

#ifndef FEM_SYNTAX_EXPR
#define FEM_SYNTAX_EXPR

#include "Expression.hpp"

class SNexpr : public SNunit {

public:
  SNexpr( Expression * );
  ~SNexpr();

  int LineNumber() { return lineNumber; }
  void LineNumber(int n) { lineNumber = n; }

  void print(ostream &ost) { exprPtr->print(ost) ; }

  int checkOnlyGlobalScalar(void);

  Expression *GetExpr() { return(exprPtr); }

private:
  int lineNumber;
  Expression *exprPtr;
};

#endif
