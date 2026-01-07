/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999,2000
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : MT_aist90PCP.cpp
 *  Date     : 2002/06/28  (copied from MT_ff90AMGCRS.cpp)
 *  Modified : 
 *  
 *  Purpose  :
 *  
 *  1. Constructors/destructors
 *  
 */

#include "ElemGeneratorTemplate.hpp"
#include "MT_aist90PCP.hpp"


// 1. Constructors, destructors

MT_aist90PCP::MT_aist90PCP() 
{
  return;   // do nothing now
}

MT_aist90PCP::~MT_aist90PCP() 
{
  return;   // do nothing now
}




// 2. CoSolve Routine definitions
//    ElemGenerator Main  

void MT_aist90PCP::GenerateCoSolveElemGenerator (Solve *solvePtr)
{
  ElemGeneratorTemplate<MT_aist90PCP> *ptrEG =
    new ElemGeneratorTemplate<MT_aist90PCP>();
  ptrEG->NormalAssembly(solvePtr,solvePtr->GetIthSolveElementPtr(0)); //P2 limi

  return;
}


void MT_aist90PCP::F90useSolveMT( void )
{
  writeSource("! Matrix data structure related modules");
  //  writeSource("use AMGCRS");
  writeSource("use pcp90");
  com();
  
  return;
}

////////////////////////////////////////////////////
//  General routine
////////////////////////////////////////////////////
void MT_aist90PCP::pushMatrixArgumentsCalled()
{
  pushSource("AMAT,VFG,ICOL0,ICPNT,NELT,neq,IWORK,KIWORK");
  return;
}

void MT_aist90PCP::writeMatrixDeclarations()
{
  writeReal8Ptr1("AMAT,VFG");                  // matrix, load vector
  writeInteger4Ptr1("ICOL0,ICPNT,IWORK");      // index for matrix
  writeInteger4sc("NELT,NELTES,KIWORK");       // array size
  writeInteger4Ptr1("IEPNT");                  // ielem pointer

  //  writeInteger4Ptr2("NPP");                    // FORCE related(02/12/08)
  return;
}

//  solve routine matrix dependent parts
void MT_aist90PCP::DoSolveVariableDefinitionsMT()
{
  COMMENTlong("Matrix related variables");

  writeMatrixDeclarations();    

  writeReal8Ptr1("RWORK");   


  writeInteger4sc("NNZERO");
  writeInteger4sc("NOVLAP");
  writeInteger4sc("NLAG");
  writeInteger4sc("NCON_PCP,KCON_PCP");
  writeInteger4sc("NENOD");
  writeInteger4sc("NISIZ,NRSIZ");
  com();

  //  writeInteger4Ptr1("ABAK");
  com();

  return;
}

void MT_aist90PCP::pushMatrixArgumentsAllocated(void)
{
  pushMatrixArgumentsCalled();             // same in Fortran 90
  return;
}



void MT_aist90PCP::DoSolveInitializerMT( Solve *solvePtr)
{
  // do nothing for aistpcp90
  return;
}


// ### Matrix allocation in solve routine

void MT_aist90PCP::DoSolveMatrixAllocate( Solve *)
{
  COMMENTlong("Calculate maxmal number of element connection to one node");
  writeSource("call nc_connectp2(npmax,ielem,nelem,np, ncmax)");
  com();

  writeSource("call reportmodule('nc_connectp2')");
  com();

  COMMENTlong("Calculate maximum connecting node between nodes");
  writeSource("nenfremax = 0      ! nenfremax is maximum DOF at node");
  writeSource("do i=1,neg");       
  writeSource(" do j=1,maxElementNodes");
  writeSource("  if(nenfremax < nenfre(j,i)) nenfremax=nenfre(j,i)");
  com();

  // PCP check
  writeSource("  if(NDF_PCP .NE. nenfre(j,i)) then");
  writeSource("    stop 'PCP must have same DOF at each node.'");
  writeSource("  end if");
  com();
   
  writeSource(" end do");
  writeSource("end do");
  com();

  writeSource("!ndfmax : max element freedom");
  writeSource("!ncon   : over estimated DOF at each row in final matrix");
  com();
  writeSource("ndfmax = nenfremax * maxElementNodes");
  writeSource("ncon   = nenfremax * maxElementNodes * ncmax");


  COMMENTlong("Generate PCP index");
  com();

  writeSource("NNZERO = ncon    ! this is maximum");
  com();

  writeSource("NOVLAP = npmax   ! ???");
  writeSource("NLAG   = 0");
  com();


  writeSource("NCON_PCP  = 0");
  writeSource("KCON_PCP  = 0");
  com();

  writeSource("KIWORK = 5 * npmax");
  writeSource("allocate(IWORK(KIWORK))");
  com();

  // Make IEPNT array   P2 limit
  writeSource("allocate(IEPNT(nelem+1))");
  writeSource("do i=1,nelem+1");
  writeSource(" IEPNT(i) = np*(i-1)+1");
  writeSource("end do");
  com();

  writeSource("NENOD = np * nelem");
  com();

  // evaluate array size
  com();
  writeSource("! evaluate array size");
  com();

  writeSource("call PCP_MEMSI1(NDF_PCP         , npmax,NNZERO,  &");
  writeSource("                NOVLAP,NLAG,NCON_PCP,KCON_PCP,   &");
  writeSource("                IOPT,nprocs,myrank,NELTES,NISIZ, &");
  writeSource("                NRSIZ,nelem,iedom,ielem,IEPNT,   &");
  writeSource("                NENOD,IWORK,KIWORK                )");
  com();
  writeSource("deallocate(IWORK)    ! size KIWORK");


  com();

  

  writeSource("allocate(ICOL0(NELTES))"); 
  writeSource("allocate(ICPNT(neq+1))          ! NP*NDF+1");

  //  writeSource("allocate(IABAK(NELT))");
  writeSource("allocate(IWORK(NISIZ))");
  writeSource("allocate(RWORK(NRSIZ))");
  com();
  
  writeSource("call PCP_MKINDX( npmax,  nelem, NDF_PCP   , &");
  writeSource("                 nelem * np   , IEPNT     , &");
  writeSource("                 ielem  ,iedom, NELT      , &");
  writeSource("                 NELTES ,ICOL0, ICPNT     , &");
  writeSource("                 NISIZ  ,IWORK, myrank       )");
  com();
  com();

  //PCP_MKMTNT (2002/12/05)
  //  writeSource("allocate(MTNEW(NLMAX/NDF)");
  //  writeSource("allocate(NT   (npmax)");
  //  writeSource("allocate(NTNEW(npmax+1)");
  //  com();
  //  writeSource("call PCP_MKMTNT( npmax  ,NDF_PCP,nelem    , &");
  //  writeSource("                 IEPNT  ,ielem  ,NT       , &");
  //  writeSource("                 NTNEW  ,MTNEW  ,NLMAX       )");

  // allocate matrix array
  writeSource("allocate(AMAT(NELT))");
  writeSource("allocate(VFG(neq))");
  com();
  writeSource("call zerod(AMAT,NELT)");
  writeSource("call zerod(VFG ,neq )");
  com();

  // force related routine
  //  writeSource("allocate(NPP(nprocs,neq))"); // FORCE(02/12/08)
  //  writeSource("do i=1,neq");
  //  writeSource(" do j=1,nprocs");
  //  writeSource("  NPP(j,i)=0");
  //  writeSource(" end do");
  //  writeSource("end do");
  //  com();

  writeSource("! ?????????    deallocate(IWORK)");
  com();

  return;
}


////////////////////////////////////////////////////
//  call assemble routine
////////////////////////////////////////////////////
void MT_aist90PCP::DoSolveCallAssembleRoutine( Solve *solvePtr)
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
  //  pushSource("(myrank,nprocs,IEDOM,NPP,ielem,matno,nelem,np,   &");
  pushSource("(myrank,nprocs,IEDOM,ielem,matno,nelem,np,   &");
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
  pushSource(")");          // neq is added temporary
  flushSource();
  com();

  return;
}


////////////////////////////////////////////////////
//  call Neumann data routine
////////////////////////////////////////////////////
void MT_aist90PCP::DoSolveCallLinearNeumannData( Solve *solvePtr)
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
void MT_aist90PCP::DoSolveCallLinearDirichletData( Solve *solvePtr)
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

void MT_aist90PCP::DoSolveCallEdevRoutine( Solve *solvePtr)
{

  COMMENTlong("Call Edev Routine");

  pushSource("call ");
  pushEdevRoutineName( solvePtr->GetSolveNo(), 1 );  // P2FIX  NEG is 1
  pushSource("(resvec,ipd, &");
  flushSource();

  pushSource("  ielem,nelem,np");
  SolveElement *sePtr = solvePtr->GetIthSolveElementPtr(0);   // P2FIX NEG is 1
  pushVariableListInCalled( sePtr->GetUnknownVariablePtrLst());
  pushSource(")");
  flushSource();
  
  comment();

  return;
}

void MT_aist90PCP::DoSolveFreeMemoryMT()
{
  COMMENTlong("deallocate matrix related arrays");
  writeSource("deallocate(IEPNT)");
  com();

  writeSource("deallocate(vfg)");
  writeSource("deallocate(resvec)");
  com();
}

void MT_aist90PCP::DoSolveMakeUpdateInformationMT()
{
  // AMG make information and initialize amg
  COMMENTlong("Matrix dependent initialization");
  writeSource("! none required for AMGCRS");
  //  writeSource("call amg_initialize()");
  //  writeSource("!call initcommon()");
  //  writeSource("!call amg_alloc_clearcounters()");
  com();

  return;
}
