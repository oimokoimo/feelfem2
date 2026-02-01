/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : GeometryObject.hpp
 *  Date     : 2002/03/12
 *  Modified : 
 *  
 *  Purpose  :
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
 */

#ifndef FEM_CLASS_GEOMETRYOBJECT
#define FEM_CLASS_GEOMETRYOBJECT

#include "list.hpp"
#include "string.hpp"
#include "GeomObj.hpp"

class BGeom;
class Mesher;
class NeumannGeom;
class DirichletGeom;
class RegionObject;

class GeometryObject {
  
public:
  GeometryObject();
  ~GeometryObject();

  void SetMesherName(string &);
  void SetProblemName(string &);
  void SetMesherPtr(Mesher *);
  const char *GetMesherName() const { return (const char *)mesherName;}

  // Etype   (2002/11 add for integral() and bintegral() functionalities
  // RegionEtype (In Gid case, it is explicitly given by user in scheme,
  // while 2D mesher case it will generate automatically.
  void AddRegionEtypes(int etype);
  void AddUniqEtypeStr( string &);
  int  GetNumberOfEtypes(void);     // how many etypes  
  int  GetRegionalEtype(void);      // check there is only one element type
  int  GetBoundaryEtype(void);      // check there is only one element type
  int  IsOnlyOneEtype(void); 


  // usedNameLst  (check duplication in _CHECK routine)
  void AddUsedNameLst( string &);
  int  IsUsedName( string &);

  void SetSpaceDimension(int);
  int  GetSpaceDimension(void) { return dimension; }
  void AddGeomObj( GeomObj *);

  int GetGeomObjTypeByName( string &);
  GeomObj *GetGeomObjByName(string &);

  // for Assignment Geometry
  int IsValidAssignPlace(int geomType, int placeFlag );
  int IsValidAssignmentGeometry( int varType, int geomType );

  // for Boundary Geometry
  int IsValidNeumannBoundary(int);   // if given type code is valid neumann?
  NeumannGeom   *AcquireNeumannGeomByName(GeomObj *);   // if undef make new
  DirichletGeom *AcquireDirichletGeomByName(GeomObj *); // if undef make new

  list <DirichletGeom *>&GetDirichletGeomLst(void) {
    return dBGeomPtrLst;
  }
  list <NeumannGeom *>&GetNeumannGeomLst(void) {
    return nBGeomPtrLst;
  }
  list <GeomObj *>&GetGeomObjLst(void) {
    return geomObjPtrLst;
  }

  int HowManyNeumannGeoms(void)  { return neumannGeoms;   }
  int HowManyDirichletGeoms(void){ return dirichletGeoms; }

  
  // currently, used for GiD class
  const char *GetProblemName(void) const {
    return ( (const char *)problemName );
  }

  // RegionObject
  int GetNumberOfRegionObjects(void);
  void SetRegionObjects(int);
  void AddRegionObjectPtr(RegionObject *);
  int IsRegionObjectName( string &);
  RegionObject *GetRegionObjectPtrByName(string &);
  void StoreAssociateMaterialRegionStrLst(string &,list <string> &);
  list <RegionObject *>&GetRegionObjectPtrList(void) {
    return rObjPtrLst;
  }



  

private:

  int dimension;

  string mesherName;
  Mesher *mesherPtr;

  string problemName;          // for GiD

  list <string>   usedNameLst;   // used for checking 
  list <GeomObj *>geomObjPtrLst;
  //  list <BGeom *>  bgeomPtrLst;

  int   dirichletGeoms;
  int   neumannGeoms;
  list <DirichletGeom *>dBGeomPtrLst;
  list <NeumannGeom   *>nBGeomPtrLst;

  // for region (02/11/06)
  int   regionObjects;
  list <RegionObject *> rObjPtrLst;

  int       regionEtypes;
  list <int>regionEtypeLst;

};

#endif
