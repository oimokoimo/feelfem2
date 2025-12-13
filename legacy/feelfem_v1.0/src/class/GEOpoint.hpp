/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : GEOpoint.hpp
 *  Date     : 2001/02/27
 *  Modified : Point object for Geometry
 *  
 *  Purpose  : 
 *  
 */

#ifndef FEM_GEO_POINT
#define FEM_GEO_POINT

#include "string.hpp"
#include "feelfuncs.hpp"

class GEOpoint {
public:
  GEOpoint( char *nm , double s, double t, double u)
  {
    name       = nm;

    
    dimension  = 3;
    x          = s;
    y          = t;
    z          = u;
  }



private:
  string name;              // Name
  int    dimension;
  int    referenceNo;       // 

  double x,y,z;             // coordinate


};


#endif
