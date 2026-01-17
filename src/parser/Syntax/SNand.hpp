/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNand.hpp
 *  Date     : 2001/02/20
 *  Modified : 
 *  
 *  Purpose  :
 *  
 */

#ifndef FEM_SYNTAX_AND
#define FEM_SYNTAX_AND

#include "../../class/string.hpp"
#include "SNunit.hpp"

class SNand : public SNunit {
public:
  SNand(SNunit *a1,SNunit *a2) : SNunit("and",SN_AND),arg1(a1),arg2(a2)
  {}

  void print(ostream & ost) { 
    arg1->print(ost);
    ost << "&&";
    arg2->print(ost);
  }

#include "expr_friend.def"


private:
  SNunit *arg1;
  SNunit *arg2;
};


#endif
