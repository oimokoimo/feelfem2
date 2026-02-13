/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : Geometry.hpp
 *  Date     : 2001/04/03
 *  Modified : 
 *  
 *  Purpose  : Geometry object
 *             All geometric numbering is done while stored in this class
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

#ifndef FEM_CLASS_GEOMETRY
#define FEM_CLASS_GEOMETRY

#include "ptrList.hpp"
#include "string.hpp"

class Point;
class Edge;
class PolygonalRegion;
class Domain;

// mesh generator dependent
class Bamg;                   

class Geometry {
public:
  Geometry();
  ~Geometry();

  void SetDimension(int n) { dimension = n; return; }
  int  GetSpaceDimension(void) { return dimension; }
  void AddPointPtr(Point *);  // add uniq number to each point
  void AddEdgePtr(Edge *);  // add uniq number to each point
  void AddPolygonalRegionPtr(PolygonalRegion *);  // add uniq number to each point

  Point *GetPointPtrByName( const char * ); // if not exist return NULLp
  Edge  *GetEdgePtrByName( const char * );  // if not exist return NULLp

  void setVertices( int v ) { vertices = v; }
  int  getVertices( void  ) { return(vertices); }
    

  // Mesh generator interface

  // Implement in Geometry/BamgInterface.cpp
  void BamgGeomSet    ( Bamg * );  // main routine to call following funcs.
  void BamgPointSet   ( Bamg * );
  void BamgBamgEdgeSet( Bamg * );
  void BamgSubDomainSet( Bamg *);

  double getMaximumArea2D( void )
  {
    return( (xmax-xmin) * (ymax-ymin) );
  }
  double getApproximateH2D( void );


  // Following functions are called from SNpedge.cpp
  // In case of that extreme points are on parametric edge....
  void candidateXMax(double x) {
    if( x > xmax) xmax = x;
  }
  void candidateYMax(double y) {
    if( y > ymax) ymax = y;
  }
  void candidateZMax(double z) {
    if( z > zmax) zmax = z;
  }
  void candidateXMin(double x) {
    if( x > xmax) xmax = x;
  }
  void candidateYMin(double y) {
    if( y > ymax) ymax = y;
  }
  void candidateZMin(double z) {
    if( z > zmax) zmax = z;
  }
  
  void GenerateGeometryObject();

private:

  int dimension;

  int points;
  list <Point *>pointPtrLst;
  double xmin,xmax;               // set in AddPointPtr
  double ymin,ymax;
  double zmin,zmax;

  string mesherName;

  int edges;
  list <Edge *>edgePtrLst;

  int faces;
  //  ptrList <Face *>facePtrLst;

  int volumes;
  //  ptrList <Volume *>volumePtrLst;

  // 2 dimensional only
  int regions;
  list <PolygonalRegion *>polygonalRegionPtrLst;

  int domains;
  //  ptrList <Domain *>domainPtrLst;

  int vertices;   // from vertices(NNN);

  // Geometry used in scheme block

  int solveRegions;    // number of solve EDAT set
  int boundaryEdges;   // 

};

#endif
