/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
q *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNgeomMesher.hpp
 *  Date     : 2002/03/12
 *  Modified : 
 *  
 *  Purpose  : geom-mesher class for parser  (for GiD interface)
 *  
 */

#ifndef FEM_SYNTAX_GEOMMESHER
#define FEM_SYNTAX_GEOMMESHER

#include "SNunit.hpp"
#include "string.hpp"

class SNgeomMesher : public SNunit {
public:
  SNgeomMesher(char *nm) : SNunit("geomMesher",SN_GEOMMESHER) {
    mesherName = nm;
    return;
  }

  void print(ostream & ost) { ost << "geomMesher "<< mesherName ; }

  string &GetName() {
    return mesherName;
  }

  virtual int Check(void);
  virtual int InfoGenerate();

private:
  string mesherName;

};

#endif
