
/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : GeomObj.hpp
 *  Date     : 2002/03/15
 *  Modified : 
 *  
 *  Purpose  : unit class for Abstract Geometry Objects
 *
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
 *  
 */

#ifndef FEM_CLASS_GEOMOBJ
#define FEM_CLASS_GEOMOBJ

#include "string.hpp"

class GeomObj {

public:
  GeomObj(int,char *);
  ~GeomObj();

  int GetType();
  int IsNameIs(string &);
  const char *GetName(void) const {
    return static_cast<const char *>(name);
  }

  void SetDirichletFlag();
  void SetNeumannFlag();
  int  GetDirichletFlag();
  int  GetNeumannFlag();

  virtual int GetPropertyNo(void);

protected:
  int    geomNo;
  int    geomType;
  string name;

private:
  static int geomObjNo;   // initialized in Geometry/GeometryObject.cpp

  int    dFlag;  // used for Dirichlet data
  int    nFlag;  // used for Neumann data
  
  int    dNo;    // data no for Dirichlet conditions
  int    nNo;    // data no for Neumann   conditions
  int    mNo;    // material No for region object
  int    pNo;    // point no for point object

};

#endif
