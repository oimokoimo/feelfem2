/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNor.hpp
 *  Date     : 2001/02/20
 *  Modified : 
 *  
 *  Purpose  :
 *  
 */

#ifndef FEM_SYNTAX_OR
#define FEM_SYNTAX_OR

#include "../../class/string.hpp"
#include "SNunit.hpp"

class SNor : public SNunit {
public:
  SNor(SNunit *a1,SNunit *a2) : SNunit("or",SN_OR),arg1(a1),arg2(a2)
  {}

  void print(ostream & ost) { 
    arg1->print(ost);
    ost << " or ";
    arg2->print(ost);
  }

private:
  SNunit *arg1;
  SNunit *arg2;
};


#endif
