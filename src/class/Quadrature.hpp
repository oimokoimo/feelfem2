/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : Quadrature.hpp
 *  Date     : 1999/12/15
 *  Modified : 1999/12/15
 *  
 *  Purpose  : Class definition for quadrature
 *
 * 
 *  feelfem2 (modernized/ported)
 *  Copyright (C) 2025-2026 Hidehiro Fujio and contributors
 *  SPDX-License-Identifier: BSD-3-Clause
 *  Repository: https://github.com/oimokoimo/feelfem2
 *
 *
 *  Notes:
 *  
 */

#ifndef FEM_CLASS_QUADRATURE
#define FEM_CLASS_QUADRATURE

#include "string.hpp"
#include "GaussPoints.hpp"


class Quadrature : public GaussPoints {
public:

  Quadrature();   // default constructor, should not be called
  Quadrature(string &,int,int,int);
  ~Quadrature();


  // for test/main.cpp 
  void testSetName(char *);
  void testSetQuadraturePoints(int);

//  int   GetQuadraturePoints(void);   // now in GauassPoints
  const char *GetName();
  

  int isNameIs(const char *nm) {
    return(name == nm);
  }

  int GetEtype(void)
  {
    return(elementEtype);
  }

  
  // debug routine
  void dbgXDisplay(void);

  
private:

//  Initializa in Constructor    (Quadrature private)
  string name;
  int    dimension;           // space dimension
  int    elementEtype;

//  Quadrature point information are stored in GaussPoint class

};

#endif
