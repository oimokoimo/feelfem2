/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999,2000
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : MT_ff90AMGDrama.cpp
 *  Date     : 2000/10/19
 *  Modified : 2001/02/02 orderedPtrList
 *  
 *  Purpose  :
 *  
 *  1. Constructors/destructors
 *  
 */

#include "ElemGeneratorTemplate.hpp"
#include "MT_ff90PAMGCRS.hpp"


// 1. Constructors, destructors

MT_ff90PAMGCRS::MT_ff90PAMGCRS() 
{
  return;   // do nothing now
}

MT_ff90PAMGCRS::~MT_ff90PAMGCRS() 
{
  return;   // do nothing now
}




// 2. CoSolve Routine definitions
//    ElemGenerator Main  

void MT_ff90PAMGCRS::GenerateCoSolveElemGenerator (Solve *solvePtr)
{
  ElemGeneratorTemplate<MT_ff90PAMGCRS> *ptrEG =
    new ElemGeneratorTemplate<MT_ff90PAMGCRS>();
  ptrEG->DistributedAssembly(solvePtr,solvePtr->GetIthSolveElementPtr(0)); //P2 limi

  return;
}


void MT_ff90PAMGCRS::F90useSolveMT( void )
{
  writeSource("! Matrix data structure related modules");
  writeSource("use PAMGCRS");
  com();
  
  return;
}



////////////////////////////////////////////////////
//  General routine
////////////////////////////////////////////////////
void MT_ff90PAMGCRS::pushMatrixArgumentsCalled()
{
  pushSource("valmat,vfg,indrow,iptrcol,neq,ipd_halo,nhalo");
  return;
}

void MT_ff90PAMGCRS::writeMatrixDeclarations()
{
  writeInteger4sc("nhalo");
  writeInteger4Ptr1("ipd_halo");
  writeReal8Ptr1("valmat,vfg");
  writeInteger4Ptr1("indrow,iptrcol");
  return;
}

//  solve routine matrix dependent parts
void MT_ff90PAMGCRS::DoSolveVariableDefinitionsMT()
{
  COMMENTlong("Matrix related variables");

  writeMatrixDeclarations();    // distributed CRS,
  writeInteger4Ptr1("sort_ex");
  writeInteger4sc("ncof");
  com();

  writeSource("type (amg_penv),       pointer :: penv");
  writeSource("type (amg_update_info),pointer :: pupdate");
  writeSource("type (amg_global_info),pointer :: glinfo");
  com();
  return;
}


void MT_ff90PAMGCRS::DoSolveInitializerMT(Solve *)
{
  // do nothing for PAMGCRS
  return;
}

//  elem routine matrix dependent parts
void MT_ff90PAMGCRS::doElemVariableDefinitionsMT()
{
  writeMatrixDeclarations();
  writeInteger4sc("ncof");
  return;
}

void MT_ff90PAMGCRS::pushMatrixArgumentsAllocated(void)
{
  pushMatrixArgumentsCalled();             // same in Fortran 90
  return;
}



// ### Matrix allocation in solve routine

void MT_ff90PAMGCRS::DoSolveMatrixAllocate( Solve *)
{
  COMMENTlong("Calculate maxmal number of element connection to one node");
  writeSource("call pnc_connect90(mypeid,npmax,enptr   ,con   ,nelem   , &");
  writeSource("                                enptr_ex,con_ex,nelem_ex, &");
  writeSource("                                ncmax                     )");
  com();

  writeSource("if(myrank == 0) call preportmodule('PNC_CONNECT90')");
  com();

  COMMENTlong("Make distributed AMG-CRS array");
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
  
  writeSource("call pmkAMGCRShalo(nouter,ndno,peno,ipf_ex,ipd_ex, &");
  writeSource("                   ipd_halo,sort_ex                )");
  writeSource("if(myrank==0) call preportmodule('pmkAMGCRShalo')");
  com();

  writeSource("call pmkAMGCRSindex(mypeid,nprocs,            &");
  writeSource("                    neq,isumup,               &");
  writeSource("                    ndfmax,ncon,              &");
  writeSource("                    ipf,ipd,npmax,            &");
  writeSource("                    ndno,peno,nouter,         &");
  writeSource("                    ipf_ex,ipd_ex,ipd_halo,   &");
  writeSource("                    enptr,con,nelem,          &");
  writeSource("                    enptr_ex,con_ex,nelem_ex, &");
  writeSource("                    iptrcol,indrow,ncof,nhalo )");
  com();
  
  writeSource("if(myrank == 0) call preportmodule('pmkAMGCRSindex')");
  com();

  // allocate matrix array
  COMMENTlong("Allocate matrix, right hand side");
  MODULEmallocERT("valmat","CRS distributed matrix","ncof","1");
  MODULEmallocERT("vfg","Right hand side","neq","1");
  MODULEzeroclearD("valmat","ncof");
  MODULEzeroclearD("vfg"   ,"neq" );
  com();

  return;
}


////////////////////////////////////////////////////
//  call assemble routine
////////////////////////////////////////////////////
void MT_ff90PAMGCRS::DoSolveCallAssembleRoutine( Solve *solvePtr)
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
  pushSource("(mypeid,nprocs,isumup,               &");
  flushSource();

  writeSource("      enptr,con,nelem,                         &");

  pushSource( "      ");
  pushCoordinateSource();
  pushSource(",ipf,ipd,npmax,                       &");
  flushSource();

  writeSource("      enptr_ex,con_ex,nelem_ex,                &");

  pushSource( "      ndno,peno,");
  pushCoordinateExternalSource();
  pushSource(",ipf_ex,ipd_ex,nouter &");
  flushSource();

  // related variables (FEM,EWISE,SCALAR variables)
  pushSource( "     ");
  for(itr.init(); !itr;++itr) {
    pushSource(",");
    pushVariableInCalled(itr());
  }

  //exterior node values
  if(fem_exchange_variables >0) {
    for(itr.init(); !itr;++itr) {
      if(itr()->GetType() == VAR_FEM) {
	pushSource(",");
	pushFEMVariableExternalInCalled(itr());
      }
    }
  }
  pushSource(",");
  pushMatrixArgumentsAllocated();
  pushSource(",ncof)");
  flushSource();
  com();

  return;
}


////////////////////////////////////////////////////
//  call Neumann data routine
////////////////////////////////////////////////////
void MT_ff90PAMGCRS::DoSolveCallLinearNeumannData( Solve *solvePtr)
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
    //    pushSource("(mypeid,nprocs,                        &");
    //    flushSource();
    
    //    pushSource("     nbedtno(");
    //    pushSourceInt(i+1);
    //    pushSource("),firstDramaEdatPtr,isumup,           &");
    //    flushSource();

    //    pushSource("     npmax,");
    //    pushCoordinateSource();
    //    pushSource(",ipf,ipd,                             &");
    //    flushSource();  

    //    pushSource("     nouter,ndno,peno,ipf_ex,ipd_ex,");
    //    pushCoordinateExternalSource();   // f90 is the same in called and in solve
    //    pushSource("       &");
    //    flushSource();

    //    pushSource("    ");
    /* Additional variables */
    //    orderedPtrList<Variable *>varPtrLst = solvePtr->GetIthNeumannVariablePtrLst(i);
    //    listIterator <Variable *>itr(varPtrLst);
    //
    /* Domain variables */
    //    pushVariableAndFEMExternalListInSolve( varPtrLst );
    
    pushSource(",");
    pushMatrixArgumentsAllocated();
    pushSource(")");
    flushSource();
    com();

    doIthNeumannCallInSolvePM2(solvePtr,i);

    com();
  }

  return;
}

////////////////////////////////////////////////////
//  call Dirichlet data routine
////////////////////////////////////////////////////
void MT_ff90PAMGCRS::DoSolveCallLinearDirichletData( Solve *solvePtr)
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
    //    pushSource("(mypeid,nprocs,                       &");
    //    flushSource();
    //
    //    pushSource("       nsetno(");
    //    pushSourceInt(i+1);
    //    pushSource("),firstDramaNsetPtr,                &");
    //    flushSource();
    //
    //    writeSource("       isumup,                                     &");
    //    writeSource("       enptr,con,nelem,                            &");
    //
    //    pushSource( "       ");
    //    pushCoordinateSource();
    //    pushSource(",ipf,ipd,npmax,                          &");
    //    flushSource();
    //
    //    writeSource("       enptr_ex,con_ex,nelem_ex,                   &");
    // 
    //    pushSource("       ndno,peno,");
    //    pushCoordinateExternalSource();
    //    pushSource(",ipf_ex,ipd_ex,nouter    &");
    //    flushSource();
    //
    //    pushSource("       ");
    //    pushVariableAndFEMExternalListInCalled(solvePtr->GetIthDirichletVariablePtrLst(i));
    //

    pushSource(",");
    pushMatrixArgumentsCalled();
    pushSource(")");
    flushSource();

    doIthDirichletCallInSolvePM2(solvePtr,i);

    com();


  }

  com();
  return;
}

///////////////////////////////////////
// Edev routine calling sequence to edev
///////////////////////////////////////

void MT_ff90PAMGCRS::DoSolveCallEdevRoutine( Solve *solvePtr)
{

  COMMENTlong("Call Edev Routine");

  pushSource("call ");
  pushEdevRoutineName( solvePtr->GetSolveNo(), 1 );  // P2FIX  NEG is 1
  pushSource("(mypeid,resvec,ipd, &");
  flushSource();

  pushSource("  enptr,con,nelem");
  SolveElement *sePtr = solvePtr->GetIthSolveElementPtr(0);   // P2FIX NEG is 1
  pushVariableListInCalled( sePtr->GetUnknownVariablePtrLst());
  pushSource(")");
  flushSource();
  
  comment();

  return;
}

void MT_ff90PAMGCRS::DoSolveFreeMemoryMT()
{
  writeSource("deallocate(indrow,iptrcol)");
  writeSource("deallocate(valmat,vfg)  ");
  writeSource("deallocate(resvec)");
  com();
}

void MT_ff90PAMGCRS::DoSolveMakeUpdateInformationMT()
{
  // AMG make information and initialize amg
  COMMENTlong("make amg information");
  writeSource("call amg_initialize()");
  com();

  writeSource("!call initcommon()");
  writeSource("!call amg_alloc_clearcounters()");
  com();

  writeSource("call pmkAMGCRSupdate(myrank,nprocs,mypeid,           &");
  writeSource("                     neq,nhalo,isumup,               &");
  writeSource("                     ndno,peno,nouter,               &");
  writeSource("                     ipf_ex,ipd_ex,ipd_halo,sort_ex, &");
  writeSource("                     iptrcol,indrow,ncof,            &");
  writeSource("                     penv,pupdate,glinfo             )");
  com();
 
  writeSource("if(myrank.eq.0) call preportmodule('pmkAMGCRSupdate')");
  com();

  return;
}
