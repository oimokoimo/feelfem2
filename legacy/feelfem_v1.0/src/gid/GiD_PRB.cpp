/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : GiD_PRB.cpp
 *  Date     : 2002/03/25
 *  Modified : 
 *  
 *  Purpose  : generate .prb file
 *  
 */

#include <stdio.h>
#include <iostream.h>

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

void GiD::GeneratePRB(void)
{
  char fnamebuf[BUFSIZ];

  sprintf(fnamebuf,"%s.prb%c",(char *)problemTypeName,'\0');
  
  FILE *fp;
  fp = fileOpenToWrite(fnamebuf);
  if(fp == NULL) {
    cerr << "Cannot open "<<fnamebuf << endl;
    return;
  }
  fprintf(fp,"PROBLEM DATA\n");

  // initial double variables
  listIterator <Variable *>itrV(feelfemobj.GetInitialDblVarList());
  for(itrV.init(); !itrV; ++itrV) {
    
    fprintf(fp,"QUESTION: %s\n",itrV()->GetName());
    fprintf(fp,"VALUE: %lf\n",itrV()->GetInitialValue());
  }

  fprintf(fp,"END GENERAL DATA\n");

  fclose(fp);

  return;
}


  
    
  
