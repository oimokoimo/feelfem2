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

#ifndef FEM_SYNTAXNAME
#define FEM_SYNTAXNAME

#include "../../class/string.hpp"

class SyntaxName  {

public:
  SyntaxName( char * );
  ~SyntaxName() { }

  int LineNumber() { return lineNumber; }
  void LineNumber(int n) { lineNumber = n; }

private:
  int lineNumber;
  string name;
};

#endif



