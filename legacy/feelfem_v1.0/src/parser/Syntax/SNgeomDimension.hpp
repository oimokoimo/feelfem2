/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNgeomDimension.hpp
 *  Date     : 2002/03/12
 *  Modified : 
 *  
 *  Purpose  : geom-dimension class for parser  (for GiD interface)
 *  
 */

#ifndef FEM_SYNTAX_GEOMDIMENSION
#define FEM_SYNTAX_GEOMDIMENSION

#include "SNunit.hpp"

class SNgeomDimension : public SNunit {
public:
  SNgeomDimension(int d) : SNunit("geomDimension",SN_GEOMDIMENSION) {
    dim = d; 
    return;
  }

  void print(ostream & ost) { ost << "geomDimension "<< dim ; }
  int  getGeomDimension(void) { return dim; }

  virtual int Check(void);
  virtual int InfoGenerate();

private:
  int    dim;

};

#endif
