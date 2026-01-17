/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : Tezuk.hpp
 *  Date     : 2002/10/22
 *  Modified : 
 *  
 *  Purpose  : interface to 2D mesh generator BAMG
 *  
 */

#ifndef FEM_CLASS_TEZUK
#define FEM_CLASS_TEZUK

#include <stdio.h>

#include "ptrList.hpp"
#include "string.hpp"

#include "Mesher.hpp"

class Point;
class Edge;
class Polygon;
class PolygonalRegion;

class TezukPoint {
public:
  TezukPoint(Point *,int);   // Point structure and vertices No.
  ~TezukPoint();

  int getOriginalRefNo(void) { return(refNo);     }
  int getTezukRefNo    (void) { return(tezukRefNo); }
  double getX(void)          { return(x); }
  double getY(void)          { return(y); }
  

  
private:
  double x,y;
  int    refNo;             // Original reference No.
  int    type;              // Original type

  int    tezukRefNo;         // Reference No. in Tezuk
  int    onEdgeFlag;        // If on geometrical edge, YES, otherwise NO
};


class TezukEdge {
public:
  TezukEdge(int tezukFrom,int tezukTo,int tezukRefNo);
  ~TezukEdge();

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

  int getTezukRefNo(void) {
    return(tezukEdgeRefNo);
  }


private:
  int from,to;
  int refNo;               // original reference no
  int tezukEdgeRefNo;       // local edge number in TEZUK
};


class TezukSubDomain {
public:
  TezukSubDomain(int edgeNo, int dir, int mno);
  ~TezukSubDomain();

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



class Tezuk : public Mesher {
public:  
  Tezuk();
  ~Tezuk();

  void makeTezukGeom( char *filename );   // generate geometry file



  void addVertices ( Point * );
  //  void addVertices ( double ,double , int);  // future generalization

  void addBoundaryEdge    ( Edge  * );

  // Tezuk correspondance of Edges
  void addTezukEdgeByPolygonalRegion( PolygonalRegion *);   
  void addTezukEdgeByPolygon(Polygon *);
  void addTezukEdgeBy2OriginalRefNo(int , int );   // with numbering to edge
  int  getTezukEdgeRefNoFrom2OriginalRefNo(int ,int );
  // ^^^^^^^^^ direction is given by +-

  void addTezukSubDomainByPolygonalRegion( PolygonalRegion *);



  int  getTezukPointRefNoFromOriginalRefNo( int );

  // interface SN object to Tezuk standard method


  // Execute command
  void execTezuk( const char *, const char *);

  // Reading functions
  void readTezukMesh( const char *filename );   // read Tezuk mesh file


  // Debug draw
  void DebugPrintTezukMesh(void);
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

  int tezukRefNoMaster;

  int  tezukVertices;
  int isolatePoints;          // isolated points (not on edges)
  list <TezukPoint *>tezukPointPtrLst;

  int  tezukEdges;                 // number of initial edges
  list <TezukEdge  *>tezukEdgePtrLst;

  //  double *Vert_x,*Vert_y;     // information of coordinates of initial 
  //  int    *Vert_n;
  int tezukSubDomains;
  list <TezukSubDomain *>tezukSubDomainPtrLst;


  // Reading tezuk.mesh file  
  void readTezukMeshVersionFormatted(FILE *);
  int tezukMeshVersion;           // read in readTezukMeshVersionFormatted()

  void readTezukDimension(FILE *);
  int tezukMeshDimension;         // read in readTezukDimension

  void readTezukGeometry(FILE *);
  string tezukGeometryFilename;   // read in readTezukGeometry

  void readTezukIdentifier(FILE *);
  string tezukIdentifierNotice;   // read in readTezukIdentifier

  // Vertices                       read in readTezukVertices
  void readTezukVertices(FILE *);
  int tezukMeshVertices;
  double *xBM,*yBM;
  int    *nodeTypeBM;
  double  xMaxBM,xMinBM,yMaxBM,yMinBM;  // set in reading

  // Edges                          read in readTezukEdges
  void readTezukEdges(FILE *);
  int tezukMeshEdges;
  int *fromEdgeBM,*toEdgeBM,*typeEdgeBM;

  // Triangles                      read in readTezukTriangles
  void readTezukTriangles(FILE *);
  int tezukMeshTriangles;
  int *ielemTriBM,*matnoTriBM;

  // SubDomain
  void readTezukSubDomainFromMesh(FILE *);
  int tezukMeshSubDomains;
  int *subDomTypeBM,*subDomNoBM,*subDomDirectionBM,*subDomMatnoBM;

  void readTezukSubDomainFromGeom(FILE *);  // this must be same in geometry
  int tezukMeshSubDomainsGEOM;
  int *subDomTypeGM,*subDomNoGM,*subDomDirectionGM,*subDomMatnoGM;

  void readTezukVertexOnGeometricVertex(FILE *fp);
  int tezukMeshVerticesOnGeometricVertex;
  int *meshVNo_geomVNo;                   // mesh vertex no vs geom vertex no

  void readTezukVertexOnGeometricEdge(FILE *fp);
  int tezukMeshVerticesOnGeometricEdge;
  int *meshVNo_geomENo;                   // mesh vertex No vs geom Edge no
  double *meshVNoPosInGeomEdge;           // position parameter in geom Edge

  void readTezukEdgeOnGeometricEdge(FILE *fp);
  int tezukMeshEdgesOnGeometricEdge;
  int *meshENo_geomENo;
};



#endif

