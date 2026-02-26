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
#include <cstdio>

#include "Bamg.hpp"

void Bamg::DebugPrintBamgMesh(void)
{
  std::cerr << "bamgMeshVersion = " << bamgMeshVersion << std::endl;
  
  std::cerr << "bamgMeshDimension = " << bamgMeshDimension << std::endl;

  std::cerr << "BamgGeometry = " << bamgGeometryFilename  << std::endl;

  std::cerr << "BamgIdentifier = " << bamgIdentifierNotice << std::endl;


  std::cerr << "BamgVertices = " << bamgMeshVertices << std::endl;

  std::cerr << "BamgEdges = " << bamgMeshEdges << std::endl;

  std::cerr << "BamgTriangles = " << bamgMeshTriangles << std::endl;

  std::cerr << "BamgSubDomainFromMesh = " <<  bamgMeshSubDomains << std::endl;

  std::cerr << "BamgSubDomainFromGeom = " <<  bamgMeshSubDomainsGEOM << std::endl;

  std::cerr << "BamgVertexOnGeometricVertex = " << bamgMeshVerticesOnGeometricVertex << std::endl;

  std::cerr << "BamgVertexOnGeometricEdge = " << bamgMeshVerticesOnGeometricEdge << std::endl;
  
  std::cerr << "BamgEdgeOnGeometricEdge = " <<bamgMeshEdgesOnGeometricEdge << std::endl;
  
  return;
}
