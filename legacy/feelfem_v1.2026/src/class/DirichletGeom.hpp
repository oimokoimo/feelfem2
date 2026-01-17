/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : DirichletGeom.hpp
 *  Date     : 2002/03/15
 *  Modified : 2002/04/19 (BCN)
 *  
 *  Purpose  : Geometry object for Dirichlet conditions
 *  
 */

#ifndef FEM_CLASS_DIRICHLETGEOM
#define FEM_CLASS_DIRICHLETGEOM

#include "GeomObj.hpp"
#include "BGeom.hpp"

#include "Dirichlet.hpp"
#include "list.hpp"

class DirichletGeom : public BGeom {
public:
  DirichletGeom(GeomObj *);
  ~DirichletGeom();

  int GetDirichletGeomNo() {
    return(no);
  }

  void StoreDirichletData(Dirichlet *);
  list <Dirichlet *>&GetDirichletDataPtrLst(void) {
    return(dDataPtrLst);
  }


private:
  static int dcondGeoms;
  int no;

  list <Dirichlet *>dDataPtrLst;  // add in SNsolveDirichlet_InfoGenerate.cpp
                                  // used in GiD_cnd.cpp
};

#endif
