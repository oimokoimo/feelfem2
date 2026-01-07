/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : mesh_exec_gid.cpp
 *  Date     : 2002/03/24
 *  Modified : 
 *  
 *  Purpose  :
 *  
 */

#include "GiD.hpp"

#include "feelfuncs.hpp"
#include "GeometryObject.hpp"

void mesh_exec_gid()
{
  GiD *gidPtr = new GiD;
  
  feelfemgeomobj.SetMesherPtr( gidPtr );


  gidPtr->GenerateCND();
  gidPtr->GenerateBAS();
  gidPtr->GenerateMAT();
  gidPtr->GeneratePRB();


  // solv_dat   also has dependency on feelfem90
  gidPtr->GenerateSolvDat();

  return;
}

  
