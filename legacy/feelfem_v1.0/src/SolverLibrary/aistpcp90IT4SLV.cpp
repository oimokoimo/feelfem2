/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : aistpcp90IT4SLV.cpp 
 *  Date     : 2002/06/28  (copy from feelfem90AMG81.cpp)
 *  Modified : 
 *  
 *  Purpose  : Single processor AMG routine
 *  
 */

#include "feelfem.hpp"

#include "Solve.hpp"
#include "MT_aist90PCP.hpp"
#include "LIB_aistpcp90IT4SLV.hpp"


//Default constructor 
LIB_aistpcp90IT4SLV <MT_aist90PCP>::LIB_aistpcp90IT4SLV()
{
  return;   // do nothing
}


//Default Destructor
LIB_aistpcp90IT4SLV <MT_aist90PCP>::~LIB_aistpcp90IT4SLV()
{
  return;  // do nothing;
}


void LIB_aistpcp90IT4SLV <MT_aist90PCP>::SolveCallSolverRoutine(Solve *solvePtr)
{
  DoSolveMakeUpdateInformationMT();       // update information making(for some solvers)

  COMMENTlong("Allocate solution vector");

  writeSource("allocate( resvec(neq))");
  writeSource("call zerod(resvec,neq)");
  com();

  COMMENTlong("PCP parameters");
  com();
  com();
  com();


  // deallocate(NPP)

  // call solver
  writeSource("  call PCP_IT4SLV(NDF_PCP,neq,NELT,                  &");
  writeSource("                nelem,np*nelem,iedom,ielem,          &");
  writeSource("                iepnt,AMAT,ICOL0,ICPNT,VFG,resvec,   &");
  writeSource("                ROPT,IOPT,NISIZ,IWORK,NRSIZ,RWORK, &");
  writeSource("                MPI_COMM_WORLD,ISTAT)");
  com();
  
  writeSource("if(ISTAT .NE. 0) then");
  writeSource("  write(*,*) 'Not converged.'");
  writeSource("  stop");
  writeSource("end if");
  com();


  writeSource("if(myrank == 0) then");
  pushSource("  call reportmodule('IT4SLV solve No.");
  pushSourceInt(solvePtr->GetSolveNo());
  pushSource(" Finished')");
  flushSource();

  writeSource("end if");
  comment();

  com();

  return;
}

void LIB_aistpcp90IT4SLV <MT_aist90PCP>::F90useSolveLIB(void)
{
  writeSource("! IT4SLV solver related modules");

  // pcp90 is common use
  com();
  
  return;
}


void LIB_aistpcp90IT4SLV <MT_aist90PCP>::SolverLibraryParameters(void)
{
  doNothingNow("void LIB_aistpcp90IT4SLV <MT_aist90PCP>::SolverLibraryParameters(void)");
  return;
}

void LIB_aistpcp90IT4SLV <MT_aist90PCP>::SolverLibraryVariableDefinition(void)
{
  COMMENTlong("Solver Library dependent variables");
  writeReal8Ptr1("resvec");
  writeReal8Ptr1("DWORK");
  writeInteger4sc("KDWORK");
  com();
  writeInteger4sc("ISTAT");
  com();

  writeInteger4sc("IOPT(10)");
  writeReal8sc("ROPT(10)");
  com();

  // IOPT is  GMRES p.70
  writeSource("! GMRES with recommended options");
  writeSource("!         ---1 ---2 ---3 ---4 ---5 ---6 ---7 ---8 ---9 --10 ");
  writeSource("data IOPT/   2,1000,  30,   4,   0,   2,   0,   0,   0,   0/");
  com();

  writeSource("!         ------1 --2 --3 --4 --5 --6 --7 --8 --9 -10 ");
  writeSource("data ROPT/1.0D-12, 0., 0., 0., 0., 0., 0., 0., 0., 0./");
  return;
}



void LIB_aistpcp90IT4SLV<MT_aist90PCP>::
DoSolveRoutineHeaderInLIB(char *routineName, Solve *solvePtr) {

  DoArgumentSequenceFromMain( routineName, solvePtr->VariablePtrLst() ); //PM
  DoSolveStarters();                                                 //PM

  F90useSolveLIB();
  F90useSolveMT();
  F90useSolvePM(solvePtr);
  
  fortImplicit();
  com();

  DoDeclareVariablesFromMainPM( solvePtr->VariablePtrLst());   //Fortran dependent
  

  return;
}



void LIB_aistpcp90IT4SLV<MT_aist90PCP>::
GenerateCoSolveSolverParamRoutine(Solve *solvePtr)
{
  SolveElement *sePtr = solvePtr->GetIthSolveElementPtr(0); // P2 FIXED
  char  hereRoutineName[BUFSIZ];
  char *hereSourceName;

  int solveElementNo = 1;   // P2 FIXED to 1

  int ivars;                // number of unknowns
  

  StoreSourceUniq(PCP90_SOURCE_NAME, LINKLEVEL_LIBRARY2);

  //  sprintf(hereRoutineName,"amg81param%d_%d",
  //	  solvePtr->GetSolveNo(),solveElementNo);  
  //  hereSourceName = GetSourceName(hereRoutineName);
  //
  //  OpenSource(hereSourceName,LINKLEVEL_LIBRARY_DEPENDENT);

  //  CloseSource();
  return;

}

//Library dependent solve-co routine generator
void LIB_aistpcp90IT4SLV <MT_aist90PCP>::
GenerateCoSolveRoutinesLIB(Solve *solvePtr)
{
  GenerateCoSolveSolverParamRoutine(solvePtr);    // iu, etc set
  return;
}
