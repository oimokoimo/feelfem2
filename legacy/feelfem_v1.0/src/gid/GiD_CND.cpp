/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : GiD_prefile.cpp
 *  Date     : 2002/03/14
 *  Modified : 
 *  
 *  Purpose  : generate .cnd .bas .mat .prb files
 *  
 */

#include <stdio.h>
#include <iostream.h>

#include "feeldef.hpp"
#include "feelfuncs.hpp"
#include "GeometryObject.hpp"

#include "GiD.hpp"
#include "SurfaceObject.hpp"
#include "EdgeObject.hpp"
#include "PointObject.hpp"
#include "RegionObject.hpp"

#include "DirichletGeom.hpp"
#include "NeumannGeom.hpp"

// for making comments in CND file
#include "Variable.hpp"
#include "Dirichlet.hpp"
#include "Neumann.hpp"
#include "pairClass.hpp"


void GiD::GenerateCND()
{
  char fnamebuf[BUFSIZ];

  sprintf(fnamebuf,"%s.cnd%c",(char *)problemTypeName,'\0');
  
  FILE *fp;
  fp = fileOpenToWrite(fnamebuf);
  if(fp == NULL) {
    cerr << "Cannot open "<<fnamebuf << endl;
    return;
  }

  // for Dirichlet
  listIterator <DirichletGeom *>itrD(feelfemgeomobj.GetDirichletGeomLst());

  for(itrD.init(); !itrD ; ++itrD ){
    
    // [STEP 1] NUMBER: 
    fprintf(fp,"NUMBER: %d CONDITION: %s",itrD()->GetBGeomNo(),
	    itrD()->GetName() );
    if(itrD()->IsBothCondition()==YES) {
      fprintf(fp,"(d)");
    }
    fprintf(fp,"\n");

    // [STEP 2] CONDTYPE:
    switch(itrD()->GetGeomType()) {
    case GOBJ_POINT:
      fprintf(fp,"CONDTYPE: over points\n");
      break;
      
    case GOBJ_EDGE:
      fprintf(fp,"CONDTYPE: over lines\n");
      break;

    case GOBJ_SURFACE:
      fprintf(fp,"CONDTYPE: over surfaces\n");
      break;

    default:
      cerr << "Illegal Dirichlet GeomObj type\n";
      assert(1==0);

    }

    // [STEP 3] :CONDMESHTYPE:
    fprintf(fp,"CONDMESHTYPE: over nodes\n");


    // [STEP 4] :Comment using QUESTION area
    listIterator <Dirichlet *>itrDdata(itrD()->GetDirichletDataPtrLst());
    for(itrDdata.init(); !itrDdata ; ++itrDdata ) {
      
      Variable *vPtr = itrDdata()->GetDcondVariablePtr();
      
      fprintf(fp,"QUESTION: solve_%d__dcond_%d:#CB#(%s=%s)\n",
	      itrDdata()->GetSolveNo(),
	      itrDdata()->GetDcondNo(),
	      vPtr->GetName(),
	      itrDdata()->GetSimpleExprStr() );

      fprintf(fp,"VALUE: %s=%s\n",
	      vPtr->GetName(),
	      itrDdata()->GetSimpleExprStr() );
    }

    // [STEP 5]
    fprintf(fp,"END CONDITION\n");
  }


  // for Neumann
  listIterator <NeumannGeom *>itrN(feelfemgeomobj.GetNeumannGeomLst());

  for(itrN.init(); !itrN ; ++itrN ){
    
    // [LINE 1] NUMBER: 
    fprintf(fp,"NUMBER: %d CONDITION: %s",itrN()->GetBGeomNo(),
	    itrN()->GetName() );
    if(itrN()->IsBothCondition()==YES) {
      fprintf(fp,"(n)");
    }
    fprintf(fp,"\n");

    // [LINE 2] CONDTYPE:
    switch(itrN()->GetGeomType()) {
    case GOBJ_EDGE:
      fprintf(fp,"CONDTYPE: over lines\n");
      break;

    case GOBJ_SURFACE:
      fprintf(fp,"CONDTYPE: over surfaces\n");
      break;

    default:
      cerr << "Illegal Neumann GeomObj type\n";
      assert(1==0);
    }

    // [LINE 3] :CONDMESHTYPE:
    fprintf(fp,"CONDMESHTYPE: over elems\n");
    


    // [STEP 4] :Comment using QUESTION area
    listIterator <Neumann *>itrNdata(itrN()->GetNeumannDataPtrLst());
    for(itrNdata.init(); !itrNdata ; ++itrNdata ) {

      int firstFlag;
      listIterator <StrStrPair*>itrNPair(itrNdata()->
					 GetNeumannPairDataPtrLst());

      fprintf(fp,"QUESTION: solve_%d__ncond_%d:#CB#(",
	      itrNdata()->GetSolveNo(),
	      itrNdata()->GetNcondNo() );

      firstFlag = 1;
      for(itrNPair.init();!itrNPair;++itrNPair) {
	if(firstFlag != 1) fprintf(fp,"_");     // here, underline necessary
	firstFlag = 0;
	fprintf(fp,"%s=%s", 
		(char *)(itrNPair()->GetFirst()),
		(char *)(itrNPair()->GetSecond()));
      }
      fprintf(fp,")\n");

      fprintf(fp,"VALUE: ");
      firstFlag = 1;
      for(itrNPair.init();!itrNPair;++itrNPair) {
	if(firstFlag != 1) fprintf(fp," ");     // here, underline unnecessary
	firstFlag = 0;
	fprintf(fp,"%s=%s", 
		(char *)(itrNPair()->GetFirst()),
		(char *)(itrNPair()->GetSecond()));
      }
      fprintf(fp,"\n");
    }

    // [STEP 5]
    fprintf(fp,"END CONDITION\n");
  }
  fclose(fp);

  return;
}

