/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : DEBUGdrawMesh.cpp
 *  Date     : 2001/04/10
 *  Modified : 
 *  
 *  Purpose  :
 *  
 */

#include "Bamg.hpp"
#include <iostream.h>
#include "../Xplot++/xplotfuncs.hpp"


void Bamg::DebugDrawMesh(void)
{
  cerr << "Bamg::DebugDrawMesh\n";

  openpl();
  openplps("oimo.ps");
  double dx = (xMaxBM-xMinBM)/20.0;
  double dy = (yMaxBM-yMinBM)/20.0;

  fspace(xMinBM-dx,yMinBM-dy,xMaxBM+dx,yMaxBM+dy);


  for(int i=0;i<bamgMeshTriangles;i++) {
    int p1,p2,p3;
    
    p1 = *(ielemTriBM + i*3 + 0);
    p2 = *(ielemTriBM + i*3 + 1);
    p3 = *(ielemTriBM + i*3 + 2);

    fmove( *(xBM+p1-1),*(yBM+p1-1));
    fcont( *(xBM+p2-1),*(yBM+p2-1));
    fcont( *(xBM+p3-1),*(yBM+p3-1));
    fcont( *(xBM+p1-1),*(yBM+p1-1));
  }
  xwait();
  closepl();
}
