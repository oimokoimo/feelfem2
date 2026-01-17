/*
 *  feelfem version 1.1  
 *             Programmed by Hidehiro  FUJIO
 *
 *  Filename : Bamg_solv_dat.cpp
 *  Date     : 2026/01/07
 *  Modified : 
 *  
 *  Purpose  : solv_dat file generator.
 *             Basically, general, but currently, for Bamg with influence of GiD.
 *             Designed for feelfem90 program model
 *
 */

#include <stdio.h>
#include <iostream.h>
#include <assert.h>

#include "feeldef.hpp"
#include "feelfuncs.hpp"

#include "Object.hpp"
#include "GeometryObject.hpp"

#include "Bamg.hpp"
#include "SurfaceObject.hpp"
#include "EdgeObject.hpp"
#include "PointObject.hpp"
#include "RegionObject.hpp"

#include "DirichletGeom.hpp"
#include "NeumannGeom.hpp"

#include "Variable.hpp"          // for initial doubles


void GiD::GenerateSolvDat(void)
{
  FILE *fp;
  
  fp = fileOpenToWrite(FNAME_SOLV_DAT);
  if(fp == NULL) {
    cerr << "Cannot open " << FNAME_SOLV_DAT << " to open." << endl;
    return;
  }


  // GiD limitation

  // PROB    (the first word)
  fprintf(fp,"PROB\n");

  // MEDT    (Main edat data no. GiD limitation, it must be 1)
  fprintf(fp,"MEDT\n");
  fprintf(fp,"%8d  (Fixed to 1 in GiD interface)\n",1);

  // REDT    (Number of Region EDAT. GiD limitation, it must be 1)
  fprintf(fp,"REDT\n");
  // number of region edat sets
  fprintf(fp,"%8d  (Fixed to 1 in GiD interfce)\n",GID_LIMIT_REDAT); 
  // No. of EDAT no.  GiD limitation, it must be 1
  fprintf(fp,"%8d  (Fixed to 1 in GiD interfce)\n",GID_LIMIT_REDATNO); 


  // BEDT    (Number of Boundary EDAT.
  int bedt = feelfemgeomobj.HowManyNeumannGeoms();
  fprintf(fp,"BEDT\n");
  fprintf(fp,"%8d   (Number of boundary edat sets)\n", bedt );

  if(bedt > 0) {
    int index8 = 0;

    // Neumann EDAT set
    listIterator <NeumannGeom *>itrN(feelfemgeomobj.GetNeumannGeomLst());

    for(itrN.init(); !itrN ; ++itrN ){
      int no = itrN()->GetNeumannGeomNo() + 1; // No.1 is Region
      fprintf(fp,"%8d",no);
      index8++;
      if(index8 == 8) {
	index8 = 0;
	fprintf(fp,"\n");
      }
    }
    if(index8 != 0) fprintf(fp,"\n");
  }


  //SLVS        Number of solve sentences
  int solves = feelfemobj.HowManySolves();

  fprintf(fp,"SLVS\n");
  fprintf(fp,"%8d\n",solves);
  

  // SOLV  solve boundary data information
  for(int i=0;i<solves;i++) {
    
    Solve *solvePtr = feelfemobj.GetIthSolvePtr(i);
    int dconds = solvePtr->GetDconds();
    int nconds = solvePtr->GetNconds();


    fprintf(fp,"SOLV\n");
    fprintf(fp,"%8d   (solve No.)\n",i+1);
    fprintf(fp,"%8d   (solve EDAT No.)\n",GID_LIMIT_REDATNO);
    fprintf(fp,"%8d   (Number of dconds)\n",dconds);
    fprintf(fp,"%8d   (Number of nconds)\n",nconds);


    // dcond
    for(int j=0;j<dconds;j++) {

      Dirichlet *dPtr = solvePtr->GetIthDirichletDataPtr(j);
      
      int dGeoms      = dPtr->GetNumberOfDirichletGeoms();
      
      fprintf(fp,"DCND\n");
      fprintf(fp,"%8d%8d   (dcond No. and number of D-Geoms)\n", j+1,dGeoms);
      
      int index8 = 0;
      for(int k = 0; k < dGeoms; k++) {
	DirichletGeom *dgPtr = dPtr->GetIthDirichletGeomPtr(k);
	
	fprintf(fp,"%8d",dgPtr->GetDirichletGeomNo());
	index8++;

	if(index8 == 8) {
	  fprintf(fp,"\n");
	  index8 = 0;
	}
      }
      if(index8 != 0) fprintf(fp,"\n");

    }  // dcond loop


    // ncond
    for(int j=0;j<nconds;j++) {

      Neumann *nPtr = solvePtr->GetIthNeumannDataPtr(j);
      
      int nGeoms      = nPtr->GetNumberOfNeumannGeoms();
      
      fprintf(fp,"NCND\n");
      fprintf(fp,"%8d%8d   (ncond No. and number of N-Geoms)\n", j+1,nGeoms);
      
      int index8 = 0;
      for(int k = 0; k < nGeoms; k++) {
	NeumannGeom *ngPtr = nPtr->GetIthNeumannGeomPtr(k);
	
	fprintf(fp,"%8d",ngPtr->GetNeumannGeomNo() + GID_LIMIT_BEDATNO);
	index8++;

	if(index8 == 8) {
	  fprintf(fp,"\n");
	  index8 = 0;
	}
      }
      if(index8 != 0) fprintf(fp,"\n");

    }  // ncond loop

  } // solve loop


  fclose(fp);
  return;
}
