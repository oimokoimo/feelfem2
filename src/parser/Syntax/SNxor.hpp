/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNxor.hpp
 *  Date     : 2001/02/20
 *  Modified : 
 *  
 *  Purpose  :
 *  
 */

#ifndef FEM_SYNTAX_XOR
#define FEM_SYNTAX_XOR

#include "../../class/string.hpp"
#include "SNunit.hpp"

class SNxor : public SNunit {
public:
  SNxor(SNunit *a1,SNunit *a2) : SNunit("xor",SN_XOR),arg1(a1),arg2(a2)
  {}

  void print(std::ostream & ost) { 
    arg1->print(ost);
    ost << " xor ";
    arg2->print(ost);
  }

private:
  SNunit *arg1;
  SNunit *arg2;
};


#endif
