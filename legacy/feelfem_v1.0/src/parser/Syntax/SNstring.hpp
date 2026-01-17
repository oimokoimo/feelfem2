/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999,2000
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNstring.hpp    
 *  Date     : 2002/11/21
 *  Modified : 2002/11/21
 *  
 *  Purpose  : for Write sentences
 *  
 */

#ifndef FEM_SYNTAX_STRING
#define FEM_SYNTAX_STRING

#include "SNunit.hpp"

#include "../../class/string.hpp"

class SNstring :public SNunit {

public:
  SNstring( char * );
  ~SNstring();

  int LineNumber() { return lineNumber; }
  void LineNumber(int n) { lineNumber = n; }

  void print(ostream &ost) { ost << (char *)str ; }

  const char *GetString() { return(str); }
  operator const char *() const ;


private:
  int lineNumber;
  string str;
};

#endif
