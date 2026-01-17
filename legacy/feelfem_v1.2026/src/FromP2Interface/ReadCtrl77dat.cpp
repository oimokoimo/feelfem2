/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : ReadCtrl77dat.cpp
 *  Date     : 1999/11/26
 *  Modified : 1999/11/26
 *  
 *  Purpose  : Read P2 generated data
 *  
 *  
 *  The format of ctrl77.dat
 *  
 *       solve block
 *       dirichlet block  *** repeat
 *       neumann   block  *** repeat
 *       solveElement block
 *  
 *  
 *  
 *  
 */

#include <stdio.h>
#include "feelfuncs.hpp"   // stringLength, abortExit
#include "Variable.hpp"
#include "Solve.hpp"
#include "Object.hpp"
#include "Dirichlet.hpp"
#include "Neumann.hpp"
#include "SolveElement.hpp"
#include "Quadrature.hpp"

#define MAX_BCONDS  38
#define DBG          0

extern Object feelfemobj;
int strindex(const char *,const char *);
int testHereatoi(char *str)
{
  int ret;
  sscanf(str,"%d",&ret);
  return(ret);
}

void ReadCtrl77dat(Solve &solve)
{
  int solve_no;
 
  int femVars;
  int ewiseVars;
  int scalarVars;

  int elemg;
  
  int maxnodes;
  int nedtno;
  
  int dconds;
  int nconds;
  
  int nonlinearFlag;
  int unknowns;
  int elemKnownFemVars;
  int elemKnownEwiseVars;
  int elemScalarVars;

  int edevUnknowns;

  /* Only One SolveElement */
  SolveElement *sePtr = new SolveElement;
  Dirichlet dclass[MAX_BCONDS];
  Neumann   nclass[MAX_BCONDS];

  FILE *fp;
  char buf[BUFSIZ];
  
  fp = fopen("ctrl77.dat","r");
  if(fp == NULL) {
    fprintf(stderr,"cannot open ctrl77.dat to read\n");
    abortExit(1);
  }


  // SOLVE BLOCK

  fgets(buf,sizeof(buf),fp);
  sscanf(buf,"%d",&solve_no);
  if(DBG) fprintf(stderr,"READ buf=%s",buf);
  if(DBG) fprintf(stderr,"*** solve_no=%d\n",solve_no);

  solve.testSetSolveNo(solve_no);       // test
    
  fgets(buf,sizeof(buf),fp);
  sscanf(buf,"%d",&femVars);
  if(DBG) fprintf(stderr,"READ buf=%s",buf);
  if(DBG) fprintf(stderr,"***femVars =%d\n",femVars);

  for(int i=0;i<femVars;i++) {
    fgets(buf,sizeof(buf),fp);
    if(DBG) fprintf(stderr,"READ buf=%s",buf);
    buf[stringLength(buf)-1] = '\0';

    Variable var(buf,VAR_FEM);          //test
    feelfemobj.StoreVariable( var);
    //      solve.AddVariable(var);

  }

  /* ewise variables */
  fgets(buf,sizeof(buf),fp);
  sscanf(buf,"%d",&ewiseVars);    
  if(DBG) fprintf(stderr,"READ buf=%s",buf);
  if(DBG) fprintf(stderr,"*** ewiseVars = %d\n",ewiseVars);




  for(int i=0;i<ewiseVars;i++) {
    fgets(buf,sizeof(buf),fp);
    if(DBG) fprintf(stderr,"READ buf=%s",buf);
    buf[stringLength(buf)-1] = '\0';

    Variable var(buf,VAR_EWISE);       //test
    feelfemobj.StoreVariable( var);
    //      solve.AddVariable(var);

  }

  /* scalar variables */
  fgets(buf,sizeof(buf),fp);
  if(DBG) fprintf(stderr,"READ buf=%s",buf);

  sscanf(buf,"%d",&scalarVars);    
  if(DBG) fprintf(stderr,"*** scalarVars=%d\n",scalarVars);
    


  for(int i=0;i<scalarVars;i++) {
    fgets(buf,sizeof(buf),fp);
    if(DBG) fprintf(stderr,"READ buf=%s",buf);

    buf[stringLength(buf)-1] = '\0';

    Variable var(buf,VAR_DOUBLE);       //test
    feelfemobj.StoreVariable( var);
    //      solve.AddVariable(var);

  }


  /* elemg */
  fgets(buf,sizeof(buf),fp);
  if(DBG) fprintf(stderr,"READ buf=%s",buf);

  sscanf(buf,"%d",&elemg);
  if(DBG) fprintf(stderr,"*** elemg = %d\n",elemg);

  /* maxnode */
  fgets(buf,sizeof(buf),fp);
  sscanf(buf,"%d",&maxnodes);
  if(DBG) fprintf(stderr,"READ buf=%s",buf);
  if(DBG) fprintf(stderr,"*** maxnodes=%d\n",maxnodes);

  solve.testSetMaxnodes(maxnodes);  //test

  /* nedtno */
  fgets(buf,sizeof(buf),fp);
  if(DBG) fprintf(stderr,"READ buf=%s",buf);

  sscanf(buf,"%d",&nedtno);    // caution it is not array!
  if(DBG) fprintf(stderr,"*** nedtno =%d\n",nedtno);


    
  sePtr->testSetEdatno(nedtno);
    
  int *nenfre = new int[maxnodes];
  for(int i=0;i<maxnodes;i++) {
    fgets(buf,sizeof(buf),fp);
    if(DBG) fprintf(stderr,"READ buf=%s",buf);
    sscanf(buf,"%d",nenfre+i);          
    if(DBG) {
      fprintf(stderr,"nenfre[%d]=%d\n",i,*(nenfre+i));
    }
  }
  sePtr->testSetNodeFreedom( maxnodes, nenfre );  // test  (maxnodes is
  //        is not good...)

  /* dconds */
  fgets(buf,sizeof(buf),fp);
  if(DBG) fprintf(stderr,"READ buf=%s",buf);

  sscanf(buf,"%d",&dconds);
  if(DBG) {fprintf(stderr,"dconds =%d\n",dconds);
  }
    
  int *nsetno;
  if(dconds !=0) {
    nsetno = new int[dconds];
  }

  for(int i=0;i<dconds;i++) {
    fgets(buf,sizeof(buf),fp);
    if(DBG) fprintf(stderr,"READ buf=%s",buf);

    sscanf(buf,"%d",nsetno+i);
    dclass[i].testSetNsetno( *(nsetno+i));
  }


  /* nconds */
  fgets(buf,sizeof(buf),fp);
  sscanf(buf,"%d",&nconds);
  if(DBG) fprintf(stderr,"READ buf=%s",buf);
  if(DBG) {fprintf(stderr,"*** nconds =%d\n",nconds);    }


  int *nbedtno;
  if(nconds !=0){
    nbedtno = new int[nconds];
  }
  for(int i=0;i<nconds;i++) {
    fgets(buf,sizeof(buf),fp);
    if(DBG) fprintf(stderr,"READ buf=%s",buf);

    sscanf(buf,"%d",nbedtno+i);
    nclass[i].testSetNbedtno( *(nbedtno+i));
  }
    
  fgets(buf,sizeof(buf),fp);  // elem %d %d
  if(DBG) fprintf(stderr,"READ buf=%s",buf);

  if(strindex(buf,"elem")==0) {
    cerr << "Readbuf="<<buf<<"\n";
    cerr << "Illegal format in ReadCtrl77dat.cpp (at elem %d %d)\n";
    abortExit(1);
  }

  /* nonlinear flag */
  fgets(buf,sizeof(buf),fp);
  sscanf(buf,"%d",&nonlinearFlag);
  if(DBG) fprintf(stderr,"READ buf=%s",buf);
  if(DBG) fprintf(stderr,"*** nonlinearFlag=%d\n",nonlinearFlag);

  solve.testSetNonlinearFlag(nonlinearFlag);

  /* Solve statement */
  /* unknonws */
  fgets(buf,sizeof(buf),fp);
  sscanf(buf,"%d",&unknowns);    // currently does not try to read name!!

  if(DBG) fprintf(stderr,"READ buf=%s",buf);
  if(DBG) fprintf(stderr,"*** unknowns = %d\n",unknowns);
    
  solve.testSetUnknowns(unknowns);

  /* read unknowns */

  if(nonlinearFlag !=0) {
    for(int i=0;i<unknowns;i++) {
      fgets(buf,sizeof(buf),fp);
      if(DBG) fprintf(stderr,"READ buf=%s",buf);
	
      buf[stringLength(buf)-1] = '\0';    // skip reading
    }      
  }

  /* elemKnownFemVars  */
  fgets(buf,sizeof(buf),fp);
  sscanf(buf,"%d",&elemKnownFemVars);

  if(DBG) fprintf(stderr,"READ buf=%s",buf);
  if(DBG) fprintf(stderr,"*** elemKnownFemVars=%d\n",elemKnownFemVars);

  for(int i=0;i<elemKnownFemVars;i++) {
    fgets(buf,sizeof(buf),fp);
    if(DBG) fprintf(stderr,"READ buf=%s",buf);

    buf[stringLength(buf)-1] = '\0';

    Variable varfem(buf,VAR_FEM);
    feelfemobj.StoreVariable(varfem);

    Variable *vptr;
    vptr = feelfemobj.GetVariablePtrWithNameType(buf,VAR_FEM);
    sePtr->testAddVariablePtr(vptr);
  }      

  /* elemKnownEwiseVars */
  fgets(buf,sizeof(buf),fp);
  sscanf(buf,"%d",&elemKnownEwiseVars);

  if(DBG) fprintf(stderr,"READ buf=%s",buf);
  if(DBG) fprintf(stderr,"*** elemKnownEwiseVars=%d\n",elemKnownEwiseVars);

  for(int i=0;i<elemKnownEwiseVars;i++) {
    fgets(buf,sizeof(buf),fp);
    if(DBG) fprintf(stderr,"READ buf=%s",buf);

    buf[stringLength(buf)-1] = '\0';

    Variable varewise(buf,VAR_EWISE);
    feelfemobj.StoreVariable(varewise);


    Variable *vptr;
    vptr = feelfemobj.GetVariablePtrWithNameType(buf,VAR_EWISE);
    sePtr->testAddVariablePtr(vptr);

  }      

  /* elemScalarVars */
  fgets(buf,sizeof(buf),fp);
  if(DBG) fprintf(stderr,"READ buf=%s",buf);

  sscanf(buf,"%d",&elemScalarVars);
  for(int i=0;i<elemScalarVars;i++) {
    fgets(buf,sizeof(buf),fp);
    if(DBG) fprintf(stderr,"READ buf=%s",buf);

    buf[stringLength(buf)-1] = '\0';

    Variable varsc(buf,VAR_DOUBLE);
    feelfemobj.StoreVariable(varsc);

    Variable *vptr;
    vptr = feelfemobj.GetVariablePtrWithNameType(buf,VAR_DOUBLE);
    sePtr->testAddVariablePtr(vptr);

  }
    
  /* neumann conditions (read again)*/
  fgets(buf,sizeof(buf),fp);  
  sscanf(buf,"%d",&nconds);

  if(DBG) fprintf(stderr,"READ buf=%s",buf);
  if(DBG) fprintf(stderr,"*** nconds = %d\n",nconds);


  for(int i=0;i<nconds;i++) {
    int fvars,svars;
    fgets(buf,sizeof(buf),fp);
    sscanf(buf,"%d",&fvars);       // i-th neumann fem vars 
    if(DBG) fprintf(stderr,"READ buf=%s",buf);
    if(DBG) fprintf(stderr,"*** fvars[%d] = %d\n",i,fvars);

    for(int j=0;j<fvars;j++) {
      fgets(buf,sizeof(buf),fp);
      if(DBG) fprintf(stderr,"READ buf=%s",buf);

      buf[stringLength(buf)-1] = '\0';

      Variable varfem(buf,VAR_FEM);
      feelfemobj.StoreVariable(varfem);

      Variable *vptr;
      vptr = feelfemobj.GetVariablePtrWithNameType(buf,VAR_FEM);
      nclass[i].AddVariablePtr(vptr);
    }

    fgets(buf,sizeof(buf),fp);
    sscanf(buf,"%d",&svars);       // i-th neumann scalar vars 

    if(DBG) fprintf(stderr,"READ buf=%s",buf);
    if(DBG) fprintf(stderr,"*** svars[%d] = %d\n",i,svars);

    for(int j=0;j<svars;j++) {
      fgets(buf,sizeof(buf),fp);
      if(DBG) fprintf(stderr,"READ buf=%s",buf);

      buf[stringLength(buf)-1] = '\0';

      Variable varsc(buf,VAR_DOUBLE);
      feelfemobj.StoreVariable(varsc);

      Variable *vptr;
      vptr = feelfemobj.GetVariablePtrWithNameType(buf,VAR_DOUBLE);
      nclass[i].AddVariablePtr(vptr);
    }
  }

  /* dirichlet conditions (read again)*/
  fgets(buf,sizeof(buf),fp);  
  sscanf(buf,"%d",&dconds);

  if(DBG) fprintf(stderr,"READ buf=%s",buf);
  if(DBG) fprintf(stderr,"*** dconds = %d\n",dconds);

  for(int i=0;i<dconds;i++) {
    int fvars,svars;
    fgets(buf,sizeof(buf),fp);
    sscanf(buf,"%d",&fvars);       // i-th dirichlet fem vars 

    if(DBG) fprintf(stderr,"READ buf=%s",buf);
    if(DBG) fprintf(stderr,"*** fvars[%d]=%d\n",i,fvars);

    for(int j=0;j<fvars;j++) {
      fgets(buf,sizeof(buf),fp);
      if(DBG) fprintf(stderr,"READ buf=%s",buf);

      buf[stringLength(buf)-1] = '\0';

      Variable varfem(buf,VAR_FEM);
      feelfemobj.StoreVariable(varfem);

      Variable *vptr;
      vptr = feelfemobj.GetVariablePtrWithNameType(buf,VAR_FEM);
      dclass[i].AddVariablePtr(vptr);

    }

    /* scalar vars in Dirichlet */
    fgets(buf,sizeof(buf),fp);
    sscanf(buf,"%d",&svars);       // i-th dirichlet scalar vars

    if(DBG) fprintf(stderr,"READ buf=%s",buf);
    if(DBG) fprintf(stderr,"*** svars[%d]=%d\n",i,svars);

    for(int j=0;j<svars;j++) {
      fgets(buf,sizeof(buf),fp);
      if(DBG) fprintf(stderr,"READ buf=%s",buf);

      buf[stringLength(buf)-1] = '\0';


      Variable varsc(buf,VAR_DOUBLE);
      feelfemobj.StoreVariable(varsc);

      Variable *vptr;
      vptr = feelfemobj.GetVariablePtrWithNameType(buf,VAR_DOUBLE);
      dclass[i].AddVariablePtr(vptr);

    }
  }

  /* edev routine */
  fgets(buf,sizeof(buf),fp);
  sscanf(buf,"%d",&edevUnknowns);

  if(DBG) fprintf(stderr,"READ buf=%s",buf);
  if(DBG) fprintf(stderr,"*** edevUnknowns=%d\n",edevUnknowns);

  for(int i=0;i<edevUnknowns;i++) {
    int freedom;
    char numbuf[80];

    fgets(buf,sizeof(buf),fp);
    if(DBG) fprintf(stderr,"READ buf=%s",buf);
    buf[stringLength(buf)-1] = '\0';

    fgets(numbuf,sizeof(numbuf),fp);
    if(DBG) fprintf(stderr,"READ buf(NUMBUF)=%s",numbuf);
    freedom = testHereatoi( numbuf );

    Variable varfem(buf,VAR_FEM);

    if(DBG) fprintf(stderr,"NUMBUF VAL=%d\n",freedom);
    feelfemobj.StoreVariable(varfem);

    Variable *vptr;
    vptr = feelfemobj.GetVariablePtrWithNameType(buf,VAR_FEM);
    vptr->testPutElementFreedom( freedom );

    sePtr->testAddUnknownVariablePtr(vptr);

  }          
    
  if(DBG) fprintf(stderr,"*** END OF READING ***\n");

  solve.AddSolveElementPtr(sePtr);
  for(int i=0;i<dconds;i++) {
    Dirichlet *dptr = new Dirichlet(dclass[i]);
    solve.AddDirichletDataPtr( dptr );
  }
  for(int i=0;i<nconds;i++) {
    Neumann   *nptr = new Neumann(nclass[i]);
    solve.AddNeumannDataPtr( nptr );
  }
  cerr << "FINISH READING\n";

  fgets(buf,sizeof(buf),fp);
  if(!strindex(buf,"owari")) {
    cerr << "FORMAT ERROR, FAILED TO READ owari FOR SOLVEDAT\n";
    abortExit(1);
  }

  // DIRICHLET BLOCK
  /**************************  reading dcond data */
  for(int i=0;i<dconds;i++) {
    fgets(buf,sizeof(buf),fp);
    if(!strindex(buf,"***dcond")) {
      cerr << "FORMAT ERROR, FAILED TO READ ***dcond FOR dcond No."
	   << i+1 <<"\n";
      abortExit(1);
    }
    
    int solveno,dcondno;
    sscanf(buf,"%d %d",&solveno,&dcondno);
    if(solveno != 1 || dcondno != i+1) {
      cerr << "SOLVENO/DCONDNO mismatch in reading  ***dcond FOR dcond No."
	   << i+1 <<"\n";
    }
    fgets(buf,sizeof(buf),fp);
    if(DBG) fprintf(stderr,"READ buf=%s",buf);
    buf[stringLength(buf)-1] = '\0';
    
    Dirichlet *dptr;
    dptr = solve.GetIthDirichletDataPtr(dcondno-1);
    dptr->testSetTestExpression(buf);

    dptr->testSetSolveNo(solveno);
    dptr->testSetDcondNo(dcondno);                    // CAUTION dcondno in
    // Dirichlet conditions set here!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

    fgets(buf,sizeof(buf),fp);
    if(!strindex(buf,"end of dcond")) {
      cerr << "FORMAT ERROR, FAILED TO READ ***dcond FOR dcond No."
	   << i+1 <<"\n";
      abortExit(1);
    }

  }

  // NEUMANN BLOCK
  for(int i=0;i<nconds;i++) {
    fgets(buf,sizeof(buf),fp);
    if(!strindex(buf,"***ncond(ncondgen)")) {
      cerr << "FORMAT ERROR, FAILED TO READ ***ncond FOR ncond No."
	   << i+1 <<"\n";
      abortExit(1);
    }

    int solveno,ncondno;
    sscanf(buf,"%d %d",&solveno,&ncondno);
    if(solveno != 1 || ncondno != i+1) {
      cerr << "Solveno/Ncondno mismatch in reading ***ncond for " 
	   << "ncond no " << i + 1 << "\n";
      abortExit(1);
    }

    /* GET NEUMANN PTR */
    Neumann *nPtr = solve.GetIthNeumannDataPtr(i);

    nPtr->testSetSolveNo(solveno);
    nPtr->testSetNcondNo(ncondno);                    // CAUTION ncondno in

    /*--------------------------------------------------------*/
    /* read NPG */
    fgets(buf,sizeof(buf),fp);
    if(DBG) fprintf(stderr,"READ buf=%s",buf);
    
    int NPG;
    sscanf(buf,"%d",&NPG);
    if(DBG) fprintf(stderr,"NPG =%d\n",NPG);

    nPtr->testSetNPG(NPG);


    /*--------------------------------------------------------*/
    /* read NDF */
    fgets(buf,sizeof(buf),fp);
    if(DBG) fprintf(stderr,"READ buf=%s",buf);
    
    int NDF;
    sscanf(buf,"%d",&NDF);
    if(DBG) fprintf(stderr,"NDF =%d\n",NDF);

    nPtr->testSetNDF(NDF);

    /*--------------------------------------------------------*/
    /* Quadrature array */
    fgets(buf,sizeof(buf),fp);
    if(!strindex(buf,"***START OF QUADRATURE array")) {
      cerr << "Cannot find '***START OF QUADRATURE array' sentence\n";
      abortExit(1);
    }

    while(fgets(buf,sizeof(buf),fp)) {
      if(strindex(buf,"***END OF QUADRATURE array")) break;

      buf[stringLength(buf)-1] = '\0';
      nPtr->AddQuadratureArrayLst( buf );  // memory aquired in Add routine
    }

    /*--------------------------------------------------------*/
    /* IENP */
    fgets(buf,sizeof(buf),fp);
    if(!strindex(buf,"***START OF IENP")) {
      cerr << "Cannot find '***START OF IENP' sentence\n";
      abortExit(1);
    }

    while(fgets(buf,sizeof(buf),fp)) {
      if(strindex(buf,"***END OF IENP")) break;

      buf[stringLength(buf)-1] = '\0';
      nPtr->AddIENPLst( testHereatoi(buf) );  // memory aquired in Add routine
    }
    /* END of IENP */

    /*--------------------------------------------------------*/
    /* IEDP */
    fgets(buf,sizeof(buf),fp);
    if(!strindex(buf,"***START OF IEDP")) {
      cerr << "Cannot find '***START OF IEDP' sentence\n";
      abortExit(1);
    }

    while(fgets(buf,sizeof(buf),fp)) {

      if(strindex(buf,"***END OF IEDP")) break;

      buf[stringLength(buf)-1] = '\0';
      nPtr->AddIEDPLst( testHereatoi(buf) );  // memory aquired in Add routine
    }
    /* END of IEDP */

    /*--------------------------------------------------------*/
    /* number of gauss points */
    fgets(buf,sizeof(buf),fp);
    if(!strindex(buf,"(gauss_points)")) {
      cerr << "Cannot find '(gauss_points)'\n";
      abortExit(1);
    }
    int gauss_points;
    sscanf(buf,"%d",&gauss_points);
    nPtr->testSetGaussPoints(gauss_points);

    /*--------------------------------------------------------*/
    /* gauss quadrature parameter Read */
    for(int i=0;i<gauss_points;i++) {
      char gxbuf[BUFSIZ];
      char wbuf[BUFSIZ];

      fgets(buf,sizeof(buf),fp);
      sscanf(buf,"%s",gxbuf);

      fgets(buf,sizeof(buf),fp);
      sscanf(buf,"%s",wbuf);

      nPtr->AddGXArrayLst( gxbuf );
      nPtr->AddWArrayLst (  wbuf );
    }
    /* end of gauss quadrature parameter */

    /*--------------------------------------------------------*/
    /* S VALUE TRIANGLE OR RECTANGLE */  /* chg 2001/01/23 OOIMO */
    fgets(buf,sizeof(buf),fp);
    if(!strindex(buf,"(S VALUE TRIANGLE)") &&
       !strindex(buf,"(S VALUE RECTANBLE)")   ){
      cerr << "Cannot find '(S VALUE TRIANGLE) or RECTANBLE'\n";
      abortExit(1);
    }      
    char Sbuf[BUFSIZ];
    sscanf(buf,"%s",Sbuf);
    nPtr->testSetSValue(Sbuf);
    
    /*--------------------------------------------------------*/
    /* TERMS */
    fgets(buf,sizeof(buf),fp);
    if(!strindex(buf,"**** START OF TERMS")) {
      cerr << "Cannot find '**** START OF TERMS' sentence\n";
      abortExit(1);
    }

    while(fgets(buf,sizeof(buf),fp)) {
      if(strindex(buf,"**** END OF TERMS")) break;

      char leftBuf[BUFSIZ];
      char rightBuf[BUFSIZ];
      
      sscanf(buf,"%s",leftBuf);
      sscanf(buf+stringLength(leftBuf),"%s",rightBuf);
      
      if(DBG) {
	fprintf(stderr,"TERM LVALUE=%s\n",leftBuf);
	fprintf(stderr,"TERM RVALUE=%s\n",rightBuf);
      }
      nPtr->AddTermsLeftLst(leftBuf);
      nPtr->AddTermsRightLst(rightBuf);
    }
    /* END of TERMS */

    /*--------------------------------------------------------*/
    /* Read boundary_points for LOOP 200 */
    fgets(buf,sizeof(buf),fp);
    if(!strindex(buf,"boundary_points for LOOP")) {
      cerr << "Cannot find 'boundary_points for LOOP'\n";
      abortExit(1);
    }
    int boundary_points;
    sscanf(buf,"%d",&boundary_points);
    nPtr->testSetBoundaryPoints(boundary_points);
    

    /*--------------------------------------------------------*/
    /* Read (n_ptr->fem vars) */
    int nptr_fem_vars_flag;
    
    fgets(buf,sizeof(buf),fp);
    if(!strindex(buf,"(n_ptr->fem_vars)")) {
      cerr << "Cannot find '(n_ptr->fem_vars)'\n";
      abortExit(1);
    }
    sscanf(buf,"%d",&nptr_fem_vars_flag);

       
    /* if nptr_fem_vars_flag is not null, read fem vars for formula */
    if(nptr_fem_vars_flag != 0) {
      fgets(buf,sizeof(buf),fp);
      if(!strindex(buf,"***START OF FEM VARS FORMULA")) {
	cerr << "Cannot find '***START OF FEM VARS FORMULA'\n";
	abortExit(1);
      }      
      while(fgets(buf,sizeof(buf),fp)) {
	if(strindex(buf,"***END OF FEM VARS FORMULA")) break;

	char fleftbuf[BUFSIZ],equalbuf[10],frightbuf[BUFSIZ];
	sscanf(buf,"%s %s %s",fleftbuf,equalbuf,frightbuf);
	if(equalbuf[0] != '=') {
	  cerr << "Reading FEM VARS FORMULA ERR\n";
	  cerr << "Middle is not '='.\n";

	  cerr << "READBUF=" << buf;
	  abortExit(1);
	}

	nPtr->AddFemVarsFormulaLeftLst ( fleftbuf  );
	nPtr->AddFemVarsFormulaRightLst( frightbuf );

      }
    }
    /* END OF READING FEM VARS FORMULA */

    /*--------------------------------------------------------*/
    /* Read dx formula */
    fgets(buf,sizeof(buf),fp);
    if(!strindex(buf,"*** dx formula")) {
      cerr << "Cannot find '*** dx formula'\n";
      abortExit(1);
    }
    fgets(buf,sizeof(buf),fp);
    buf[stringLength(buf)-1] = '\0';
    nPtr->testSetDxFormula(buf);
    /* end of reading dx formula / ncond */
    

    /*--------------------------------------------------------*/
    /* Read dy formula */
    fgets(buf,sizeof(buf),fp);
    if(!strindex(buf,"*** dy formula")) {
      cerr << "Cannot find '*** dy formula'\n";
      abortExit(1);
    }
    fgets(buf,sizeof(buf),fp);
    buf[stringLength(buf)-1] = '\0';
    nPtr->testSetDyFormula(buf);
    /* end of reading dy formula / ncond */

    /*--------------------------------------------------------*/
    /* Read qx formula, if exists */
    fgets(buf,sizeof(buf),fp);
    if(!strindex(buf,"(xflag for qx assignment")) {
      cerr << "Cannot find '*** xflag for qx assignment\n";
      abortExit(1);
    }
    int qx_flag;
    sscanf(buf,"%d",&qx_flag);
    nPtr->testSetQxFlag(qx_flag);
    
    if(qx_flag != 0) {
      fgets(buf,sizeof(buf),fp);
      if(!strindex(buf,"*** qx formula")) {
	cerr << "Cannot find '*** qx formula\n";
	abortExit(1);
      }
      
      /* read qx formula */
      fgets(buf,sizeof(buf),fp);
      buf[stringLength(buf)-1] = '\0';
      nPtr->testSetQxFormula(buf);
    }
    /* end of reading qx formula/ncond */


    /*--------------------------------------------------------*/
    /* Read qy formula, if exists */
    fgets(buf,sizeof(buf),fp);
    if(!strindex(buf,"(yflag for qy assignment")) {
      cerr << "Cannot find '*** yflag for qy assignment\n";
      abortExit(1);
    }
    int qy_flag;
    sscanf(buf,"%d",&qy_flag);
    nPtr->testSetQyFlag(qy_flag);
    
    if(qy_flag != 0) {
      fgets(buf,sizeof(buf),fp);
      if(!strindex(buf,"*** qy formula")) {
	cerr << "Cannot find '*** qy formula\n";
	abortExit(1);
      }
      
      /* read qy formula */
      fgets(buf,sizeof(buf),fp);
      buf[stringLength(buf)-1] = '\0';
      nPtr->testSetQyFormula(buf);
    }
    /* end of reading qy formula/ncond */

    /*--------------------------------------------------------*/
    /* read ba_flag */
    fgets(buf,sizeof(buf),fp);
    if(!strindex(buf,"(expr_ba_flag, again)")) {
      cerr << "Cannot find 'expr_ba_flag, again\n";
      abortExit(1);
    }
    int ba_yet_flag;
    sscanf(buf,"%d",&ba_yet_flag);
    nPtr->testSetBaFlag( ba_yet_flag);

    if(DBG) { fprintf(stderr," expr_ba_flag = %d\n",ba_yet_flag); }

    /* read ba formula */
    if(ba_yet_flag) {
      while(fgets(buf,sizeof(buf),fp)) {
	if(strindex(buf,"***** END OF BA FORMULA")) 
	  break;

	/* read i,j */
	int indi,indj;

	sscanf(buf,"%d %d",&indi,&indj);

	/* read formula */
	fgets(buf,sizeof(buf),fp);
	
	buf[stringLength(buf)-1] = '\0';
      
	nPtr->AddBaFormulaLst(indi,indj,buf);

	if(DBG) fprintf(stderr,"DBG**  BA(%d,%d) %s\n",indi,indj,buf);
      }
    }
    /* end of reading ba formulas/ncond */
      

    /*--------------------------------------------------------*/
    /* read (freedom again for bb) */
    fgets(buf,sizeof(buf),fp);
    if(DBG) fprintf(stderr,"READ BUF=%s",buf);

    if(!strindex(buf,"(freedom again for bb)")) {
      cerr << "Cannot find '(freedom again for bb)\n";
      abortExit(1);
    }
    int bb_freedom;
    sscanf(buf,"%d",&bb_freedom);
    nPtr->testSetBbFreedom(bb_freedom);
    /* end of reading bb freedom */
    
    
    /*--------------------------------------------------------*/
    /* read bb formula */
    for(int i=0;i<bb_freedom;i++) {
      fgets(buf,sizeof(buf),fp);
      if(!strindex(buf,"(bb(")) {
	cerr<< "Reading error while reading bb formula index\n";
	abortExit(1);
      }
      fgets(buf,sizeof(buf),fp);
      buf[stringLength(buf)-1] = '\0';

      nPtr->AddBbFormulaLst(buf);
    }
    /* end of reading bb formula */

    /*--------------------------------------------------------*/
    /* read end mark of  */
    fgets(buf,sizeof(buf),fp);
    if(!strindex(buf,"owari for Neumanndata")) {
      cerr << "FORMAT ERROR, FAILED TO READ owari for Neumanndata"
	   << i+1 <<"\n";
      abortExit(1);
    }
    /* end of reading mark of ONE neumann data */
  }
  // END OF READING NEUMANN BLOCK
  

  // SOLVE ELEMENT BLOCK
  /**************************  reading elem data */
  fgets(buf,sizeof(buf),fp);
  if(!strindex(buf,"*** elem data ***")) {
    cerr << "FORMAT ERROR, FAILED TO READ *** elem data *** FOR ELEMDAT\n";
    abortExit(1);
  }

  /* dirichlet conditions (read again)*/

  int solveNo,elemNo,tmp;

  fgets(buf,sizeof(buf),fp);  
  sscanf(buf,"%d %d",&solveNo,&elemNo);
  if(DBG) fprintf(stderr,"READ buf=%s",buf);
  if(DBG) fprintf(stderr,"@@@ solveNo=%d  elemNo=%d\n",solveNo,elemNo);
  sePtr->testSetSolveNo(solveNo);
  sePtr->testSetElemNo(elemNo);

  fgets(buf,sizeof(buf),fp);  
  sscanf(buf,"%d",&tmp);
  if(DBG) fprintf(stderr,"READ buf=%s",buf);
  if(DBG) fprintf(stderr,"@@@ nonlinear flag = %d\n",tmp);
  sePtr->testSetNonlinearFlag(tmp);

  /* skip unknown fem vars */
  fgets(buf,sizeof(buf),fp);  
  sscanf(buf,"%d",&unknowns);
  if(DBG) fprintf(stderr,"READ buf=%s",buf);
  if(DBG) fprintf(stderr,"@@@ unknowns = %d\n",unknowns);
  sePtr->testSetUnknowns(unknowns);
  
  for(int i=0;i<unknowns;i++) {
    fgets(buf,sizeof(buf),fp);  
    if(DBG) fprintf(stderr,"READ buf(SKIP)=%s",buf);
  }

  /* skip known fem vars */
  fgets(buf,sizeof(buf),fp);  
  sscanf(buf,"%d",&tmp);
  if(DBG) fprintf(stderr,"READ buf=%s",buf);
  if(DBG) fprintf(stderr,"@@@ knowns = %d\n",tmp);
  
  for(int i=0;i<tmp;i++) {
    fgets(buf,sizeof(buf),fp);  
    if(DBG) fprintf(stderr,"READ buf(SKIP)=%s",buf);
  }

  /* skip known ewise vars */
  fgets(buf,sizeof(buf),fp);  
  sscanf(buf,"%d",&tmp);
  if(DBG) fprintf(stderr,"READ buf=%s",buf);
  if(DBG) fprintf(stderr,"@@@ ewise knowns = %d\n",tmp);
  
  for(int i=0;i<tmp;i++) {
    fgets(buf,sizeof(buf),fp);  
    if(DBG) fprintf(stderr,"READ buf(SKIP)=%s",buf);
  }

  /* skip known scalar vars */
  fgets(buf,sizeof(buf),fp);  
  sscanf(buf,"%d",&tmp);
  if(DBG) fprintf(stderr,"READ buf=%s",buf);
  if(DBG) fprintf(stderr,"@@@ scalar knowns = %d\n",tmp);
  
  for(int i=0;i<tmp;i++) {
    fgets(buf,sizeof(buf),fp);  
    if(DBG) fprintf(stderr,"READ buf(SKIP)=%s",buf);
  }

  int NDF; 
  fgets(buf,sizeof(buf),fp);  
  sscanf(buf,"%d",&NDF);
  if(DBG) fprintf(stderr,"READ buf=%s",buf);
  if(DBG) fprintf(stderr,"@@@ NDF = %d\n",NDF);

  int quadratureMethods;
  fgets(buf,sizeof(buf),fp);  
  sscanf(buf,"%d",&quadratureMethods);
  if(DBG) fprintf(stderr,"READ buf=%s",buf);
  if(DBG) fprintf(stderr,"@@@ quadratureMethods = %d\n",quadratureMethods);

  for(int i=0;i<quadratureMethods;i++) {
    Quadrature *quadPtr = new Quadrature;
    int points;
    char name[50];
    fgets(buf,sizeof(buf),fp);  
    sscanf(buf,"%d  %s",&points,name);
    if(DBG) fprintf(stderr,"READ buf=%s",buf);
    if(DBG) fprintf(stderr,"@@@ quadraturePoints = %d\n",points);
    if(DBG) fprintf(stderr,"@@@ quadrature Name  = %s\n",name);
    quadPtr->testSetQuadraturePoints(points);
    quadPtr->testSetName(name);
    sePtr->testAddQuadraturePtr(quadPtr);
  }
  

  /* read NDF again for ienp */
  fgets(buf,sizeof(buf),fp);  
  sscanf(buf,"%d",&NDF);
  if(DBG) fprintf(stderr,"READ buf=%s",buf);
  if(DBG) fprintf(stderr,"@@@ NDF = %d\n",NDF);

  int *ienp = new int[NDF];
  for(int i=0;i<NDF;i++) {
    int tmp;
    fgets(buf,sizeof(buf),fp);  
    sscanf(buf,"%d",&tmp);
    if(DBG) fprintf(stderr,"READ buf=%s",buf);
    if(DBG) fprintf(stderr,"@@@ ienp[%d] = %d\n",i,tmp);
    *(ienp+i) = tmp;
  }


  /* read NDF again for iedp */
  fgets(buf,sizeof(buf),fp);  
  sscanf(buf,"%d",&NDF);
  if(DBG) fprintf(stderr,"READ buf=%s",buf);
  if(DBG) fprintf(stderr,"@@@ NDF = %d\n",NDF);

  int *iedp = new int[NDF];
  for(int i=0;i<NDF;i++) {
    int tmp;
    fgets(buf,sizeof(buf),fp);  
    sscanf(buf,"%d",&tmp);
    if(DBG) fprintf(stderr,"READ buf=%s",buf);
    if(DBG) fprintf(stderr,"@@@ iedp[%d] = %d\n",i,tmp);
    *(iedp+i) = tmp;
  }
  sePtr->testSetNDFIENPIEDP(NDF,ienp,iedp);
  

  fgets(buf,sizeof(buf),fp);  
  sscanf(buf,"%d",&tmp);
  if(DBG) fprintf(stderr,"READ buf=%s",buf);
  if(DBG) fprintf(stderr,"@@@ nodes = %d\n",tmp);
  sePtr->testSetIelemNodes(tmp);
  
  while(1) {
    if(DBG) fprintf(stderr,"@@@@@@@@@@@ while loop\n");
    int args;
    fgets(buf,sizeof(buf),fp);  
    sscanf(buf,"%d",&args);    
    if(DBG) fprintf(stderr,"READ buf=%s",buf);
    if(DBG) fprintf(stderr,"@@@ ARGS[FEM] = %d\n",args);

    if(args == 0) break;

    for(int i=0;i<args;i++) {
      fgets(buf,sizeof(buf),fp);  
      if(DBG) fprintf(stderr,"FEM[%d]READ buf=%s",i,buf);
      buf[stringLength(buf)-1] = '\0';
      sePtr->testAddEcalArgs( buf );
    }
  }

  int args;
  fgets(buf,sizeof(buf),fp);  
  sscanf(buf,"%d",&args);    
  if(DBG) fprintf(stderr,"READ buf=%s",buf);
  if(DBG) fprintf(stderr,"@@@ Ewise knows  = %d\n",args);

  for(int i=0;i<args;i++) {
    fgets(buf,sizeof(buf),fp);  
    if(DBG) fprintf(stderr,"[%d]READ buf=%s",i,buf);
    buf[stringLength(buf)-1] = '\0';     
    sePtr->testAddEcalArgs( buf );
  }


  fgets(buf,sizeof(buf),fp);  
  sscanf(buf,"%d",&args);    
  if(DBG) fprintf(stderr,"READ buf=%s",buf);
  if(DBG) fprintf(stderr,"@@@ scalar knows  = %d\n",args);

  for(int i=0;i<args;i++) {
    fgets(buf,sizeof(buf),fp);  
    if(DBG) fprintf(stderr,"[%d]READ buf=%s",i,buf);
    buf[stringLength(buf)-1] = '\0';
    sePtr->testAddEcalArgs( buf );
  }


  /* read owari */

  fgets(buf,sizeof(buf),fp);  
  if(DBG) fprintf(stderr,"READ buf=%s",buf);
  if(!strindex(buf,"owari")) {
    fprintf(stderr,"Cannot find final owari\n");
    abortExit(1);
  }
  

  return;
} 





