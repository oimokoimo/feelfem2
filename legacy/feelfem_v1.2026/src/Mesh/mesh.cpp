/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : mesh.cpp
 *  Date     : 2001/04/06
 *  Modified : 
 *  
 *  Purpose  : mesh control (especially for 2D)
 *  
 */
#include "feelfem.hpp"
#include "feelfuncs.hpp"
#include "feeldef.hpp"
#include "mesh_funcs.hpp"

#include "Object.hpp"

void mesh()
{
  int mesherCode;

  mesherCode = feelfemobj.GetMesherCode();

  if( getSpaceDimension()== 2) {

    switch( mesherCode) {
    case MESH_GENERATOR_BAMG:
      mesh_exec_bamg();
      break;

    case MESH_GENERATOR_GID:
      mesh_exec_gid();
      break;


    default:
      abortExit("Unknown feelfem_mesh_generator value in Mesh/mesh.cpp");
    }
  }

  if( getSpaceDimension() == 3) {
    
    switch( mesherCode ) {
    case MESH_GENERATOR_GID:
      mesh_exec_gid();
      break;

    default:
      abortExit("Unknown feelfem_mesh_generator value in Mesh/mesh.cpp");
    }
  }
  return;
}
