/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : MT_P2CRSLOC.cpp
 *  Date     : 2000/03/24
 *  Modified : 2000/03/24
 *  Modified : 2001/02/02 orderedPtrList
 *  
 *  Purpose  : Distributed CRS matrix model
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
#include "feelfem.hpp"
#include "ElemGeneratorTemplate.hpp"
#include "MT_P2CRSLOC.hpp"

MT_P2CRSLOC::MT_P2CRSLOC() 
{
  return;   // do nothing now
}

MT_P2CRSLOC::~MT_P2CRSLOC()  = default;


////////////////////////////////////////////////////
//  General routine
////////////////////////////////////////////////////
void MT_P2CRSLOC::pushMatrixArgumentsCalled()
{
  pushSource("valmat,vfg,indrow,iptrcol,neq");
  return;
}

void MT_P2CRSLOC::writeMatrixDeclarations()
{
  writeSource("      real*8  valmat(*)");
  writeSource("      real*8  vfg(*)");
  writeSource("      integer indrow(*)");
  writeSource("      integer iptrcol(*)");
  return;
}

void MT_P2CRSLOC::doElemVariableDefinitionsMT()   
{
  writeMatrixDeclarations();
  return;
}

void MT_P2CRSLOC::pushMatrixArgumentsAllocated(void)
{
  pushSource("feel(np_VALMAT),feel(np_VFG),feel(np_INDROW),feel(np_IPTRCOL),neq");
  return;
}

void MT_P2CRSLOC::DoSolveVariableDefinitionsMT(void)
{
  doNothingNow("void MT_P2CRSLOC::DoSolveVariableDefinitionsMT(void)");
  // do nothing now
}

////////////////////////////////////////////////////
//  Matrix allocation   ( it would be template, if CRS is generalized)
////////////////////////////////////////////////////
void MT_P2CRSLOC::DoSolveMatrixAllocate( Solve *)
{
  COMMENTlong("Matrix array allocation (Distributed CRS:Program Model FEELP2");

  writeSource("      call f_alloc_push");
  writeSource("      call f_alloc(np_nc,'nc',npmax,0,0)");
  writeSource("      call pnc_connect(mypeid,feel(np_nc),npmax,");
  writeSource("     $                 feel(np_e),feel(np_c),nelem,");
  writeSource("     $                 feel(np_enptr_ex),feel(np_con_ex),nelem_ex,");
  writeSource("     $                 ncmax)");
  writeSource("*");
  writeSource("* clear np_nc");
  writeSource("      call f_alloc_pop");
  com();
  writeSource("      if(myrank.eq.0) call preportmodule('PNC_CONNECT')");
  comment();

  writeSource("* Make distributed CRS array");
  com();
  writeSource("      nenfremax = 1");
  writeSource("      do 15 j=1,NEG");
  writeSource("      do 15 i=1,MAX_ELEMENT_NODES");
  writeSource("       if(nenfremax .LT. nenfre(i,j)) nenfremax=nenfre(i,j)");
  writeSource(" 15   continue");
  com();
  writeSource("      ncon = MAX_ELEMENT_NODES*NCMAX*nenfremax");
  writeSource("      call f_alloc(np_IP,'SOLVE(IP)',neq+1,0,0)");

  writeSource("      call f_alloc_push");
  writeSource("      call f_alloc(np_IC,'solve(IC)',neq*ncon,0,0)");
  com();
  writeSource("      call pmkCRSindex(mypeid,nprocs,ndfmax,");
  writeSource("     $     feel(np_isumup),myeqfrom,myeqto,neqtotal,");
  writeSource("     $     feel(np_e),feel(np_c),nelem,");
  writeSource("     $     feel(np_ipf),feel(np_ipd),npmax,");
  writeSource("     $     feel(np_enptr_ex),feel(np_con_ex),nelem_ex,");
  writeSource("     $     feel(np_ndno),feel(np_peno),");
  writeSource("     $     feel(np_ipfex),feel(np_ipdex),nouter,");
  writeSource("     $     feel(np_IC),feel(np_IP),ncon,neq,");
  writeSource("     $     feel(np_IC),");
  writeSource("     $     ncof,maxnzpr)");
  com();
  
  writeSource("      if(ncof .gt. ncon*neq) then");
  writeSource("        call abortexit(myrank,'ncof>ncon*neq')");
  writeSource("      endif");
  com();


  writeSource("* memory move (actual movment done in pmkCRSindex)");
  writeSource("      call f_alloc_pop");
  writeSource("      call f_alloc(np_indrow,'INDROW',ncof,0,0)");
  writeSource("      np_iptrcol = np_IP");
  com();
  writeSource("      if(myrank.eq.0) call preportmodule('pmkCRSindes')");
  writeSource("* allocation");
  writeSource("      call f_alloc(np_valmat,'solve(valmat)',ncof,1,0)");
  writeSource("      call f_alloc(np_vfg   ,'solve(vfg)',   neq ,1,0)");
  writeSource("      call zerod(feel(np_valmat),ncof)");
  writeSource("      call zerod(feel(np_vfg)   ,neq )");
  comment();

  return;
}


////////////////////////////////////////////////////
//  call assemble routine
////////////////////////////////////////////////////
void MT_P2CRSLOC::DoSolveCallAssembleRoutine(Solve *solvePtr)
{
  int fem_exchange_variables;
  SolveElement *sePtr = solvePtr->GetIthSolveElementPtr(0); // P2 FIXED
  orderedPtrList <Variable *> varPtrLst = sePtr->GetVariablePtrLst();
  
  fem_exchange_variables = 0;
  listIterator <Variable *> itr(varPtrLst);
  for(itr.init(); !itr;++itr) {
    if(itr()->GetType() == VAR_FEM) fem_exchange_variables++;
  }

  
  comment();
  pushSource("      call ");
  pushElemRoutineName( solvePtr->GetSolveNo());
  pushSource("(mypeid,nprocs,");
  flushSource();

  writeSource("     $   feel(np_isumup),myeqfrom,myeqto,neqtotal,");
  writeSource("     $   feel(np_e),feel(np_c),nelem,");
  writeSource("     $   x,y,feel(np_ipf),feel(np_ipd),npmax");

  // related variables 
  pushSource( "     $   ");
  for(itr.init(); !itr;++itr) {
    string a;
    pushSource(",");
    NameVariableInCalled(itr(),a);
    pushSource(a);
  }
  pushSource(",");
  flushSource();

  //exterior node values
  writeSource("     $   feel(np_enptr_ex),feel(np_con_ex),nelem_ex,");
  writeSource("     $   nouter,feel(np_ndno),feel(np_peno),");
  writeSource("     $   feel(np_xex),feel(np_yex),feel(np_ipfex),feel(np_ipdex),");

  pushSource("     $   ");
  if(fem_exchange_variables >0) {
    for(itr.init(); !itr;++itr) {
      if(itr()->GetType() == VAR_FEM) {
	pushSource("feel(npfex_");
	pushSource(itr()->GetName());
	pushSource("),");
      }
    }
  }
  pushMatrixArgumentsAllocated();
  pushSource(",ncof)");
  flushSource();
  return;
}


////////////////////////////////////////////////////
//  call Neumann data routine
////////////////////////////////////////////////////
void MT_P2CRSLOC::DoSolveCallLinearNeumannData( Solve *solvePtr)
{
  int nconds = solvePtr->GetNconds();

  if(nconds == 0) {
    COMMENTlong("No Neumann Condition");
    return;
  }

  COMMENTlong("Neumann Conditions");
  
  for(int i=0;i<nconds;i++) {
    pushSource("      no_inb = inbctr2search(nbedtno(");
    pushSourceInt(i+1);
    pushSource("),inbctr2,nbedat)");
    flushSource();

    pushSource("      call ");
    pushNeumannRoutineName(solvePtr->GetSolveNo(),i+1);
    pushSource("(mypeid,nprocs,");
    flushSource();

    writeSource("     $     inbctr2(1,no_inb),inbctr2(2,no_inb),");
    writeSource("     $     feel(inbctr2(3,no_inb)),feel(inbctr2(4,no_inb)),");
    writeSource("     $     feel(inbctr2(5,no_inb)),");
    writeSource("     $     feel(np_isumup),myeqfrom,myeqto,neqtotal,");
    writeSource("     $     x,y,feel(np_ipf),feel(np_ipd),npmax,");
    writeSource("     $     feel(np_ndno),feel(np_peno),feel(np_xex),feel(np_yex),");
    writeSource("     $     feel(np_ipfex),feel(np_ipdex),nouter,");

    pushSource("     $     ");
    pushMatrixArgumentsAllocated();
    flushSource();
    
    pushSource("     $");
    pushVariableListInCalled( solvePtr->GetIthNeumannVariablePtrLst(i));
 
    /* _ex variables for FEM variable */
    orderedPtrList <Variable *>varPtrLst=solvePtr->GetIthNeumannVariablePtrLst(i);
    listIterator <Variable *>itr(varPtrLst);
    for(itr.init(); !itr; ++itr ){
      if(itr()->GetType() != VAR_FEM) continue;
      pushSource(",");
      pushFEMVariableExternalInSolve(itr());
    }

    pushSource(")");
    flushSource();
    
    comment();
  }

  return;
}

////////////////////////////////////////////////////
//  call Dirichlet data routine
////////////////////////////////////////////////////
void MT_P2CRSLOC::DoSolveCallLinearDirichletData( Solve *solvePtr)
{
  int dconds = solvePtr->GetDconds();

  if(dconds == 0) {
    COMMENTlong("No Dirichlet Condition");
    return;
  }

  COMMENTlong("Dirichlet Conditions");
  
  for(int i=0;i<dconds;i++) {
    pushSource("      nbdno = nsetno(");
    pushSourceInt(i+1);
    pushSource(")");
    flushSource();

    pushSource("      call ");
    pushDirichletRoutineName(solvePtr->GetSolveNo(),i+1);
    pushSource("(mypeid,nprocs,");
    flushSource();

    writeSource("     $     idbctr2(1,nbdno),idbctr2(2,nbdno),");
    writeSource("     $     idbctr2(3,nbdno),");
    writeSource("     $     feel(idbctr2(4,nbdno)),");
    writeSource("     $     feel(idbctr2(5,nbdno)),");
    writeSource("     $     feel(np_isumup),myeqfrom,myeqto,neqtotal,");
    writeSource("     $     feel(np_e),feel(np_c),nelem,");
    writeSource("     $     x,y,");
    writeSource("     $     feel(np_ipf),feel(np_ipd),npmax,");
    writeSource("     $     feel(np_enptr_ex),feel(np_con_ex),nelem_ex,");
    writeSource("     $     feel(np_ndno),feel(np_peno),");
    writeSource("     $     feel(np_xex),feel(np_yex),");
    writeSource("     $     feel(np_ipfex),feel(np_ipdex),nouter,");
    writeSource("     $     feel(np_iptrcol),feel(np_indrow),");
    writeSource("     $     feel(np_valmat),feel(np_vfg),neq,ncof");

    pushSource ("     $");
    pushVariableListInCalled( solvePtr->GetIthDirichletVariablePtrLst(i));
 
    /* _ex variables for FEM variable */
    orderedPtrList <Variable *>varPtrLst = 
      solvePtr->GetIthDirichletVariablePtrLst(i);

    listIterator <Variable *>itr(varPtrLst);
    for(itr.init(); !itr; ++itr ){
      if(itr()->GetType() != VAR_FEM) continue;
      
      pushSource(",");
      pushFEMVariableExternalInSolve(itr());
      
    }
    pushSource(")");
    flushSource();
    
    comment();
  }

  return;
}

///////////////////////////////////////
// Edev routine
///////////////////////////////////////

void MT_P2CRSLOC::DoSolveCallEdevRoutine(Solve *solvePtr)
{

  COMMENTlong("Call Edev Routine");

  pushSource("      call ");
  pushEdevRoutineName( solvePtr->GetSolveNo(), 1 );  // P2FIX  NEG is 1
  pushSource("(myrank,feel(np_resvec),feel(np_ipd),");
  flushSource();

  writeSource("     $      feel(np_e),feel(np_c),nelem");

  SolveElement *sePtr = solvePtr->GetIthSolveElementPtr(0);   // P2FIX NEG is 1
  pushSource("     $");
  pushVariableListInCalled( sePtr->GetUnknownVariablePtrLst());
  pushSource(")");
  flushSource();
  
  comment();

  return;
}


void MT_P2CRSLOC::DoSolveFreeMemoryMT()
{
  PopReturn();
  return;
}

// CoSolve Routine definitions
// ElemGenerator Main  

void MT_P2CRSLOC::GenerateCoSolveElemGenerator (Solve *solvePtr)
{
  ElemGeneratorTemplate<MT_P2CRSLOC> *ptrEG =
    new ElemGeneratorTemplate<MT_P2CRSLOC>();
  ptrEG->DistributedAssembly(solvePtr,solvePtr->GetIthSolveElementPtr(0)); //P2 limi

  return;
}



