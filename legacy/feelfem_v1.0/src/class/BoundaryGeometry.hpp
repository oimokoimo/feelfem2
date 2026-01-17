/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : BoundaryGeometry.hpp
 *  Date     : 2002/03/19
 *  Modified : 
 *  
 *  Purpose  :
 *  
 */

#ifndef FEM_CLASS_BOUNDARYGEOMETRY
#define FEM_CLASS_BOUNDARYGEOMETRY

class BGeom;

class BoundaryGeometry {
public:
  BoundaryGeometry();  ~BoundaryGeometry();

  void AddBGeomPtr(BGeom *);

private:
  
  list <BGeom *>boundaryGeomPtrLst;
};

#endif
