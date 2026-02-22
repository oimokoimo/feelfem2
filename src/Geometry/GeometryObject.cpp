/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : GeometryObject.cpp
 *  Date     : 2002/03/14
 *  Modified : 2002/11/07 (   AddUniqEtypeStr(string &);  )
 *                            
 *  
 *  
 *  Purpose  :
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

#include <iostream>
#include <cassert>

#include "feeldef.hpp"

#include "GeometryObject.hpp"
#include "SurfaceObject.hpp"
#include "EdgeObject.hpp"
#include "PointObject.hpp"
#include "RegionObject.hpp"
#include "GeomObj.hpp"

#include "NeumannGeom.hpp"
#include "DirichletGeom.hpp"

GeometryObject feelfemgeomobj;

int GeomObj::geomObjNo       = 0;
int SurfaceObject::surfaceNo = 0;
int PointObject::pointNo     = 0;
int EdgeObject::edgeNo       = 0;
int RegionObject::regionNo   = 0;

GeometryObject::GeometryObject(void)
{
  problemName = DEFAULT_GOBJ_PROBLEM_NAME;

  dimension   = 2;

  mesherPtr   = 0;

  dirichletGeoms = 0;
  neumannGeoms   = 0;

  regionObjects  = 0;

  regionEtypes   = 0;

  return;
}

GeometryObject::~GeometryObject() = default;

void GeometryObject::SetSpaceDimension(int n)
{
  dimension = n;
  return;
}

void GeometryObject::AddGeomObj(GeomObj *goPtr)
{
  geomObjPtrLst.addlast(goPtr);
  return;
}


int GeometryObject::IsUsedName(string &nm)
{
  if(usedNameLst.includes(nm)) return(YES);
  
  return(NO);
}

void GeometryObject::AddUsedNameLst(string &nm)
{
  usedNameLst.addlast(nm);
  return;
}

void GeometryObject::SetMesherName(string &nm)
{
  mesherName = nm;
  return;
}

void GeometryObject::SetProblemName(string &nm)
{
  problemName = nm;
  return;
}

void GeometryObject::SetMesherPtr( Mesher *ptr)
{
  mesherPtr = ptr;
  return;
}


int GeometryObject::GetGeomObjTypeByName( string &name )
{
  listIterator <GeomObj *>itr(geomObjPtrLst);

  for(itr.init(); !itr ; ++itr ){
    
    if(itr()->IsNameIs(name) == YES) {
      return(itr()->GetType());
    }
  }
  std::cerr << "No object found......\n";
  assert(1==0);
  return(0);
}

GeomObj *GeometryObject::GetGeomObjByName(string &name)
{
  listIterator <GeomObj *>itr(geomObjPtrLst);

  for(itr.init(); !itr ; ++itr ){
    if(itr()->IsNameIs(name) == YES) {
      return(itr());
    }
  }
  std::cerr << "No object found......\n";
  assert(1==0);
  return(0);
}

int GeometryObject::IsValidNeumannBoundary(int code)
{
  if(dimension == 3 && code == GOBJ_SURFACE ) return(YES);
  if(dimension == 2 && code == GOBJ_EDGE    ) return(YES);
  
  return(NO);
}

//assignement
int GeometryObject::IsValidAssignPlace(int geomType, int placeFlag )
{
  if(placeFlag == SN_ASSIGNMENT_AT ) {
    if(geomType == GOBJ_POINT) return(YES);
    return(NO);
  }
  
  if(placeFlag == SN_ASSIGNMENT_ON ) {
	  std::cerr << "on is not supported in current version." << std::endl;
	  std::cerr << "GeometryObject::IsValidAssignPlace\n";
    return(NO); 
  }
  
  if(placeFlag == SN_ASSIGNMENT_IN ) {
    if(geomType == GOBJ_REGION) return(YES);
    return(NO);
  }

  std::cerr << "placeFlag(GeometryObject::IsValidAssignPlace)=" 
       << placeFlag << std::endl;   
  return(NO);
}
  
int GeometryObject::IsValidAssignmentGeometry( int varType,
					       int geomType  )
{
  switch(varType) {

    // scalar variable
  case VAR_DOUBLE:
  case VAR_INT:
    if(geomType        == GOBJ_POINT ) {
      return(YES);
    }
    else {
      return(NO);
    }
    break;

  case VAR_EWISE:
  case VAR_EWISE_A:
    if(geomType       == GOBJ_REGION ) {
      return(YES);
    }
    else {
      return(NO);
    }
    break;

  case VAR_FEM:
    if(geomType  == GOBJ_REGION || geomType == GOBJ_POINT) {
      return(YES);
    }
    else {
      return(NO);
    }

  default:
    assert(1==0);  // VFEM, CONST
  }
  
  return(NO);
}
 
NeumannGeom *GeometryObject::AcquireNeumannGeomByName(GeomObj *goPtr)
{
  string nm = goPtr->GetName();
  
  listIterator <NeumannGeom *>itr(nBGeomPtrLst);
  for(itr.init(); !itr ; ++itr) {
    if(itr()->IsNameIs(nm) == YES) {
      return(itr());
    }
  }

  NeumannGeom *ngPtr = new NeumannGeom( goPtr );
  nBGeomPtrLst.addlast(ngPtr);
  neumannGeoms++;

  return(ngPtr);
}


DirichletGeom *GeometryObject::AcquireDirichletGeomByName(GeomObj *goPtr)
{
  string nm = goPtr->GetName();

  listIterator <DirichletGeom *>itr(dBGeomPtrLst);
  for(itr.init(); !itr ; ++itr) {
    if(itr()->IsNameIs(nm) == YES) {
      return(itr());
    }
  }

  DirichletGeom *dgPtr = new DirichletGeom( goPtr );
  dBGeomPtrLst.addlast(dgPtr);
  dirichletGeoms++;

  return(dgPtr);
}

void GeometryObject::AddRegionObjectPtr(RegionObject *roPtr)
{
  rObjPtrLst.addlast(roPtr);
  return;
}

void GeometryObject::SetRegionObjects( int n)
{
  regionObjects = n;
  return;
}

int  GeometryObject::GetNumberOfEtypes(void)
{
  return(regionEtypes);
}


int  GeometryObject::GetNumberOfRegionObjects(void)
{
  return(regionObjects);
}

int GeometryObject::IsRegionObjectName(string &nm)
{
  listIterator <RegionObject *>itr(rObjPtrLst);
  for(itr.init(); !itr ; ++itr) {
    if( nm == itr()->GetName() ) return(YES);
  }
  return(NO);
}

RegionObject *GeometryObject::GetRegionObjectPtrByName( string &nm)
{
  listIterator <RegionObject *>itr(rObjPtrLst);
  for(itr.init(); !itr ; ++itr) {
    if( nm == itr()->GetName() ) {
      return (itr());
    }
  }
  std::cerr << "There is no RegionObject with specified name." << std::endl;
  assert(1==0);
}

void GeometryObject::StoreAssociateMaterialRegionStrLst(string &materialName,
							list<string>&lst     )
{
  listIterator <RegionObject *>itr(rObjPtrLst);
  for(itr.init(); !itr ; ++itr) {
    if( itr()->HasMaterialAttribute( materialName ) ) {
      const char *nm = itr()->GetName();
      lst.addlast(nm);
    }
  }  
  return;
}


void GeometryObject::AddUniqEtypeStr(string &etypeName)
{
  int etype = -1;  // -1 means error

  if(etypeName == ETYPE_POINT_NAME) { etype = ELEMENT_TYPE_POINT;}
  if(etypeName == ETYPE_LINE_NAME ) { etype = ELEMENT_TYPE_LINE ;}
  if(etypeName == ETYPE_TRI_NAME  ) { etype = ELEMENT_TYPE_TRI  ;}
  if(etypeName == ETYPE_RECT_NAME ) { etype = ELEMENT_TYPE_RECT ;}
  if(etypeName == ETYPE_TETRA_NAME) { etype = ELEMENT_TYPE_TETRA;}
  if(etypeName == ETYPE_CUBE_NAME ) { etype = ELEMENT_TYPE_CUBE ;}

  assert(etype != -1);

  if(regionEtypeLst.includes(etype)) {
    return;
  }
  else {
    regionEtypes++;
    regionEtypeLst.add(etype);
  }

  return;
}

// integral, bintegral 
int GeometryObject::IsOnlyOneEtype(void)
{
  if(regionEtypes==1) {
    return(YES);
  }
  return(NO);
}

int GeometryObject::GetRegionalEtype(void)
{
  assert(regionEtypes==1);

  int ret = regionEtypeLst.getNthElement(1);
  
  return(ret);
}
  
