/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999,2000
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : MT_ff90smpiMUMPSCA.cpp
 *  Date     : 2003/01/01 (Copied from MT_ff90AMGCRS.cpp)
 *  Modified : 
 *  
 *  Purpose  :
 *  
 *  1. Constructors/destructors
 *  
 */

#include "ElemGeneratorTemplate.hpp"
#include "MT_ff90smpiMUMPSCA.hpp"


// 1. Constructors, destructors

MT_ff90smpiMUMPSCA::MT_ff90smpiMUMPSCA() 
{
  return;   // do nothing now
}

MT_ff90smpiMUMPSCA::~MT_ff90smpiMUMPSCA() 
{
  return;   // do nothing now
}




// 2. CoSolve Routine definitions
//    ElemGenerator Main  

void MT_ff90smpiMUMPSCA::GenerateCoSolveElemGenerator (Solve *solvePtr)
{
  ElemGeneratorTemplate<MT_ff90smpiMUMPSCA> *ptrEG =
    new ElemGeneratorTemplate<MT_ff90smpiMUMPSCA>();
  ptrEG->NormalAssembly(solvePtr,solvePtr->GetIthSolveElementPtr(0)); //P2 limi

  return;
}


void MT_ff90smpiMUMPSCA::F90useSolveMT( void )
{
  writeSource("! Matrix data structure related modules");
  writeSource("use MUMPSCA");
  com();
  
  return;
}

////////////////////////////////////////////////////
//  General routine
////////////////////////////////////////////////////
void MT_ff90smpiMUMPSCA::pushMatrixArgumentsCalled()
{
  pushSource("mumps_par,iptrcol,neq");
  return;
}

void MT_ff90smpiMUMPSCA::writeMatrixDeclarations()
{
  // MUMPS solver needs include mpif.h and dmumps_struct.h
  writeSource("include 'mpif.h'");
  writeSource("include 'dmumps_struc.h'");
  com();
  writeSource("type (DMUMPS_STRUC)                     :: mumps_par");
  writeInteger4Ptr1("iptrcol");
  writeInteger4sc("ierr");
  com();

  return;
}

//  solve routine matrix dependent parts
void MT_ff90smpiMUMPSCA::DoSolveVariableDefinitionsMT()
{
  COMMENTlong("Matrix related variables");


  writeMatrixDeclarations();    // MUMPSCA

  //integer                                  :: ncof
  //  writeInteger4sc("ncof");
  com();

  return;
}

void MT_ff90smpiMUMPSCA::pushMatrixArgumentsAllocated(void)
{
  pushMatrixArgumentsCalled();             // same in Fortran 90
  return;
}

void MT_ff90smpiMUMPSCA::DoSolveInitializerMT( Solve *solvePtr) 
{
  // MPI initialize for MUMPSCA
  COMMENTlong("MPI initialize for MUMPS solver");
  writeSource("mumps_par%COMM = MPI_COMM_WORLD");
  com();
  
  writeSource("! SYM 0:unsymmetric 1:symmetric positive definite 2:general symmetric");
  writeSource("mumps_par%SYM  = 0  ! maybe 2 is the best, but does not work");
  com();
 
  writeSource("! PAR:0 host is not involved factorization  1:involved");
  writeSource("mumps_par%PAR  = 1");
  com();

  writeSource("! JOB  -1  initialization");
  writeSource("mumps_par%JOB  = -1");
  com();
  
  writeSource("call DMUMPS(mumps_par)");
  com();

  COMMENTlong("MUMPS Centralized matrix");
  writeSource("if( mumps_par%MYID .eq. 0) then");  // endif is in LIB MUMPSCA
  com();

  return;
}

// ### Matrix allocation in solve routine

void MT_ff90smpiMUMPSCA::DoSolveMatrixAllocate( Solve *)
{

  // allocate memory at subroutine for N,NZ,IRN,JCN



  COMMENTlong("Calculate maxmal number of element connection to one node");
  writeSource("call nc_connectp2(npmax,ielem,nelem,np, ncmax)");
  com();

  writeSource("call reportmodule('nc_connectp2')");
  com();

  COMMENTlong("Make AMG-CRS array");
  writeSource("nenfremax = 0");
  writeSource("do i=1,neg");       
  writeSource(" do j=1,maxElementNodes");
  writeSource("  if(nenfremax < nenfre(j,i)) nenfremax=nenfre(j,i)");
  writeSource(" end do");
  writeSource("end do");
  com();

  writeSource("ndfmax = nenfremax * maxElementNodes");
  writeSource("ncon   = nenfremax * maxElementNodes * ncmax");
  com();
  
  writeSource("call mkMUMPSCAindex( neq,                    &");
  writeSource("                     ndfmax,ncon,            &");
  writeSource("                     ipf,ipd,npmax,          &");
  writeSource("                     ielem,nelem,np,         &");
  writeSource("                     mumps_par     ,         &");
  writeSource("                     iptrcol                  )");
  com();
  
  writeSource("call reportmodule('mkMUMPSCAindex')");
  com();

  // allocate matrix array
  COMMENTlong("Allocate matrix, right hand side");
  writeSource(" allocate(mumps_par%A  ( mumps_par%NZ))");
  writeSource(" allocate(mumps_par%RHS( mumps_par%N ))");
  com();
  writeSource(" call zerod(mumps_par%A  , mumps_par%NZ)");
  writeSource(" call zerod(mumps_par%RHS, mumps_par%N )");
  

  return;
}


////////////////////////////////////////////////////
//  call assemble routine
////////////////////////////////////////////////////
void MT_ff90smpiMUMPSCA::DoSolveCallAssembleRoutine( Solve *solvePtr)
{
  int fem_exchange_variables;
  SolveElement *sePtr = solvePtr->GetIthSolveElementPtr(0); // P2 FIXED
  orderedPtrList <Variable *> varPtrLst = sePtr->GetVariablePtrLst();
  
  fem_exchange_variables = 0;
  listIterator <Variable *> itr(varPtrLst);
  for(itr.init(); !itr;++itr) {
    if(itr()->GetType() == VAR_FEM) fem_exchange_variables++;
  }

  
  COMMENTlong(" Assemble routine call");
  pushSource("call ");
  pushElemRoutineName( solvePtr->GetSolveNo());
  pushSource("(ielem,matno,nelem,np,              &");
  flushSource();

  pushSource( "      ");
  pushCoordinateSource();
  pushSource(",ipf,ipd,npmax                       &");
  flushSource();

  // related variables (FEM,EWISE,SCALAR variables)
  pushSource( "     ");
  for(itr.init(); !itr;++itr) {
    pushSource(",");
    pushVariableInCalled(itr());
  }

  pushSource(",");
  pushMatrixArgumentsAllocated();
  pushSource(")");
  flushSource();
  com();

  return;
}


////////////////////////////////////////////////////
//  call Neumann data routine
////////////////////////////////////////////////////
void MT_ff90smpiMUMPSCA::DoSolveCallLinearNeumannData( Solve *solvePtr)
{
  int nconds = solvePtr->GetNconds();

  if(nconds == 0) {
    COMMENTlong("No Neumann Condition");
    return;
  }

  COMMENTlong("Neumann Conditions");
  
  for(int i=0;i<nconds;i++) {

    doIthNeumannCallInSolvePM(solvePtr,i);

    //    pushSource("call ");
    //    pushNeumannRoutineName(solvePtr->GetSolveNo(),i+1);
    //    pushSource("(nbedtno(");
    //    pushSourceInt(i+1);
    //    pushSource("),firstEdatPtr,                   &");
    //    flushSource();

    //    pushSource("     npmax,");
    //    pushCoordinateSource();
    //    pushSource(",ipf,ipd                             &");
    //    flushSource();  

    //    pushSource("    ");
    /* Additional variables */
    //    orderedPtrList<Variable *>varPtrLst = solvePtr->GetIthNeumannVariablePtrLst(i);
    //    listIterator <Variable *>itr(varPtrLst);
    //
    //    /* Domain variables */
    //    pushVariableListInSolve( varPtrLst );


    pushSource(",");
    pushMatrixArgumentsAllocated();
    pushSource(")");
    flushSource();

    doIthNeumannCallInSolvePM2(solvePtr,i);

    com();
  }

  return;
}

////////////////////////////////////////////////////
//  call Dirichlet data routine
////////////////////////////////////////////////////
void MT_ff90smpiMUMPSCA::DoSolveCallLinearDirichletData( Solve *solvePtr)
{
  int dconds = solvePtr->GetDconds();

  if(dconds == 0) {
    COMMENTlong("No Dirichlet Condition");
    return;
  }

  COMMENTlong("Dirichlet Conditions");
  
  for(int i=0;i<dconds;i++) {

    doIthDirichletCallInSolvePM(solvePtr,i);

    //    pushSource("! No.");
    //    pushSourceInt(i+1);
    //    flushSource();
    //
    //    pushSource("call ");
    //    pushDirichletRoutineName(solvePtr->GetSolveNo(),i+1);
    //    pushSource("(nsetno(");
    //    pushSourceInt(i+1);
    //    pushSource("),firstNsetPtr,                &");
    //    flushSource();
    //
    //    pushSource( "       ");
    //    pushCoordinateSource();
    //    pushSource(",ipf,ipd,npmax                           &");
    //    flushSource();
    //
    //    pushSource("       ");
    //    pushVariableListInCalled(solvePtr->GetIthDirichletVariablePtrLst(i));

    pushSource(",");
    pushMatrixArgumentsCalled();
    pushSource(")");
    flushSource();

    doIthDirichletCallInSolvePM2(solvePtr,i);

  }

  com();
  return;
}

///////////////////////////////////////
// Edev routine calling sequence to edev
///////////////////////////////////////

void MT_ff90smpiMUMPSCA::DoSolveCallEdevRoutine( Solve *solvePtr)
{
  COMMENTlong("Call Edev Routine");

  writeSource("if(mumps_par%MYID .eq. 0) then");
  pushSource(" call ");
  pushEdevRoutineName( solvePtr->GetSolveNo(), 1 );  // P2FIX  NEG is 1
  pushSource("(mumps_par%RHS,ipd, &");
  flushSource();

  pushSource("  ielem,nelem,np");
  SolveElement *sePtr = solvePtr->GetIthSolveElementPtr(0);   // P2FIX NEG is 1
  pushVariableListInCalled( sePtr->GetUnknownVariablePtrLst());
  pushSource(")");
  flushSource();
  writeSource("end if");
  
  comment();

  return;
}

void MT_ff90smpiMUMPSCA::DoSolveFreeMemoryMT()
{
  COMMENTlong("deallocate matrix related arrays");

  writeSource("if(mumps_par%MYID .eq. 0) then");
  writeSource("  deallocate( mumps_par%IRN)");
  writeSource("  deallocate( mumps_par%JCN)");
  writeSource("  deallocate( mumps_par%A  )");
  writeSource("  deallocate( mumps_par%RHS)");
  com();

  writeSource("  deallocate( iptrcol )");
  com();

  writeSource("end if");
  com();

  writeSource("! Destory the instance(deallocate internal data structrues)");
  writeSource("mumps_par%JOB = -2");
  writeSource("call DMUMPS(mumps_par)");
  com();
}

void MT_ff90smpiMUMPSCA::DoSolveMakeUpdateInformationMT()
{
  // AMG make information and initialize amg
  COMMENTlong("Matrix dependent initialization");
  writeSource("! none required for MUMPSCA");
  //  writeSource("call amg_initialize()");
  //  writeSource("!call initcommon()");
  //  writeSource("!call amg_alloc_clearcounters()");
  com();

  return;
}
