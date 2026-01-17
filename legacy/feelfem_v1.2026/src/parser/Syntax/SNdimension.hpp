/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNdimension.hpp
 *  Date     : 2001/02/14
 *  Modified : 
 *  
 *  Purpose  : dimension class for parser  (reference aumc)
 *  
 */

#ifndef FEM_SYNTAX_DIMENSION
#define FEM_SYNTAX_DIMENSION

#include "SNunit.hpp"

class SNdimension : public SNunit {
public:
  SNdimension(long int & d) : SNunit("dimension",SN_DIMENSION) {
    dim = d; 
    return;
  }

  void print(ostream & ost) { ost << "dimension "<< dim ; }
  int  getSpaceDimension(void) { return dim; }

private:
  int    dim;

};


#endif
