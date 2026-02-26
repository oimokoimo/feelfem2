/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : readBamgMesh.cpp
 *  Date     : 2001/04/10
 *  Modified : 
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

#include <cassert>
#include <cstdio>
#include "feelfuncs.hpp"       // abortExit();
#include "Bamg.hpp"
#include "string.hpp"

void Bamg::readBamgMesh( const char *filename)
{
  FILE *fp;
  char key[BUFSIZ];
  
  fp = fopen(filename,"r");
  if(fp == NULL) {
    abortExit("Cannot open bamg mesh file to read");
  }

  while(fscanf(fp,"%s",key) != EOF) {

    if(1 == strindex(key,"MeshVersionFormatted")) {
      readBamgMeshVersionFormatted(fp);
      continue;

    }
    if(1 == strindex(key,"Dimension")) {
      readBamgDimension(fp);
      continue;
    }

    if(1 == strindex(key,"Identifier")) {
      readBamgIdentifier(fp);
      continue;
    }

    if(1 == strindex(key,"Geometry")) {
      readBamgGeometry(fp);
      continue;
    }

    if(1 == strindex(key,"Vertices")) {
      readBamgVertices(fp);
      continue;
    }

    if(1 == strindex(key,"Edges")) {
      readBamgEdges(fp);
      continue;
    }

    if(1 == strindex(key,"End")){
      fclose(fp);
      return;
    }

    if(1 == strindex(key,"Triangles")) {
      readBamgTriangles(fp);
      continue;
    }

    if(1 == strindex(key,"SubDomainFromMesh")) {
      readBamgSubDomainFromMesh(fp);
      continue;
    }

    if(1 == strindex(key,"SubDomainFromGeom")) {
      readBamgSubDomainFromGeom(fp);
      continue;
    }

    if(1 == strindex(key,"VertexOnGeometricVertex")) {
      readBamgVertexOnGeometricVertex(fp);
      continue;
    }

    if(1 == strindex(key,"VertexOnGeometricEdge")) {
      readBamgVertexOnGeometricEdge(fp);
      continue;
    }
    
    if(1 == strindex(key,"EdgeOnGeometricEdge")) {
      readBamgEdgeOnGeometricEdge(fp);
      continue;
    }

    /* END OF BAMG mesh data */ 
    if(1 == strindex(key,"End")){
      fclose(fp);
      return;
    }

    /* UNKNOWN keyword */
    fprintf(stderr,"Not supported BAMG keyword [%s]\n",key);
  }

  fclose(fp);
  abortExit("Unexpected end of file for BAMG mesh.");
}

void Bamg::readBamgMeshVersionFormatted(FILE *fp)
{
  fscanf(fp,"%d",&bamgMeshVersion);
  return;
}

void Bamg::readBamgDimension(FILE *fp)
{
  fscanf(fp,"%d",&bamgMeshDimension);
  return;
}

void Bamg::readBamgGeometry(FILE *fp)
{
  char buf[BUFSIZ];
  fgets(buf,sizeof(buf),fp);   // skip is necessary

  fgets(buf,sizeof(buf),fp);
  bamgGeometryFilename = buf;

  return;
}

void Bamg::readBamgIdentifier(FILE *fp)
{
  char buf[BUFSIZ];

  fgets(buf,sizeof(buf),fp);  // skip is necessary

  fgets(buf,sizeof(buf),fp);
  bamgIdentifierNotice = buf;

  return;
}


void Bamg::readBamgVertices(FILE *fp)
{
  fscanf(fp,"%d",&bamgMeshVertices);
  assert(bamgMeshVertices>0);

  xBM        = new double[bamgMeshVertices];
  yBM        = new double[bamgMeshVertices];
  nodeTypeBM = new int   [bamgMeshVertices];

  assert( xBM        != 0);
  assert( yBM        != 0);
  assert( nodeTypeBM != 0);

  for(int i=0;i<bamgMeshVertices;i++) {
    fscanf(fp,"%lf %lf %d",xBM+i,yBM+i,nodeTypeBM+i);
  }
  xMaxBM = *(xBM);
  xMinBM = *(xBM);
  yMaxBM = *(yBM);
  yMinBM = *(yBM);

  for(int i=1;i<bamgMeshVertices;i++) {
    if(xMaxBM < *(xBM+i)) xMaxBM = *(xBM+i);
    if(yMaxBM < *(yBM+i)) yMaxBM = *(yBM+i);
    if(xMinBM > *(xBM+i)) xMinBM = *(xBM+i);  
    if(yMinBM > *(yBM+i)) yMinBM = *(yBM+i);  
  }

  return;
}

void Bamg::readBamgEdges(FILE *fp)
{
  fscanf(fp,"%d",&bamgMeshEdges);
  assert(bamgMeshEdges>0);

  fromEdgeBM = new int[bamgMeshEdges];
  toEdgeBM   = new int[bamgMeshEdges];
  typeEdgeBM = new int[bamgMeshEdges];

  assert(fromEdgeBM != 0);
  assert(toEdgeBM   != 0);
  assert(typeEdgeBM != 0);

  for(int i=0;i<bamgMeshEdges;i++) {
    fscanf(fp,"%d %d %d",fromEdgeBM+i,toEdgeBM+i,typeEdgeBM+i);
  }
  return;
}  

void Bamg::readBamgTriangles(FILE *fp)
{
  fscanf(fp,"%d",&bamgMeshTriangles);
  assert(bamgMeshTriangles>0);

  ielemTriBM = new int[bamgMeshTriangles*3];
  matnoTriBM = new int[bamgMeshTriangles  ];

  assert(ielemTriBM != 0);
  assert(matnoTriBM != 0);

  for(int i=0;i<bamgMeshTriangles;i++) {
    fscanf(fp,"%d %d %d %d",
	   ielemTriBM+(i*3),ielemTriBM+(i*3)+1,ielemTriBM+(i*3)+2,
	   matnoTriBM+ i);
  }
  return;
}

void Bamg::readBamgSubDomainFromMesh(FILE *fp)
{
  //  int *tndm;       /* type,number,direction,matno */
  fscanf(fp,"%d",&bamgMeshSubDomains);
  assert(bamgMeshSubDomains>0);

  subDomTypeBM      = new int[bamgMeshSubDomains];
  subDomNoBM        = new int[bamgMeshSubDomains];
  subDomDirectionBM = new int[bamgMeshSubDomains];
  subDomMatnoBM     = new int[bamgMeshSubDomains];

  assert(subDomTypeBM      != 0);
  assert(subDomNoBM        != 0);
  assert(subDomDirectionBM != 0);
  assert(subDomMatnoBM     != 0);

  for(int i=0;i<bamgMeshSubDomains;i++) {
    fscanf(fp,"%d %d %d %d",subDomTypeBM+i,subDomNoBM+i,
	   subDomDirectionBM+i,subDomMatnoBM+i);
  }
}

void Bamg::readBamgSubDomainFromGeom(FILE *fp)
{
  /* Be CAREFUL,  This is from GEOMETRY  */
  fscanf(fp,"%d",&bamgMeshSubDomainsGEOM);
  assert(bamgMeshSubDomainsGEOM>0);

  subDomTypeGM      = new int[bamgMeshSubDomainsGEOM];
  subDomNoGM        = new int[bamgMeshSubDomainsGEOM];
  subDomDirectionGM = new int[bamgMeshSubDomainsGEOM];
  subDomMatnoGM     = new int[bamgMeshSubDomainsGEOM];

  assert(subDomTypeGM      != 0);
  assert(subDomNoGM        != 0);
  assert(subDomDirectionGM != 0);
  assert(subDomMatnoGM     != 0);

  for(int i=0;i<bamgMeshSubDomains;i++) {
    fscanf(fp,"%d %d %d %d",subDomTypeGM+i,subDomNoGM+i,
	   subDomDirectionGM+i,subDomMatnoGM+i);
  }
}

void Bamg::readBamgVertexOnGeometricVertex(FILE *fp)
{
  fscanf(fp,"%d",&bamgMeshVerticesOnGeometricVertex);

  if(bamgMeshVerticesOnGeometricVertex == 0) {
    fprintf(stderr,"Warrning :: no Vertices on Geometric Vertex\n");
    return;
  }

  assert(bamgMeshVerticesOnGeometricVertex > 0);
  
  meshVNo_geomVNo = new int[bamgMeshVerticesOnGeometricVertex*2];
  assert(meshVNo_geomVNo != 0);

  for(int i=0;i<bamgMeshVerticesOnGeometricVertex;i++) {
    fscanf(fp,"%d %d",meshVNo_geomVNo+(i*2),meshVNo_geomVNo+(i*2+1));
  }
  return;
}

void Bamg::readBamgVertexOnGeometricEdge(FILE *fp)
{
  fscanf(fp,"%d",&bamgMeshVerticesOnGeometricEdge);
  
  if(bamgMeshVerticesOnGeometricEdge==0) {
    fprintf(stderr,"Warnning: no vertices on geometric edge\n");
    return;
  }
  
  assert(bamgMeshVerticesOnGeometricEdge>0);

  meshVNo_geomENo      = new int   [bamgMeshVerticesOnGeometricEdge*2];
  meshVNoPosInGeomEdge = new double[bamgMeshVerticesOnGeometricEdge  ];

  assert(meshVNo_geomENo      != 0);
  assert(meshVNoPosInGeomEdge != 0);

  for(int i=0;i<bamgMeshVerticesOnGeometricEdge;i++) {
    fscanf(fp,"%d %d %lf",meshVNo_geomENo+(i*2),meshVNo_geomENo+(i*2+1),
	   meshVNoPosInGeomEdge+i);
  }
  return;
}

void Bamg::readBamgEdgeOnGeometricEdge(FILE *fp)
{
  fscanf(fp,"%d",&bamgMeshEdgesOnGeometricEdge);
  assert(bamgMeshEdgesOnGeometricEdge>0);

  meshENo_geomENo = new int[bamgMeshEdgesOnGeometricEdge*2];
  assert(meshENo_geomENo != 0);

  for(int i=0;i<bamgMeshEdgesOnGeometricEdge;i++) {
    fscanf(fp,"%d %d",meshENo_geomENo+(i*2),meshENo_geomENo+(i*2+1));
  }
  return;  
}
