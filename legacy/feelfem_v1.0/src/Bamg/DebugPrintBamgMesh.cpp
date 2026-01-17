/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : DebugPringBamgMesh.cpp
 *  Date     : 2001/04/10
 *  Modified : 
 *  
 *  Purpose  :
 *  
 */
#include <iostream.h>
#include <stdio.h>

#include "Bamg.hpp"

void Bamg::DebugPrintBamgMesh(void)
{
  cerr << "bamgMeshVersion = " << bamgMeshVersion << endl;
  
  cerr << "bamgMeshDimension = " << bamgMeshDimension << endl;

  cerr << "BamgGeometry = " << bamgGeometryFilename  << endl;

  cerr << "BamgIdentifier = " << bamgIdentifierNotice << endl;


  cerr << "BamgVertices = " << bamgMeshVertices << endl;

  cerr << "BamgEdges = " << bamgMeshEdges << endl;

  cerr << "BamgTriangles = " << bamgMeshTriangles << endl;

  cerr << "BamgSubDomainFromMesh = " <<  bamgMeshSubDomains << endl;

  cerr << "BamgSubDomainFromGeom = " <<  bamgMeshSubDomainsGEOM << endl;

  cerr << "BamgVertexOnGeometricVertex = " << bamgMeshVerticesOnGeometricVertex << endl;

  cerr << "BamgVertexOnGeometricEdge = " << bamgMeshVerticesOnGeometricEdge << endl;
  
  cerr << "BamgEdgeOnGeometricEdge = " <<bamgMeshEdgesOnGeometricEdge << endl;
  
  return;
}
