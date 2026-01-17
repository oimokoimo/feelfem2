/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNvertices.hpp
 *  Date     : 2001/02/23
 *  Modified : 
 *  
 *  Purpose  : vertices class for parser  (reference aumc)
 *  
 */

#ifndef FEM_SYNTAX_VERTICES
#define FEM_SYNTAX_VERTICES

#include "SNunit.hpp"

class SNvertices : public SNunit {
public:
  SNvertices( int vs) : vertices(vs),SNunit("vertices",SN_VERTICES) {
    return;
  }

  void print(ostream & ost) {
    ost << "vertices ";
    ost << vertices;
  }

  int getVertices() {
    return(vertices);
  }
  

private:
  int vertices;

};


#endif
