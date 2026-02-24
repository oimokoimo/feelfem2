/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : feelP2.cpp
 *  Date     : 1999/11/15
 *  Modified : 1999/11/15
 *  Modified : 2001/02/02 orderedPtrList
 *  
 *  Purpose  : feelP2 programming style implementation
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
#include "feelfuncs.hpp"

#include "Quadrature.hpp"
#include "Dirichlet.hpp"
#include "Neumann.hpp"
#include "PM_feelP2.hpp"

PM_feelP2::PM_feelP2()
{
  return;
}

PM_feelP2::~PM_feelP2() = default;


//////////////////////////////////////////////////////////////////
void PM_feelP2::OpenSource(const char *filename)
{
  startSource( filename );
  Fortran77GeneratorSetFP( GetSourceFP() );
  return;
}

void PM_feelP2::OpenSource(const char *filename, int makeFlag)
{
  startSource( filename , makeFlag);
  Fortran77GeneratorSetFP( GetSourceFP() );
  return;
}

void PM_feelP2::CloseSource()
{
  endSource(  );
  Fortran77GeneratorSetFP( NULL );
  return;
}

//////////////////////////////////////////////////////////////////
void PM_feelP2::commentPM()
{
  writeSource("* FEEL P2 Program Model");
  return;
}

/////////////////////////////////////////////////////////////////
//  General File handling functions
/////////////////////////////////////////////////////////////////
const char *PM_feelP2::GetSourceName( const char *routineName)
{
  int   len = stringLength(routineName)+3;
  char *ptr = new char[len];
  
  sprintf(ptr,"%s.f",routineName);
  return(ptr);
}

/////////////////////////////////////////////////////////////////
//  General Process function in Program Model feelP2
/////////////////////////////////////////////////////////////////

void PM_feelP2::MODULEzeroclearD(const char *varname, const char *size)
{
  char buf[BUFSIZ];

  sprintf(buf,"      call zerod(%s,%s)",varname,size);
  writeSource(buf);
  
  return;
}

void PM_feelP2::MODULEzeroclearI(const char *varname, const char *size)
{
  char buf[BUFSIZ];

  sprintf(buf,"      call zeroi(%s,%s)",varname,size);
  writeSource(buf);
  
  return;
}

void PM_feelP2::MODULEmalloc(const char *ptr,const char *comment,const char *size, const char *type)
{
  mallocF77(ptr,comment,size,type);
  return;
}

void PM_feelP2::MODULEmallocERT(const char *ptr,const char *comment,const char *size, const char *type)
{
  mallocF77imode(ptr,comment,size,type);
  return;
}

void PM_feelP2::MODULEmallocCHK()
{
  mallocF77check();
  com();
  
  return;
}

/////////////////////////////////////////////////////////////////
//  Generator components for Problem Model feelP2
/////////////////////////////////////////////////////////////////
void PM_feelP2::NameVariableInCalled( Variable *valPtr, string &name)
{
  char buf[BUFSIZ];
  switch(valPtr->GetType()) {
  case VAR_FEM:
    sprintf(buf,"fem_%s",valPtr->GetName());
    break;
    
  case VAR_EWISE:
  case VAR_EWISE_A:
    sprintf(buf,"ew_%s",valPtr->GetName());
    break;
    
  case VAR_DOUBLE:
  case VAR_INT:
    sprintf(buf,"sc_%s",valPtr->GetName());
    break;
    
  case VAR_CONST:
    sprintf(buf,"co_%s",valPtr->GetName());
    break;
    
  default:
    assert(1==0);
  }
  
  name = buf;
  return;
}

void PM_feelP2::pushVariableListInCalled( orderedPtrList <Variable *>varPtrLst)
{
  listIterator <Variable *> itr(varPtrLst);
  for(itr.init(); !itr;++itr) {
    string a;
    pushSource(",");
    NameVariableInCalled(itr(),a);
    pushSource(a);
  }
  return;

}

void PM_feelP2::pushVariableListInCalled( list <Variable *> varPtrLst)
{
  listIterator <Variable *> itr(varPtrLst);
  for(itr.init(); !itr;++itr) {
    string a;
    pushSource(",");
    NameVariableInCalled(itr(),a);
    pushSource(a);
  }
  return;

}

///////////////////////////////////////////////////////////
void PM_feelP2::DefaultParameterBlock()
{
  writeSource("      parameter (MAX_FEEL    = 10000000)");
  writeSource("      parameter (MAX_DOMAIN  = 10)");
  writeSource("      parameter (MAX_EDATSET = 38)");
  writeSource("      parameter (MAX_NODESET = 20)");
  writeSource("      parameter (MAX_NUMSET  = 10)");
  writeSource("      parameter (MAX_EWISE   = 20)");
  writeSource("      parameter (MAX_IP      =  7)");
  writeSource("      parameter (MAX_SOLVE   = 10)");
  comment();
}


void PM_feelP2::PopReturn()                     // General in PM
{
  //  writeSource("      np_work = np_push");
  writeSource("      call f_alloc_pop");
  com();

  return;
}


void PM_feelP2::DoSolveReport( int no, const char *s)
{
  pushSource("      call report('solve");
  pushSourceInt(no);
  pushSource(" : ");
  pushSource(s);
  pushSource("')");
  flushSource();
  
  return;
}
    

/////////////////////////////////////////////////////////////////
// General components for generating subroutines
/////////////////////////////////////////////////////////////////

void PM_feelP2::DoArgumentSequenceFromMain
( char                         *subroutineName,
  orderedPtrList <Variable *>&varPtrLst       )
{
  char buf[BUFSIZ];
  sprintf(buf,"      subroutine %s(feel,imode,x,y",subroutineName);
  writeSource(buf);

  pushSource("     &");

  pushVariableListInCalled( varPtrLst);
  pushSource(")");
  flushSource();
  
  return;
}

/////////////////////////////////////////////////////////////////////////////
void PM_feelP2::ArgumentVariableDeclaration(Variable *varPtr)
{
  string a;
  NameVariableInCalled(varPtr,a);
  pushSource("      ");

  switch(varPtr->GetType()) {
  case VAR_FEM:
    pushSource("dimension ");
    pushSource(a);
    pushSource("(*)");
    flushSource();
    break;
    
  case VAR_EWISE:
  case VAR_EWISE_A:                     // P2 FIX

    pushSource("dimension ");
    pushSource(a);
    pushSource("(*)");
    flushSource();
    break;


    
  case VAR_DOUBLE:
    pushSource("real*8    ");
    pushSource(a);
    flushSource();
    break;

  case VAR_INT:
    pushSource("integer   ");
    pushSource(a);
    flushSource();
    break;
    
  case VAR_CONST:
    pushSource("real*8    ");
    pushSource(a);
    flushSource();
    break;
    
  default:
    assert(1==0);
  }
  
  return;
}

  

/////////////////////////////////////////////////////////////////////////////
void PM_feelP2::ArgumentVariableDeclarationLst(orderedPtrList <Variable *>& varPtrLst)
{
  listIterator <Variable *> itr(varPtrLst);
  for(itr.init(); !itr;++itr) {
    ArgumentVariableDeclaration(itr());
  }  
  
  return;
}



/////////////////////////////////////////////////////////////////
// Routine name for feelP2 program model
// Get  Routine name series  [Definition of routine names]
// push Routine name series  [Writing source file routine names]
/////////////////////////////////////////////////////////////////
const char *PM_feelP2::GetSolveRoutineName( int no )
{
  char *ptr = new char[8];
  if(no < 10) {
    sprintf(ptr,"solve0%d",no);
  }
  else {
    sprintf(ptr,"solve%d",no);
  }
  return(ptr);
}

//char *PM_feelP2::GetElemRoutineName( int solveNo, int elemNo )
//{
//  int length = stringLength("elem?_?");
//  if(solveNo > 9) {
//    length++;
//    if(solveNo >99) {
//      std::cerr <<"solve number too large(GetElemRoutineName)\n";
//      abortExit(1);
//    }
//  }
//
//  if(elemNo > 9){
//    length++;
//    if(elemNo >99) {
//      std::cerr <<"elem number too large(GetElemRoutineName)\n";
//      abortExit(1);
//    }
//  }
//
//  char *ptr = new char[length];
//
//  sprintf(ptr,"elem%d_%d",solveNo,elemNo);
//
//  return(ptr);
//}
//////////////////////////////////////////////////////////////////
void PM_feelP2::pushSolveRoutineName( int no )
{
  const char *ptr;

  ptr = GetSolveRoutineName( no );
  pushSource(ptr);
  delete ptr;
}

void PM_feelP2::pushElemRoutineName(int solveNo, int elemNo)
{
  const char *ptr;
  ptr = GetElemRoutineName(solveNo,elemNo);
  pushSource(ptr);
  delete ptr;

  return;
}

void PM_feelP2::pushNeumannRoutineName(int solveNo, int ncondNo)
{
  char buf[BUFSIZ];
  sprintf(buf,"ncond%d_%d",solveNo,ncondNo);
  pushSource(buf);

  return;
}

void PM_feelP2::pushDirichletRoutineName(int solveNo, int dcondNo)
{
  char buf[BUFSIZ];
  sprintf(buf,"dcond%d_%d",solveNo,dcondNo);
  pushSource(buf);

  return;
}

void PM_feelP2::pushEdevRoutineName(int solveNo, int solveElementNo)
{
  char buf[BUFSIZ];
  sprintf(buf,"edev%d_%d",solveNo,solveElementNo);
  pushSource(buf);

  return;
}
  
/////////////////////////////////////////////////////////////////
// solve related component generators
/////////////////////////////////////////////////////////////////
void PM_feelP2::SourceStarters()
{
  copyright();
  commentPM();
  timestamp();

  fortImplicit();   // implicit real*8(a-h,o-z) for fortran77

  comment();
  
  return;
}
///////////////////////////////////////
// Do Solve functions
///////////////////////////////////////
void PM_feelP2::DoSolveStarters()
{
  SourceStarters();
  return;
}

void PM_feelP2::DoSolveParametersPM( Solve *solvePtr )
{
  DefaultParameterBlock();
  
  // Here problem depend parameter block generator
  // NEG is fixed
  writeSource("      parameter (NEG = 1)");   // FIXP2

  // NDC (number of Dirichlet conditions)
  pushSource ("      parameter (NDC = ");
  pushSourceInt( solvePtr->GetDconds() );
  pushSource (")"); flushSource();

  // NNC (number of Neumann conditions)
  pushSource ("      parameter (NNC = ");
  pushSourceInt( solvePtr->GetNconds() );
  pushSource (")"); flushSource();

  comment();
  return;
}
///////////////////////////////////////
//////
void PM_feelP2::
DoDeclareVariablesFromMainPM( orderedPtrList<Variable *>varPtrLst)
{
  // Variable definitions (Arguments in solve routine)

  // default Solve variable
  writeSource("      real*4 feel(*)");
  writeSource("      real*8 x(*),y(*)");
  com();

  // Argument Variable declaration
  ArgumentVariableDeclarationLst( varPtrLst );
  com();
 
  return;
}
//


void PM_feelP2::DoSolveVariableDefinitionsPM(Solve *solvePtr)
{
  comment();

  // Solve Varible declaration
  int dconds = solvePtr->GetDconds();
  int nconds = solvePtr->GetNconds();

  writeSource("      dimension np_ielem(NEG),np_matno(NEG)");
  writeSource("      dimension nedtno(NEG)");
  writeSource("      dimension nonode(NEG)");

  pushSource("      parameter (MAX_ELEMENT_NODES = ");   // 010127 version
  pushSourceInt(solvePtr->GetMaxnodes()); 
  pushSource(")");
  flushSource();

  writeSource("      dimension nenfre(MAX_ELEMENT_NODES,NEG)");

  if(dconds)writeSource("      dimension np_inset(NDC)");
  if(dconds)writeSource("      dimension nsetno(NDC)");
  if(nconds)writeSource("      dimension np_bielem(NNC)");
  if(nconds)writeSource("      dimension np_bmatno(NNC)");
  if(nconds)writeSource("      dimension nbedtno(NNC)");
  comment();

  writeSource("      common /feel_geo/ndim,npmax,ndomain,nedat,nnodeset,nnumdat,nip");
  writeSource("      common /feel_ctl/mode_ex,mode_output,max_heap");
  writeSource("      common /feel_var/np_x,np_y,np_z,nvars_fem,nvars_ewise,");
  writeSource("     &                 np_fem,np_ewise,np_heap");
  writeSource("      common /feel_fil/io_in,io_tmp,io_out,io_stderr,");
  writeSource("     &                 io_edat,io_node,io_num,io_fem");
  writeSource("      common /feel_dat/n_edat(MAX_EDATSET,3),");
  writeSource("     &                 n_nset(MAX_NODESET,2),n_num(MAX_NUMSET),");
  writeSource("     &                 n_ewise(MAX_EWISE,2),n_nodeno(MAX_IP)");
  writeSource("      common /feel_sol/n_sstat(MAX_SOLVE),n_smaxp(MAX_SOLVE)");
  comment();

  return;
}
///////////////////////////////////////
void PM_feelP2::DoSolveInitializerPM(Solve *solvePtr)
{
  int dconds = solvePtr->GetDconds();
  int nconds = solvePtr->GetNconds();
  
  SolveElement *sePtr = solvePtr->GetIthSolveElementPtr(0);  // 0 fix P2 limit
  Dirichlet    *dptr;
  Neumann      *nptr;

  // Data statement (Problem depenedent)
  pushSource("      data nedtno/");
  pushSourceInt(sePtr->GetEdatno());
  pushSource("/");
  flushSource();

  pushSource("      data nonode/0/");
  flushSource();

  pushSource("      data nenfre/");
  for(int i=0;i<solvePtr->GetMaxnodes();i++) {//maxnodes should be nodes in SE
    if(i!=0) pushSource(",");
    pushSourceInt(sePtr->GetNenfre(i));
  }
  pushSource("/");
  flushSource();
  
  if(dconds) {
    pushSource("      data nsetno/");
    for(int i=0;i<dconds;i++) {
      if(i!=0) pushSource(",");
      pushSourceInt(solvePtr->GetIthDirichletNsetno(i));
    }
    pushSource("/");
    flushSource();
  }
  
  if(nconds) {
    pushSource("      data nbedtno/");
    for(int i=0;i<nconds;i++) {
      if(i!=0) pushSource(",");
      pushSourceInt(solvePtr->GetIthNeumannNbedtno(i));
    }
    pushSource("/");
    flushSource();
  }

  comment();

  //  report routine
  pushSource("      call report('SOLVE ");
  pushSourceInt(solvePtr->GetSolveNo());
  pushSource(" START')");
  flushSource();
  
  //  NO = [solve no]
  pushSource("      NO = ");
  pushSourceInt(solvePtr->GetSolveNo());
  flushSource();
  
  //
  //  writeSrouce("      np_push = np_work");   010127 version modified
  writeSource("      call f_alloc_push");
  com();
  
  //
  writeSource("      if( n_sstat(NO) .ne. 0) then");
  writeSource("      stop 'Not implemented now'");
  writeSource("      endif");
  comment();
  
  return;
}
////////////////////////////////////////////////////////////////////
void PM_feelP2::DoSolveDegreeOfFreedom(Solve *solvePtr)
{

  COMMENTlong("IPD (node-wise equation number)");
  MODULEmalloc("np_IPD","(IPD)","npmax","0");

  COMMENTlong("IPF (node-wise freedom)");
  MODULEmalloc("np_IPF","(IPF)","npmax","0");

  MODULEzeroclearI("feel(np_IPD)","npmax");
  MODULEzeroclearI("feel(np_IPF)","npmax");

  COMMENTlong("IELEM,MATNO (element-node array,materinal array)");

  writeSource("      do 10 i=1,NEG");
  writeSource("        neelem = n_edat(nedtno(i),1)");
  writeSource("        nenode = n_edat(nedtno(i),2)");

  MODULEmalloc("np_ielem(i)","(ielem)","neelem*nenode","0");
  MODULEmalloc("np_matno(i)","(matno)","neelem" ,"0");

  writeSource("        iunit = nedtno(i) + io_edat - 1");
  writeSource("        call get_ielem(iunit,feel(np_ielem(i)),feel(np_matno(i)),");
  writeSource("     $                 neelem,nenode)");
  writeSource("   10 continue");
  comment();


  writeSource("      do 100 i=1,NEG");
  writeSource("*");
  writeSource("        call ipf_nfree(n_edat(nedtno(i),1),n_edat(nedtno(i),2),");
  writeSource("     $                 feel(np_IPF),feel(np_ielem(i)),nenfre(1,i))");
  writeSource("*");
  writeSource("  100 continue");
  comment();

  writeSource("      do 200 i=1,NEG");
  writeSource("        if(nonode(i) .eq. 0) goto 200");
  writeSource("*");
  writeSource("        call ipd_nonode(n_edat(nedtno(i),1),n_edat(nedtno(i),2),");
  writeSource("     $                  nonode(i),feel(np_ipd),feel(np_ielem(i)))");
  writeSource("*");
  writeSource("  200 continue");
  comment();

  writeSource("      call makeipd(feel(np_ipf),feel(np_ipd),npmax,neq)  ");
  comment();

  return;
  
}

void PM_feelP2::DoSolveAssemblyPreparation(Solve *solvePtr)
{
  // do nothing   2000:03/28
  return;
}

void PM_feelP2::GenerateCoSolveRoutines(Solve *solvePtr)
{
  // no co-solve routine for feelP2 version 2000/03/28
  return;
}


void PM_feelP2::DoSolveBoundaryDataPreparation(Solve *solvePtr)
{
  /* Neumann data preparation */
  
  if(solvePtr->GetNconds() != 0) {
    COMMENTlong("Neumann data preparation");
    writeSource("      do 15 i=1,NNC");
    writeSource("        neelem = n_edat(nbedtno(i),1)");
    writeSource("        nenode = n_edat(nbedtno(i),2)");
    MODULEmalloc("np_bielem(i)","(bielem)","neelem*nenode","0");
    MODULEmalloc("np_bmatno(i)","(bmatno)","neelem","0");
    writeSource("        iunit = nbedtno(i) + io_edat - 1");
    writeSource("        call get_ielem(iunit ,feel(np_bielem(i)),feel(np_bmatno(i)),");
    writeSource("     $                 neelem,nenode)");
    writeSource("   15 continue");
    comment();
  }
  else {
    COMMENTlong("No need for Neumann data preparation (do 15 loop)");
  }
  
  /* Dirichlet data preparation */
  if(solvePtr->GetDconds() != 0) {
    COMMENTlong("Dirichlet data preparation");
    writeSource("      do 20 i=1,NDC");
    writeSource("      nodes = n_nset(nsetno(i),1)");
    writeSource("      np    = n_nset(nsetno(i),2)");
    MODULEmalloc("np_inset(i)","(inset)","nodes*np","0");
    writeSource("      iunit=nsetno(i)+io_node-1");
    writeSource("      call get_inset(iunit,feel(np_inset(i)),nodes,np)");
    writeSource(" 20   continue");
    comment();
  }
  else {
    COMMENTlong("No need for Dirichlet data preparation (do 20 loop)");
  }
  return;
}



  ///////////////////////////////////////
void PM_feelP2::DoSolveReturnSequence(Solve *solvePtr)
{
  writeSource("      return");
  writeSource("      end");
  return;
}

/////////////////////////////////////////////////////////////////
// elem related component generators
/////////////////////////////////////////////////////////////////
void PM_feelP2::doElemStarters()
{
  SourceStarters();
  return;
}

void PM_feelP2::DoElemParameters(SolveElement *sePtr)
{
  pushSource("      parameter (NDF = ");
  pushSourceInt(sePtr->GetNdf());
  pushSource(")");
  flushSource();
  comment();

  for(int i=0;i<sePtr->GetQuadratures();i++) {

    Quadrature *qPtr;
    qPtr = sePtr->GetIthQuadraturePtr(i);

    pushSource("* No.");
    pushSourceInt(i+1);
    pushSource(" Numerical integration method[");
    pushSource(qPtr->GetName());
    pushSource("]");
    flushSource();

    pushSource("       parameter (NPG");
    pushSourceInt(i+1);
    pushSource(" =  ");
    pushSourceInt(qPtr->GetQuadraturePoints());
    pushSource(")");
    flushSource();
  }
  comment();
  return;

}

// elem routines

void PM_feelP2::doElemDeclareArgumentVariablesPM(SolveElement *sePtr)
{
  com();
  writeSource("      dimension x(*),y(*)");
  writeSource("      dimension ielem(np,nelem)");
  writeSource("      dimension IPD(*)");
  
  orderedPtrList <Variable *> varPtrLst = sePtr->GetVariablePtrLst();
  ArgumentVariableDeclarationLst(varPtrLst);
  
}

void PM_feelP2::DoElemVariableDefinitionsPM(SolveElement *sePtr)
{
  
  writeSource("      dimension ienp(NDF)");
  writeSource("      dimension iedp(NDF)");
  writeSource("      dimension ikp(NDF)");

  comment();

  pushSource("      common /em");
  pushSourceInt(sePtr->GetSolveNo());
  pushSource("_");
  pushSourceInt(sePtr->GetElemNo());
  pushSource("/ ea(NDF,NDF),eb(NDF)");
  flushSource();
  comment();

  return;
}

void PM_feelP2::DoElemInitializer(SolveElement *sePtr)
{
  /* data statement for ienp */
  pushSource("      data ienp/");
  for(int i=0;i<sePtr->GetNdf();i++) {
    if(i!=0) pushSource(",");
    pushSourceInt(sePtr->GetIthIENP(i));
  }
  pushSource("/");
  flushSource();

  /* data statement for iedp */
  pushSource("      data iedp/");
  for(int i=0;i<sePtr->GetNdf();i++) {
    if(i!=0) pushSource(",");
    pushSourceInt(sePtr->GetIthIEDP(i));
  }
  pushSource("/");
  flushSource();

  comment();

  for(int i=0;i<sePtr->GetQuadratures();i++) {
    pushSource("      call eset");
    pushSourceInt(sePtr->GetSolveNo());
    pushSource("_");
    pushSourceInt(sePtr->GetElemNo());
    pushSource("_");
    pushSourceInt(i+1);
    flushSource();
  }
  comment();

  return;
}

  
void PM_feelP2::DoElemElementLoopStart(int flag)
{
  writeSource("      do 100 i=1,nelem");         // just this!  ^^;
  return; 
}

void PM_feelP2::DoElemCallEcalRoutine(SolveElement *sePtr,int flag)
{
  pushSource("      call ecal");
  pushSourceInt(sePtr->GetSolveNo());
  pushSource("_");
  pushSourceInt(sePtr->GetElemNo());
  pushSource("(");

  int ielemNodes = sePtr->GetIelemNodes();
  for(int i=0;i<ielemNodes;i++) {
    if(i != 0) pushSource(",");
    pushSource("x(ielem(");
    pushSourceInt(i+1);
    pushSource(",i)),");

    pushSource("y(ielem(");
    pushSourceInt(i+1);
    pushSource(",i))");
  }

  list<string> strLst = sePtr->GetEcalCallValueLst();
  listIterator <string>itr(strLst);
  
  for(itr.init();!itr;++itr) {
    pushSource(",");
    string a = itr();
    pushSource(a);
  }

  pushSource(")");
  flushSource();

  comment();

  writeSource("      do 200 j=1,NDF");
  writeSource("        ikp(j)=IPD(ielem(ienp(j),i))+iedp(j)");
  writeSource(" 200  continue");
  comment();

  return;
}

void PM_feelP2::DoElemElementLoopEnd(int flag)
{
  writeSource(" 100  continue");
  comment();
  return;
}

void PM_feelP2::DoElemReturnSequence(SolveElement *sePtr)
{
  writeSource("      return");
  writeSource("      end");

  return;
}
//////////////////////////////////////////
// Dirichlet Conditions related functions
//////////////////////////////////////////
char *PM_feelP2::GetDirichletRoutineName(int solveNo, int dcondNo)
{
  int length = stringLength("dcond?_?");
  if(solveNo > 9) {
    length++;
    if(solveNo >99) {
      std::cerr <<"solve number too large(GetDirichletRoutineName)\n";
      abortExit(1);
    }
  }

  if(dcondNo > 9){
    length++;
    if(dcondNo >99) {
      std::cerr <<"dcond number too large(GetDirichletRoutineName)\n";
      abortExit(1);
    }
  }

  char *ptr = new char[length];

  sprintf(ptr,"dcond%d_%d",solveNo,dcondNo);    // PMDependent

  return(ptr);
}


void PM_feelP2::DoDirichletArgumentVariableDefinitionsPM(Dirichlet *dPtr)
{
  com();
  writeSource("      dimension x(*),y(*)");
  writeSource("      dimension IPD(*)");
  writeSource("      dimension inset(2,nd)");
  
  orderedPtrList <Variable *> varPtrLst = dPtr->GetVariablePtrLst();
  ArgumentVariableDeclarationLst(varPtrLst);
  
  comment();

  return;
}

void PM_feelP2::doDirichletAutoVariableDefinitionsPM(Dirichlet *dPtr)
{
  // donothing now
  doNothingNow("void PM_feelP2::DoDirichletAutoVariableDefinitionsPM(Dirichlet *dPtr)");
  return;
}


void PM_feelP2::DoDirichletReturnSequencePM(Dirichlet *dPtr)
{
  writeSource("      return");
  writeSource("      end");

  return;
}




//////////////////////////////////////////
// Neumann Conditions related functions
//////////////////////////////////////////
char *PM_feelP2::GetNeumannRoutineName(int solveNo, int ncondNo)
{
  int length = stringLength("ncond?_?");
  if(solveNo > 9) {
    length++;
    if(solveNo >99) {
      std::cerr <<"solve number too large(GetNeumannRoutineName)\n";
      abortExit(1);
    }
  }

  if(ncondNo > 9){
    length++;
    if(ncondNo >99) {
      std::cerr <<"ncond number too large(GetNeumannRoutineName)\n";
      abortExit(1);
    }
  }

  char *ptr = new char[length];

  sprintf(ptr,"ncond%d_%d",solveNo,ncondNo);    // PMDependent

  return(ptr);
}


void PM_feelP2::DoNeumannParametersPM(Neumann *nPtr)
{
  /* parameter NPG */
  int oimo = nPtr->GetNPG();
  std::cout << "NPG(oimo)=" << oimo << "\n";
  nPtr->check();
  
  pushSource("      parameter (NPG = ");
  pushSourceInt(nPtr->GetNPG());
  pushSource(")");
  flushSource();

  /* parameter NDF */
  pushSource("      parameter (NDF = ");
  pushSourceInt(nPtr->GetNDF());
  pushSource(")");
  flushSource();

  com();

  return;
}



void PM_feelP2::DoNeumannArgumentVariableDefinitionsPM(Neumann *nPtr)
{
  com();
  writeSource("      dimension x(*),y(*)");
  writeSource("      dimension IPD(*)");
  writeSource("      dimension ielem(nenode,neelem)");
  writeSource("      dimension matno(*)");
  
  orderedPtrList <Variable *> varPtrLst = nPtr->GetVariablePtrLst();
  ArgumentVariableDeclarationLst(varPtrLst);
  
  com();
  
  return;
}


void PM_feelP2::DoNeumannAutoVariableDefinitionsPM(Neumann *nPtr)
{
  /* variables defined in ncond routine */
  
  writeSource("      dimension gx(NPG),w(NPG)");

  list <char *> testQuadratureArrayLst = nPtr->GetQuadratureArrayLst();
  listIterator <char *> itr(testQuadratureArrayLst);
  
  for(itr.init();!itr;++itr) {
    pushSource("      dimension ");
    pushSource(itr());
    pushSource("(NPG)");
    flushSource();
  }
  com();
  
  /* ba,bb related */
  if(nPtr->GetMatNonZero() != 0) {
    writeSource("      dimension ba (NDF,NDF)");
  }
  writeSource("      dimension bb (NDF)");
  writeSource("      dimension ikp(NDF)");
  com();

  /* ienp,iedp */
  writeSource("      dimension ienp(NDF)");
  writeSource("      dimension iedp(NDF)");
  com();

  int commaflag;

  list <int> testIENPLst = nPtr->GetIENPLst();
  listIterator <int> itr2(testIENPLst);
  commaflag = 0;
  pushSource("      data ienp/");
  for(itr2.init(); !itr2; ++itr2 ) {
    if(commaflag) pushSource(",");
    pushSourceInt(itr2());
    commaflag = 1;
  }
  pushSource("/");
  flushSource();

  list <int> testIEDPLst = nPtr->GetIEDPLst();
  listIterator <int> itr3(testIEDPLst);
  commaflag = 0;
  pushSource("      data iedp/");
  for(itr3.init(); !itr3; ++itr3 ) {
    if(commaflag) pushSource(",");
    pushSourceInt(itr3());
    commaflag = 1;
  }
  pushSource("/");
  flushSource();
    
  comment();
  
  return;

}


void PM_feelP2::DoNeumannInitializerPM(Neumann *nPtr)
{
  int no;

  list <char *> testGXArrayLst = nPtr->GetGXArrayLst();
  list <char *> testWArrayLst  = nPtr->GetWArrayLst();

  listIterator <char *> itr1(testGXArrayLst);
  listIterator <char *> itr2(testWArrayLst );

  no = 0;
  for(itr1.init(); !itr1; ++itr1) {
    no++;
    pushSource("      gx(");
    pushSourceInt(no);
    pushSource(") = ");
    pushSource(itr1());
    flushSource();
  }

  no = 0;
  for(itr2.init(); !itr2; ++itr2) {
    no++;
    pushSource("       w(");
    pushSourceInt(no);
    pushSource(") = ");
    pushSource(itr2());
    flushSource();
  }
  com();

  /* */
  
  pushSource("      S = ");
  pushSource(nPtr->GetSValue());
  flushSource();
  com();

  /* */
  writeSource("      do 100 i=1,NPG");
  writeSource("       R=gx(i)");

  list <char *>testTermsLeftLst  = nPtr->GetTermsLeftLst();
  list <char *>testTermsRightLst = nPtr->GetTermsRightLst();

  listIterator <char *>itr3(testTermsLeftLst );
  listIterator <char *>itr4(testTermsRightLst);

  com();
  for(itr3.init(),itr4.init(); !itr3; ++itr3,++itr4) {
    pushSource("        ");
    pushSource(itr3());      // this contains (i) in Read77
    pushSource("=");
    pushSource(itr4());
    flushSource();
  }
  com();

  writeSource("  100 continue");
  com();

  return;
}


void PM_feelP2::DoNeumannBoundaryElementLoopStartPM(Neumann *nPtr)
{
  int streq(const char *, const char *);
  int testBoundaryPoints = nPtr->GetBoundaryPoints();
  writeSource("      do 200 i=1,neelem");
  com();

  for(int i=0;i<testBoundaryPoints;i++) {
    pushSource("        x");
    pushSourceInt(i+1);
    pushSource(" = x(ielem(");
    pushSourceInt(i+1);
    pushSource(",i))");
    flushSource();

    pushSource("        y");
    pushSourceInt(i+1);
    pushSource(" = y(ielem(");
    pushSourceInt(i+1);
    pushSource(",i))");
    flushSource();
  }
  com();


  /* FEM vars in boundary */
  list <char *>testFemVarsFormulaLeftLst = nPtr->GetFemVarsFormulaLeftLst();
  list <char *>testFemVarsFormulaRightLst = nPtr->GetFemVarsFormulaRightLst();

  listIterator <char *>itrfl(testFemVarsFormulaLeftLst );
  listIterator <char *>itrfr(testFemVarsFormulaRightLst);
  for(itrfl.init(),itrfr.init(); !itrfl; ++itrfl,++itrfr) {
    pushSource("      ");
    pushSource(itrfl());
    pushSource("=");
    pushSource(itrfr());
    flushSource();
  }
  com();

  
  if(nPtr->GetMatNonZero() != 0) {
    writeSource("      do 210 j=1,NDF");
    writeSource("       do 220 k=1,NDF");
    writeSource("        ba(j,k)=0.0d0");
    writeSource(" 220   continue");
    writeSource(" 210  continue");   
    com();
  }

  writeSource("        do 230 j=1,NDF");
  writeSource("         bb(j) = 0.0d0");
  writeSource(" 230    continue");
  com();

  /**/
  writeSource("      do 300 itp =1,NPG");
  com();

  pushSource("       dx=");
  pushSource(nPtr->GetDxFormula());
  flushSource();

  pushSource("       dy=");
  pushSource(nPtr->GetDyFormula());
  flushSource();
  com();

  writeSource(" not complete here feelP2.cpp (1189)");
  //  if(nPtr->GetQxFlag()) {
  //    pushSource("       qx=");
  //    pushSource(nPtr->GetQxFormula());
  //    flushSource();
  //  }

  //  if(nPtr->GetQyFlag()) {
  //    pushSource("       qy=");
  //    pushSource(nPtr->GetQyFormula());
  //    flushSource();
  //  }

  writeSource(" P2 PRGORAM FOR QY is not complete");
  com();

  writeSource("       ds=sqrt(dx*dx+dy*dy)*w(itp)");
  com();

  
  if(nPtr->GetMatNonZero() != 0) {

    writeSource("P2 program generation not complete in feelP2.cpp");
    //    list <int>testBaILst = nPtr->GetBaILst();
    //    list <int>testBaJLst = nPtr->GetBaJLst();
    //    list <char *>testBaFormulaLst = nPtr->GetBaFormulaLst();
    //
    //    listIterator <int>itrI(testBaILst);
    //    listIterator <int>itrJ(testBaJLst);
    //    listIterator <char *>itrFormula(testBaFormulaLst);

    //    for(itrI.init(),itrJ.init(),itrFormula.init();
    //	!itrI;
    //	++itrI,++itrJ,++itrFormula) {
    //      if(streq("0.0d0",itrFormula())) continue;

    //      pushSource("        ba(");
    //      pushSourceInt(itrI());
    //      pushSource(",");
    //      pushSourceInt(itrJ());
    //      pushSource(")=ba(");
    //      pushSourceInt(itrI());
    //      pushSource(",");
    //      pushSourceInt(itrJ());
    //      pushSource(")+(");
    //      pushSource(itrFormula());
    //      pushSource(")*ds");
    //      flushSource();
    //    }
  }
  com();



//  list <char *>testBbFormulaLst = nPtr->GetBbFormulaLst();
//  listIterator<char *>itrBFormula(testBbFormulaLst);
//    
//  int i;
//  i= 0;
//  for(itrBFormula.init(); !itrBFormula; ++itrBFormula,++i) {
//
//    if(streq("0.0d0",itrBFormula())) continue;
//
//    pushSource("        bb(");
//    pushSourceInt(i+1);
//    pushSource(")=bb(");
//    pushSourceInt(i+1);
//    pushSource(")+(");
//    pushSource(itrBFormula());
//    pushSource(")*ds");
//    flushSource();
//  }
//  com();

  /**/
  writeSource(" 300  continue");
  com();

  /**/  
  writeSource("      do 400 j=1,NDF");
  writeSource("       ikp(j)=IPD(ielem(ienp(j),i))+iedp(j)");
  writeSource(" 400  continue");
  com();

  return;
}
    
void PM_feelP2::DoNeumannBoundaryElementLoopEndPM(Neumann *nPtr)
{
  writeSource(" 200  continue");
  com();
  return;
}


void PM_feelP2::DoNeumannReturnSequencePM(Neumann *nPtr)
{
  writeSource("      return");
  writeSource("      end");

  return;
}

// END OF NEUMANN RELATED FUNCTIONS


  











