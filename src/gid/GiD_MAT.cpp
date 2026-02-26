/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : GiD_MAT.cpp
 *  Date     : 2002/03/25
 *  Modified : 
 *  
 *  Purpose  : generate .mat file
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
#include "GeometryObject.hpp"
#include "GeomObj.hpp"

#include "GiD.hpp"
#include "SurfaceObject.hpp"
#include "EdgeObject.hpp"
#include "PointObject.hpp"
#include "RegionObject.hpp"

#include "DirichletGeom.hpp"
#include "NeumannGeom.hpp"

void GiD::GenerateMAT(void)
{
  char fnamebuf[BUFSIZ];

  sprintf(fnamebuf,"%s.mat%c",(const char *)problemTypeName,'\0');
  
  FILE *fp;
  fp = fileOpenToWrite(fnamebuf);
  if(fp == NULL) {
    std::cerr << "Cannot open "<<fnamebuf << std::endl;
    return;
  }

  int regions = 0;

  listIterator <GeomObj *>itr(feelfemgeomobj.GetGeomObjLst());
  for(itr.init(); !itr ; ++itr ) {
    if(itr()->GetType() == GOBJ_REGION) {
      regions++;
    }
  }

  if(regions == 0) {

    // if no region, no material

    //    fprintf(fp,"NUMBER: %d MATERIAL: \n",1,
    //    fprintf(fp,"QUESTION: Region_code:#CB#(%d)\n",no);
    //    fprintf(fp,"VALUE: %d\n",no);
    //    fprintf(fp,"END MATERIAL\n");
  }
  else {

    int no = 0;

    for(itr.init(); !itr ; ++itr ) {
      
      if(itr()->GetType() != GOBJ_REGION) continue;

      no++;
      fprintf(fp,"NUMBER: %d MATERIAL: %s\n",no,itr()->GetName());
      
      fprintf(fp,"QUESTION: Region_code:#CB#(%d)\n",no);
      
      fprintf(fp,"VALUE: %d\n",no);
      
      fprintf(fp,"END MATERIAL\n");

      // itr()->GetPropertyNo() and no must be same
      assert(no == itr()->GetPropertyNo());

    }
  }

  fclose(fp);

  return;
}


  
    
  
