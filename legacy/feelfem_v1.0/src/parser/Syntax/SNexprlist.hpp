/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNexprlist.hpp
 *  Date     : 2001/02/14
 *  Modified : 
 *  
 *  Purpose  : Syntax exprlist class (mostly for debugging use)
 *  
 */

#ifndef FEM_SYNTAX_EXPRLIST
#define FEM_SYNTAX_EXPRLIST

#include "SNunit.hpp"


class SNexprlist : public SNunit {
public:

  SNexprlist(int);
  ~SNexprlist();

  SNunit *&operator[]  (int i) { return contents[i]; }
  SNunit *getIth(int i) { return contents[i]; }        // Jesus! Ugly code...
  int  howManyElements(void)  { return elements;    }

  int  howManyNotDefinedVariable( int flag,void *ptr1,void *ptr2);
  int  howManyNotDefinedFunction( int flag,void *ptr1,void *ptr2);
  int  howManyNotAssignedVariable( int flag,void *ptr1,void *ptr2);

  void exprPrint( char *buf, int flag,void *ptr1,void *ptr2);

  void print(ostream&);

#include "expr_friend.def"
  

private:
  int      elements;
  SNunit **contents;


};

#endif
