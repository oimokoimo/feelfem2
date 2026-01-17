/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNidentifierlist.hpp
 *  Date     : 2001/02/23
 *  Modified : 
 *  
 *  Purpose  : Syntax identifierlist class (mostly for debugging use)
 *  
 */

#ifndef FEM_SYNTAX_IDENTIFIERLIST
#define FEM_SYNTAX_IDENTIFIERLIST

#include "SNunit.hpp"
#include "SNname.hpp"


class SNidentifierlist : public SNunit {
public:

  SNidentifierlist(int);
  ~SNidentifierlist();

  SNname *&operator[] (int i) { return contents[i]; }

  void print(ostream&);

  void StoreContentsInStringLst(list<string > &);

  int  GetNumberOfElements() { return elements; }
  

private:
  int      elements;
  SNname **contents;


};

#endif
