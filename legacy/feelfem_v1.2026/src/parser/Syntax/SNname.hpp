/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999,2000
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SyntaxName.hpp
 *  Date     : 2000/11/28
 *  Modified : 2000/11/28
 *  
 *  Purpose  :
 *  
 */

#ifndef FEM_SYNTAX_NAME
#define FEM_SYNTAX_NAME

#include "../../class/string.hpp"

class SNname  {

public:
  SNname( char * );
  ~SNname();

  int LineNumber() { return lineNumber; }
  void LineNumber(int n) { lineNumber = n; }

  void print(ostream &ost) { ost << (char *)name ; }

  const char *GetName() { return(name); }
  operator const char *() const ;


private:
  int lineNumber;
  string name;
};

#endif
