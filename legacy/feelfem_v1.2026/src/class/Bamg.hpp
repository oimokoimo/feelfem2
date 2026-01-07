/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : Bamg.hpp
 *  Date     : 2001/03/30
 *  Modified : 
 *  
 *  Purpose  : interface to 2D mesh generator BAMG
 *  
 */

#ifndef FEM_CLASS_BAMG
#define FEM_CLASS_BAMG

#include <stdio.h>

#include "ptrList.hpp"
#include "string.hpp"

#include "Mesher.hpp"

class Point;
class Edge;
class Polygon;
class PolygonalRegion;

class BamgPoint {
public:
  BamgPoint(Point *,int);   // Point structure and vertices No.
  ~BamgPoint();

  int getOriginalRefNo(void) { return(refNo);     }
  int getBamgRefNo    (void) { return(bamgRefNo); }
  double getX(void)          { return(x); }
  double getY(void)          { return(y); }
  

  
private:
  double x,y;
  int    refNo;             // Original reference No.
  int    type;              // Original type

  int    bamgRefNo;         // Reference No. in Bamg
  int    onEdgeFlag;        // If on geometrical edge, YES, otherwise NO
};


class BamgEdge {
public:
  BamgEdge(int bamgFrom,int bamgTo,int bamgRefNo);
  ~BamgEdge();

  int isSameEdge(int from, int to);   // ordering ignored.

  int getFrom(void) {
    if(from > to) return to;
    else          return from;
  }
  int getTo(void) {
    if(from > to) return from;
    else          return to;
  }

  int getOriginalRefNo(void) {
    return(refNo);
  }

  int getBamgRefNo(void) {
    return(bamgEdgeRefNo);
  }


private:
  int from,to;
  int refNo;               // original reference no
  int bamgEdgeRefNo;       // local edge number in BAMG
};


class BamgSubDomain {
public:
  BamgSubDomain(int edgeNo, int dir, int mno);
  ~BamgSubDomain();

  int getType() { return (type); }
  int getEdgeRefNo() { return (referenceEdgeNo); }
  int getDirection() { return (direction); }
  int getMatno() { return(matno); }

  void setArea(double a) { area = a; }
  double getArea(void) {  return(area); }

private:
  int type;                 // now 2 only (it means LINE)
  int referenceEdgeNo;      // Edge No.
  int direction;            // Direction
  int matno;                // material No.

  double area;              // area
};



class Bamg : public Mesher {
public:  
  Bamg();
  ~Bamg();

  void makeBamgGeom( char *filename );   // generate geometry file



  void addVertices ( Point * );
  //  void addVertices ( double ,double , int);  // future generalization

  void addBoundaryEdge    ( Edge  * );

  // Bamg correspondance of Edges
  void addBamgEdgeByPolygonalRegion( PolygonalRegion *);   
  void addBamgEdgeByPolygon(Polygon *);
  void addBamgEdgeBy2OriginalRefNo(int , int );   // with numbering to edge
  int  getBamgEdgeRefNoFrom2OriginalRefNo(int ,int );
  // ^^^^^^^^^ direction is given by +-

  void addBamgSubDomainByPolygonalRegion( PolygonalRegion *);



  int  getBamgPointRefNoFromOriginalRefNo( int );

  // interface SN object to Bamg standard method


  // Execute command
  void execBamg( const char *, const char *);

  // Reading functions
  void readBamgMesh( const char *filename );   // read Bamg mesh file


  // Debug draw
  void DebugPrintBamgMesh(void);
  void DebugDrawMesh(void);

  void setSpecifiedVertices(int n) { specifiedVertices = n; return; }
  int  getSpecifiedVertices(int n) { return(specifiedVertices) ; }

private:

  int dimension;              // it should be 2
  int maximalAngleOfCorner;   // it should be greater than 90
  //  int corners;                // corners in initial geometry
  int elementType;            // ELEMENT_TYPE_TRI or ELEMENT_TYPE_RECT

  int specifiedVertices;      // User specified vertices

  int refNoCounter;

  int bamgRefNoMaster;

  int  bamgVertices;
  int isolatePoints;          // isolated points (not on edges)
  list <BamgPoint *>bamgPointPtrLst;

  int  bamgEdges;                 // number of initial edges
  list <BamgEdge  *>bamgEdgePtrLst;

  //  double *Vert_x,*Vert_y;     // information of coordinates of initial 
  //  int    *Vert_n;
  int bamgSubDomains;
  list <BamgSubDomain *>bamgSubDomainPtrLst;


  // Reading bamg.mesh file  
  void readBamgMeshVersionFormatted(FILE *);
  int bamgMeshVersion;           // read in readBamgMeshVersionFormatted()

  void readBamgDimension(FILE *);
  int bamgMeshDimension;         // read in readBamgDimension

  void readBamgGeometry(FILE *);
  string bamgGeometryFilename;   // read in readBamgGeometry

  void readBamgIdentifier(FILE *);
  string bamgIdentifierNotice;   // read in readBamgIdentifier

  // Vertices                       read in readBamgVertices
  void readBamgVertices(FILE *);
  int bamgMeshVertices;
  double *xBM,*yBM;
  int    *nodeTypeBM;
  double  xMaxBM,xMinBM,yMaxBM,yMinBM;  // set in reading

  // Edges                          read in readBamgEdges
  void readBamgEdges(FILE *);
  int bamgMeshEdges;
  int *fromEdgeBM,*toEdgeBM,*typeEdgeBM;

  // Triangles                      read in readBamgTriangles
  void readBamgTriangles(FILE *);
  int bamgMeshTriangles;
  int *ielemTriBM,*matnoTriBM;

  // SubDomain
  void readBamgSubDomainFromMesh(FILE *);
  int bamgMeshSubDomains;
  int *subDomTypeBM,*subDomNoBM,*subDomDirectionBM,*subDomMatnoBM;

  void readBamgSubDomainFromGeom(FILE *);  // this must be same in geometry
  int bamgMeshSubDomainsGEOM;
  int *subDomTypeGM,*subDomNoGM,*subDomDirectionGM,*subDomMatnoGM;

  void readBamgVertexOnGeometricVertex(FILE *fp);
  int bamgMeshVerticesOnGeometricVertex;
  int *meshVNo_geomVNo;                   // mesh vertex no vs geom vertex no

  void readBamgVertexOnGeometricEdge(FILE *fp);
  int bamgMeshVerticesOnGeometricEdge;
  int *meshVNo_geomENo;                   // mesh vertex No vs geom Edge no
  double *meshVNoPosInGeomEdge;           // position parameter in geom Edge

  void readBamgEdgeOnGeometricEdge(FILE *fp);
  int bamgMeshEdgesOnGeometricEdge;
  int *meshENo_geomENo;
};



#endif

