/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : GiD_BAS.cpp
 *  Date     : 2002/03/14
 *  Modified : 2002/03/25
 *  
 *  Purpose  : generate .bas file
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

#include "feeldef.hpp"
#include "feelfuncs.hpp"

#include "Object.hpp"
#include "GeometryObject.hpp"

#include "GiD.hpp"
#include "SurfaceObject.hpp"
#include "EdgeObject.hpp"
#include "PointObject.hpp"
#include "RegionObject.hpp"

#include "DirichletGeom.hpp"
#include "NeumannGeom.hpp"

#include "Variable.hpp"          // for initial doubles

void GiD::GenerateBAS(void)
{
  char fnamebuf[BUFSIZ];

  sprintf(fnamebuf,"%s.bas%c",(const char *)problemTypeName,'\0');
  
  FILE *fp;
  fp = fileOpenToWrite(fnamebuf);
  if(fp == NULL) {
    std::cerr << "Cannot open "<<fnamebuf << std::endl;
    return;
  }

  // Omajinai
  fprintf(fp,"*realformat \"%c12.5f\"\n",'%');
  fprintf(fp,"*intformat  \"%c8i\"\n",'%');


  // set boundary element


  // if 2 dimensional
  fprintf(fp,"*if(ndime==2)\n");

  // triangle linear

  fprintf(fp,"*if(nnode==3)\n");
  fprintf(fp,"*set var BNP=2\n");
  fprintf(fp,"*set var NETYPE=%d\n",ELEMENT_TYPE_TRI);     // triangle
  fprintf(fp,"*endif\n");

  // triangle quadratic
  fprintf(fp,"*if(nnode==6)\n");
  fprintf(fp,"*set var BNP=3\n");
  fprintf(fp,"*set var NETYPE=%d\n",ELEMENT_TYPE_TRI);     // triangle
  fprintf(fp,"*endif\n");

  // rectangle bilinear
  fprintf(fp,"*if(nnode==4)\n");
  fprintf(fp,"*set var BNP=2\n");
  fprintf(fp,"*set var NETYPE=%d\n",ELEMENT_TYPE_RECT);     // rectangle
  fprintf(fp,"*endif\n");

  // rectangle serendipity 8node
  fprintf(fp,"*if(nnode==8)\n");
  fprintf(fp,"*set var BNP=3\n");
  fprintf(fp,"*set var NETYPE=%d\n",ELEMENT_TYPE_RECT);     // rectangle
  fprintf(fp,"*endif\n");

  // rectangle quadratic
  fprintf(fp,"*if(nnode==9)\n");
  fprintf(fp,"*set var BNP=3\n");
  fprintf(fp,"*set var NETYPE=%d\n",ELEMENT_TYPE_RECT);     // rectangle
  fprintf(fp,"*endif\n");

  // end of *ndime == 2
  fprintf(fp,"*endif\n");


  fprintf(fp,"*if(ndime==3)\n");

  // tetrahedra linear
  fprintf(fp,"*if(nnode==4)\n");
  fprintf(fp,"*set var BNP=3\n");   // triangle
  fprintf(fp,"*set var NETYPE=%d\n",ELEMENT_TYPE_TETRA);     // tetrahedra
  fprintf(fp,"*endif\n");

  // tetrahedra quadratic
  fprintf(fp,"*if(nnode==10)\n");
  fprintf(fp,"*set var BNP=6\n");   // triangle
  fprintf(fp,"*set var NETYPE=%d\n",ELEMENT_TYPE_TETRA);     // tetrahedra
  fprintf(fp,"*endif\n");

  // cube bilinear
  fprintf(fp,"*if(nnode==8)\n");
  fprintf(fp,"*set var BNP=4\n");   // rectangle
  fprintf(fp,"*set var NETYPE=%d\n",ELEMENT_TYPE_CUBE);     // hexa
  fprintf(fp,"*endif\n");

  // cube C20
  fprintf(fp,"*if(nnode==20)\n");
  fprintf(fp,"*set var BNP=8\n");   // rectangle
  fprintf(fp,"*set var NETYPE=%d\n",ELEMENT_TYPE_CUBE);     // hexa
  fprintf(fp,"*endif\n");

  // cube complete quad
  fprintf(fp,"*if(nnode==27)\n");
  fprintf(fp,"*set var BNP=9\n");   // rectangle
  fprintf(fp,"*set var NETYPE=%d\n",ELEMENT_TYPE_CUBE);     // hexa
  fprintf(fp,"*endif\n");

  fprintf(fp,"*endif\n");   // end of if(ndime==3) 
  
  /////////////////////////////////////////////////////////////////////////
  // Start
  fprintf(fp,"FEELFEMGID\n");
  

  // information line, ndim,npmax,nedat,nnset,nnum,nip
  //                   ndim,npmax is given by GiD 
  
  int nedat = GID_LIMIT_REDAT +  feelfemgeomobj.HowManyNeumannGeoms();
  int nnset =                    feelfemgeomobj.HowManyDirichletGeoms();
  int nnum  =                    feelfemobj.HowManyInitialDoubles();
  int nip   =      0;   // point comes soon.


  fprintf(fp,"*ndime*npoin %7d %7d %7d %7d\n",nedat,nnset,nnum,nip);

  // two empty lines for compatibility
  fprintf(fp,"\n");
  fprintf(fp,"\n");

  // node 
  fprintf(fp,"NODE\n");
  fprintf(fp,"*loop nodes\n");

  
  if(feelfemgeomobj.GetSpaceDimension() == 2) {
    fprintf(fp,"*NodesNum*NodesCoord(1,real)*NodesCoord(2,real)\n");
  }
  else {
    fprintf(fp,"*NodesNum*NodesCoord(1,real)*NodesCoord(2,real)*NodesCoord(3,real)\n");
  }

  fprintf(fp,"*end nodes\n");
  fprintf(fp,"       0\n");
  fprintf(fp,"EDAT\n");
  fprintf(fp,"       1*nelem*nnode*NETYPE\n");   // netype is added
  fprintf(fp,"*loop elems\n");
  fprintf(fp,"*ElemsConec*ElemsMat\n");
  fprintf(fp,"*end elems\n");
  
  
  // for Dirichlet
  listIterator <DirichletGeom *>itrD(feelfemgeomobj.GetDirichletGeomLst());
  for(itrD.init(); !itrD ; ++itrD ){

    // NSET
    fprintf(fp,"NSET\n");

    // Set condition
    fprintf(fp,"*Set Cond %s",itrD()->GetName());
    if(itrD()->IsBothCondition()==YES) {
      fprintf(fp,"(d)");
    }
    fprintf(fp," *nodes\n");
      
    // set var
    fprintf(fp,"*set var ND(int)=CondNumEntities(int)\n");

    // NSET parameter
    fprintf(fp,"%8d*ND%8d\n",itrD()->GetDirichletGeomNo(),2); // oimokoimo

    // loop for nodes
    fprintf(fp,"*loop nodes *OnlyInCond\n");
    fprintf(fp,"*NodesNum       0\n");                        // oimokoimo
    fprintf(fp,"*end\n");
  }


  // Neumann EDAT set
  listIterator <NeumannGeom *>itrN(feelfemgeomobj.GetNeumannGeomLst());

  for(itrN.init(); !itrN ; ++itrN ){
    
    // EDAT
    fprintf(fp,"EDAT\n");
      
    // Set condition
    fprintf(fp,"*Set Cond %s",itrN()->GetName());
    if(itrN()->IsBothCondition()==YES) {
      fprintf(fp,"(n)");
    }
    fprintf(fp," *elems\n");

    // set 
    fprintf(fp,"*set var NE(int)=CondNumEntities(int)\n");   // GiD limit
    fprintf(fp,"%8d*NE*BNP\n",itrN()->GetNeumannGeomNo()+GID_LIMIT_BEDATNO);
    
    fprintf(fp,"*loop elems *OnlyInCond\n");
    fprintf(fp,"*globalnodes*elemsnum()\n");
    fprintf(fp,"*end\n");
  }

  // for NUM data
  if(feelfemobj.HowManyInitialDoubles() > 0) {
    fprintf(fp,"NUM \n");

    listIterator <Variable *>itrV(feelfemobj.GetInitialDblVarList());
    for(itrV.init(); !itrV ; ++itrV) {
      fprintf(fp,"*format \"%c15.5e\"\n",'%');    
      fprintf(fp,"*GenData(%s)\n",itrV()->GetName());
    }
  }


  // for REGN correspondance data
  int regions = feelfemgeomobj.GetNumberOfRegionObjects();

  if(regions >0) {
    fprintf(fp,"REGN\n");
    fprintf(fp,"%8d              # number of regions in script\n",regions);
    fprintf(fp,"*for(i=1;i<=%d;i=i+1)\n",regions);
    fprintf(fp,"*set var assigned=-1\n");
    fprintf(fp,"*loop materials\n");
    fprintf(fp,"*if(MatProp(Region_code,int)==i)\n");
    fprintf(fp,"*set var assigned=MatNum\n");
    fprintf(fp,"*break\n");
    fprintf(fp,"*endif\n");
    fprintf(fp,"*end materials\n");
    fprintf(fp,"*assigned        # matno for region code *i\n");
    fprintf(fp,"*end for\n");
  }

  fprintf(fp,"END \n");     // feel_dat (end mark)
  fclose(fp);

  return;
} 
