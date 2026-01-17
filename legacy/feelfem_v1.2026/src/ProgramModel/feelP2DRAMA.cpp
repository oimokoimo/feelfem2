/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : feelP2DRAMA.cpp
 *  Date     : 2000/03/20
 *  Modified : 2000/03/20
 *  Modified : 2001/01/31  LINKLEVEL added
 *  Modified : 2001/02/02 orderedPtrList
 *  
 *  Purpose  : feelP2 programming style implementation 
 *             DRAMA double index parallel version
 */

#include "feeldef.hpp"
#include "feelfuncs.hpp"
#include "feelfem.hpp"

#include "Quadrature.hpp"
#include "Dirichlet.hpp"
#include "Neumann.hpp"
#include "PM_feelP2DRAMA.hpp"

#include "MT_P2CRSLOC.hpp"
#include "ElemGeneratorTemplate.hpp"


PM_feelP2DRAMA::PM_feelP2DRAMA()
{
  return;
}

PM_feelP2DRAMA::~PM_feelP2DRAMA()
{
  return;
}
//////////////////////////////////////////////////////////////////
void PM_feelP2DRAMA::OpenSource(char *filename)
{
  startSource( filename );
  Fortran77GeneratorSetFP( GetSourceFP() );
  return;
}

void PM_feelP2DRAMA::OpenSource(char *filename, int makeFlag)
{
  startSource( filename ,makeFlag);
  Fortran77GeneratorSetFP( GetSourceFP() );
  return;
}

void PM_feelP2DRAMA::CloseSource()
{
  endSource(  );
  Fortran77GeneratorSetFP( NULL );
  return;
}

//////////////////////////////////////////////////////////////////
void PM_feelP2DRAMA::commentPM()
{
  writeSource("* FEEL P2/DRAMA Program Model");
  return;
}

/////////////////////////////////////////////////////////////////
//  General File handling functions
/////////////////////////////////////////////////////////////////

char *PM_feelP2DRAMA::GetSourceName( char *routineName)
{
  int   len = stringLength(routineName)+3;
  char *ptr = new char[len];
  
  sprintf(ptr,"%s.f",routineName);
  return(ptr);
}

/////////////////////////////////////////////////////////////////
//  General Process function in Program Model feelP2DRAMA
/////////////////////////////////////////////////////////////////

void PM_feelP2DRAMA::MODULEzeroclearD(char *varname, char *size)
{
  char buf[BUFSIZ];

  sprintf(buf,"      call zerod(%s,%s)",varname,size);
  writeSource(buf);
  
  return;
}

void PM_feelP2DRAMA::MODULEzeroclearI(char *varname, char *size)
{
  char buf[BUFSIZ];

  sprintf(buf,"      call zeroi(%s,%s)",varname,size);
  writeSource(buf);
  
  return;
}

void PM_feelP2DRAMA::MODULEmalloc(char *ptr,char *comment,char *size, char *type)
{
  mallocF77(ptr,comment,size,type);
  return;
}

void PM_feelP2DRAMA::MODULEmallocERT(char *ptr,char *comment,char *size, char *type)
{
  mallocF77imode(ptr,comment,size,type);
  return;
}

void PM_feelP2DRAMA::MODULEmallocCHK()
{
  mallocF77check();
  com();
  
  return;
}

/////////////////////////////////////////////////////////////////
//  Generator components for Problem Model feelP2
/////////////////////////////////////////////////////////////////
void PM_feelP2DRAMA::pushVariableNameInMain( Variable *valPtr)
{
  char buf[BUFSIZ];
  switch(valPtr->GetType()) {
  case VAR_FEM:
    sprintf(buf,"feel(npf_%s)",valPtr->GetName());
    break;
    
  case VAR_EWISE:
  case VAR_EWISE_A:
    sprintf(buf,"feel(npe_%s)",valPtr->GetName());
    break;
    
  case VAR_DOUBLE:
  case VAR_INT:
    sprintf(buf,"sc_%s",valPtr->GetName());
    break;
    
  case VAR_CONST:
    sprintf(buf,"co_%s",valPtr->GetName());
    break;

  case VAR_MATERIAL:
    sprintf(buf,"m_%s",valPtr->GetName());
    break;
    
  default:
    assert(1==0);
  }
  
  pushSource(buf);
  return;
}


void PM_feelP2DRAMA::NameVariableInCalled( Variable *valPtr, string &name)
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

void PM_feelP2DRAMA::pushVariableListInCalled( orderedPtrList <Variable *> varPtrLst)
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

void PM_feelP2DRAMA::pushVariableListInCalled( list <Variable *> varPtrLst)
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

/* Add 2000/05/09  (now only in feelP2DRAMA) */
void PM_feelP2DRAMA::pushFEMVariableInCalled( Variable *varPtr)
{
  pushSource("fem_");
  pushSource(varPtr->GetName());
  return;
}

/* External FEM variable  2000/05/09 */
void PM_feelP2DRAMA::pushFEMVariableExternalInCalled( Variable *varPtr)
{
  pushSource("femex_");
  pushSource(varPtr->GetName());
  return;
}

void PM_feelP2DRAMA::pushFEMVariableExternalInSolve( Variable *varPtr) 
{
  pushSource("feel(npfex_");
  pushSource(varPtr->GetName());
  pushSource(")");

  return;
}



///////////////////////////////////////////////////////////
void PM_feelP2DRAMA::DefaultParameterBlock()
{
  writeSource("      parameter (MAX_PROCS   = 256)");
  writeSource("      parameter (NBYTE_REAL8 =   2)");
  writeSource("      parameter (NCTRL_ITEMS =   4)");

  com();
 
  comment();
}


void PM_feelP2DRAMA::PopReturn()                     // General in PM
{
  writeSource("      call f_alloc_pop");
  writeSource("      return");
  writeSource("      end");
  return;
}


void PM_feelP2DRAMA::DoSolveReport( int no, const char *s)
{
  writeSource("      if(myrank .EQ. 0) then");
  pushSource("      call preport('solve");
  pushSourceInt(no);
  pushSource(" : ");
  pushSource(s);
  pushSource("')");
  flushSource();
  writeSource("      endif");
  
  return;
}
    

/////////////////////////////////////////////////////////////////
// General components for generating subroutines
/////////////////////////////////////////////////////////////////

void PM_feelP2DRAMA::DoArgumentSequenceFromMain
( char                         *subroutineName,
  orderedPtrList <Variable *>&varPtrLst       )
{
  char buf[BUFSIZ];
  sprintf(buf,"      subroutine %s(feel,myrank,nprocs,ndim,"
	  ,subroutineName);
  writeSource(buf);
  writeSource("     $   npmax,x,y,");
  writeSource("     $   redatinfo,enptrlst,matnolst,conlst,");
  writeSource("     $   nbedat,nbnset, inbctr2,idbctr2");
  
  pushSource("     &");

  pushVariableListInCalled( varPtrLst);
  pushSource(")");
  flushSource();
  
  return;
}

/////////////////////////////////////////////////////////////////////////////
void PM_feelP2DRAMA::ArgumentVariableDeclaration(Variable *varPtr)
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
  case VAR_EWISE_A:                          // P2 FIX
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
void PM_feelP2DRAMA::ArgumentVariableDeclarationLst(list <Variable *>& varPtrLst)
{
  listIterator <Variable *> itr(varPtrLst);
  for(itr.init(); !itr;++itr) {
    ArgumentVariableDeclaration(itr());
  }  
  
  return;
}



/////////////////////////////////////////////////////////////////
// Routine name for feelP2 DRAMA program model
// Get  Routine name series  [Definition of routine names]
// push Routine name series  [Writing source file routine names]
/////////////////////////////////////////////////////////////////
char *PM_feelP2DRAMA::GetSolveRoutineName( int no )
{
  char *ptr = new char[8];

  if(no >99) { cerr <<"Too large solve Number\n"; abortExit(1); }
  sprintf(ptr,"solve%d",no);

  return(ptr);
}

char *PM_feelP2DRAMA::GetElemRoutineName( int solveNo )
{
  int length = stringLength("elem?");
  if(solveNo > 9) {
    length++;
    if(solveNo >99) {
      cerr <<"solve number too large(GetElemRoutineName)\n";
      abortExit(1);
    }
  }

  char *ptr = new char[length];

  sprintf(ptr,"elem%d",solveNo);

  return(ptr);
}
//////////////////////////////////////////////////////////////////
void PM_feelP2DRAMA::pushSolveRoutineName( int no )
{
  char *ptr;

  ptr = GetSolveRoutineName( no );
  pushSource(ptr);
  delete ptr;
}

void PM_feelP2DRAMA::pushElemRoutineName(int solveNo)
{
  char *ptr;
  ptr = GetElemRoutineName(solveNo);
  pushSource(ptr);
  delete ptr;

  return;
}

void PM_feelP2DRAMA::pushNeumannRoutineName(int solveNo, int ncondNo)
{
  char buf[BUFSIZ];
  sprintf(buf,"ncond%d_%d",solveNo,ncondNo);
  pushSource(buf);

  return;
}

void PM_feelP2DRAMA::pushDirichletRoutineName(int solveNo, int dcondNo)
{
  char buf[BUFSIZ];
  sprintf(buf,"dcond%d_%d",solveNo,dcondNo);
  pushSource(buf);

  return;
}

void PM_feelP2DRAMA::pushEdevRoutineName(int solveNo, int solveElementNo)
{
  char buf[BUFSIZ];
  sprintf(buf,"edev%d_%d",solveNo,solveElementNo);
  pushSource(buf);

  return;
}

void PM_feelP2DRAMA::MPIinclude(void)
{
  writeSource("      include 'mpif.h'");
  return;
}

/////////////////////////////////////////////////////////////////
// solve related component generators
/////////////////////////////////////////////////////////////////
void PM_feelP2DRAMA::SourceStarters()
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
void PM_feelP2DRAMA::DoSolveStarters()
{
  SourceStarters();
  MPIinclude();
  return;
}

void PM_feelP2DRAMA::DoSolveParametersPM( Solve *solvePtr )
{
  DefaultParameterBlock();

  // for P2 NEG is fixed
  writeSource("      parameter (NEG = 1)");   // FIXP2

  // MAX_ELEMENT_NODES
  pushSource ("      parameter (MAX_ELEMENT_NODES=");
  pushSourceInt(solvePtr->GetMaxnodes());
  pushSource (")");
  flushSource();

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
void PM_feelP2DRAMA::
DoDeclareVariablesFromMainPM( orderedPtrList<Variable *>varPtrLst)
{
  // Variable definitions (Arguments in solve routine)

  // default Solve variable
  writeSource("      real*4 feel(*)");
  com();

  writeSource("      real*8 x(*),y(*)");
  writeSource("      integer*4 myrank,nprocs,ndim");
  writeSource("      integer*4 npmax");
  com();

  // Argument Variable declaration
  ArgumentVariableDeclarationLst( varPtrLst );
  com();

  // Mesh information
  writeSource("      integer*4 redatinfo(3,*)");
  writeSource("      integer*4 enptrlst(*),conlst(*)");
  writeSource("      integer*4 matnolst(*)");
  writeSource("      integer*4 nbedat,nbnset");
  writeSource("      integer*4 inbctr2(5,*)");
  writeSource("      integer*4 idbctr2(5,*)");
  com();
 
  return;
}




void PM_feelP2DRAMA::DoSolveVariableDefinitionsPM(Solve *solvePtr)
{

  // enptr,con
  writeSource("      integer*4 edatno");

  // Solve Varible declaration
  int dconds = solvePtr->GetDconds();
  int nconds = solvePtr->GetNconds();
  
  writeSource("      dimension nenfre(MAX_ELEMENT_NODES,NEG)");

  if(dconds)writeSource("      dimension nsetno(NDC)");
  if(nconds)writeSource("      dimension nbedtno(NNC)");

  comment();

  return;
}
///////////////////////////////////////

void PM_feelP2DRAMA::DoSolveInitializerPM(Solve *solvePtr)
{
  int dconds = solvePtr->GetDconds();
  int nconds = solvePtr->GetNconds();
  
  SolveElement *sePtr = solvePtr->GetIthSolveElementPtr(0);  // 0 fix P2 limit
  Dirichlet    *dptr;
  Neumann      *nptr;

  // Data statement (Problem depenedent)

  /* EDATNO oimo P2 limited */
  pushSource("      data edatno/");
  pushSourceInt(sePtr->GetEdatno());
  pushSource("/");
  flushSource();


  pushSource("      data nenfre/");
  for(int i=0;i<solvePtr->GetMaxnodes();i++) { //maxnodes should be nodes in SE
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
  
  // check routine
  writeSource("      if(nprocs .GT. MAX_PROCS) then");
  writeSource("        call abortexit(myrank,'Too many nprocs in solve')");
  writeSource("      endif");
  com();

  writeSource("      call f_alloc_push");
  com();

  writeSource("      mypeid = myrank");
  writeSource("      mypeidx= myrank+1");
  com();

  /* edatnolst,matnolst,conlst */
  writeSource("      nelem = redatinfo(2,edatno)");
  writeSource("      if(redatinfo(1,edatno) .ne. edatno) call abortexit(myrank,'redatinfo ERR')");
  writeSource("      if(redatinfo(3,edatno) .NE. nelem*MAX_ELEMENT_NODES) then");
  writeSource("        call abortexit(myrank,'Mismatch redatinfo/MAX_ELEMENT_NODES')");
  writeSource("      endif");
  com();


  writeSource("      np_e = enptrlst(edatno)");
  writeSource("      np_m = matnolst(edatno)");
  writeSource("      np_c = conlst  (edatno)");
  com();

  //  report routine
  writeSource("      if(myrank.eq. 0) then");
  pushSource( "        call preport('SOLVE ");
  pushSourceInt(solvePtr->GetSolveNo());
  pushSource(" START')");
  flushSource();
  writeSource("      endif");
  
  return;
}
////////////////////////////////////////////////////////////////////
void PM_feelP2DRAMA::DoSolveDegreeOfFreedom(Solve *solvePtr)
{

  COMMENTlong("IPD (node-wise equation number::DRAMA double index)");
  MODULEmalloc("np_IPD","(IPD)","npmax","0");

  COMMENTlong("IPF (node-wise freedom)");
  MODULEmalloc("np_IPF","(IPF)","npmax","0");

  MODULEzeroclearI("feel(np_IPD)","npmax");
  MODULEzeroclearI("feel(np_IPF)","npmax");

  com();
  writeSource("      call makeipfex(mypeid,nenfre,MAX_ELEMENT_NODES,NEG,");
  writeSource("     $     feel(np_e),feel(np_c),nelem,npmax,feel(np_ipf))");
  writeSource("      ndfmax = MAX_ELEMENT_NODES");  // debug
  com();
  writeSource("      call makeipdex(feel(np_ipf),feel(np_ipd),npmax,neq)");
  

  return;
}

void PM_feelP2DRAMA::DoSolveAssemblyPreparation(Solve *solvePtr)
{
  // DRAMA-double index distributed matrix
  SubDoSolveMessageKnownFEMVars(solvePtr);
  SubDoSolveMakeExIelem();
  SubDoSolveMakeExNode(solvePtr);
  SubDoSolveMakeSumupDegree();
  return;
}


void PM_feelP2DRAMA::DoSolveBoundaryDataPreparation(Solve *solvePtr)
{
  /* Neumann data preparation */
  
  comment();
  writeSource("* Boundary Data is prepared before solve 1");
  writeSource("* in DRAMA MPI parallel version.");
  comment();

  return;
}



  ///////////////////////////////////////
void PM_feelP2DRAMA::DoSolveReturnSequence(Solve *solvePtr)
{
  PopReturn();
  return;
}

/////////////////////////////////////////////////////////////////
// elem related component generators
/////////////////////////////////////////////////////////////////
void PM_feelP2DRAMA::doElemStarters()
{
  SourceStarters();
  return;
}

void PM_feelP2DRAMA::DoElemParameters(SolveElement *sePtr)
{

  pushSource("      parameter (NDF = ");
  pushSourceInt(sePtr->GetNdf());
  pushSource(")");
  flushSource();

  pushSource("      parameter (NDP = ");
  pushSourceInt(sePtr->GetIelemNodes());
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

void PM_feelP2DRAMA::doElemDeclareArgumentVariablesPM(SolveElement *sePtr)
{
  writeSource("      integer*4 isumup(*)");
  writeSource("      integer*4 enptr(2,*),con(2,*)");
  writeSource("      real   *8 x(*),y(*)");
  writeSource("      integer*4 ipf(*),ipd(*)");
  orderedPtrList <Variable *> varPtrLst = sePtr->GetVariablePtrLst();
  ArgumentVariableDeclarationLst(varPtrLst);
  com();

  writeSource("      integer*4 enptr_ex(2,*),con_ex(2,*)");
  writeSource("      integer*4 ndno(*),peno(*)");
  writeSource("      integer*4 ipfex(*),ipdex(*)");
  writeSource("      real   *8 x_ex(*),y_ex(*)");
  com();
  
  listIterator <Variable *> itr(varPtrLst);
  for(itr.init(); !itr;++itr) {
    if(itr()->GetType() == VAR_FEM) {
      pushSource("      real   *8 femex_");
      pushSource(itr()->GetName());
      pushSource("(*)");
      flushSource();
    }
  }  
  com();
}


void PM_feelP2DRAMA::DoElemVariableDefinitionsPM(SolveElement *sePtr)
{
  int strindex(const char *, const char *);
  orderedPtrList <Variable *> varPtrLst = sePtr->GetVariablePtrLst();
  listIterator <Variable *> itr(varPtrLst);

  writeSource("      real   *8 ex(NDP),ey(NDP)");
  for(itr.init(); !itr;++itr) {
    if(itr()->GetType() == VAR_FEM) {
      pushSource("      real   *8 efem_");
      pushSource(itr()->GetName());
      pushSource("(NDP)");
      flushSource();
    }
  }  
  com();

  writeSource("      integer*4 ienp(NDF)");
  writeSource("      integer*4 iedp(NDF)");
  writeSource("      integer*4 ikp (NDF),jkp(NDF)");

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

void PM_feelP2DRAMA::DoElemInitializer(SolveElement *sePtr)
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

  
void PM_feelP2DRAMA::DoElemElementLoopStart(int flag)
{
  if(flag == MY_ELEMENT) {
    writeSource("      do 100 i=1,nelem");         // just this!  ^^;
  }
  else {
    comment();
    writeSource("* External enptr_ex loop");
    comment();
    writeSource("      do 200 i=1,nelem_ex");         // just this!  ^^;
  }
  return; 
}

void PM_feelP2DRAMA::DoElemCallEcalRoutine(SolveElement *sePtr,int flag)
{
  int strindex(const char *, const char *);
  orderedPtrList <Variable *> varPtrLst = sePtr->GetVariablePtrLst();
  listIterator <Variable *> itr(varPtrLst);

  if(flag == MY_ELEMENT) {
  
    writeSource("      ipos_from = enptr(1,i  )");
    writeSource("      ipos_to   = enptr(1,i+1)-1");
    writeSource("      ietype    = enptr(2,i  )");
    writeSource("      nodes     = ipos_to-ipos_from+1");
    com();
    writeSource("***** if(ietype .EQ. 1) then");  // P2 limit
    writeSource("        do 1011 j=1,nodes");
    writeSource("          jp=j-1+ipos_from");
    writeSource("          if(con(2,jp) .eq. mypeid) then");
    writeSource("           ex(j)=x(con(1,jp))");
    writeSource("           ey(j)=y(con(1,jp))");

    for(itr.init(); !itr;++itr) {
      if(itr()->GetType() == VAR_FEM) {
	pushSource("           efem_");
	pushSource(itr()->GetName());
	pushSource("(j)=fem_");
	pushSource(itr()->GetName());
	pushSource("(con(1,jp))");
	flushSource();
      }
    }  

    writeSource("          else");
    writeSource("           nd = ndsearch_ex(con(1,jp),");
    writeSource("     $                      con(2,jp),ndno,peno,nouter)");
    writeSource("           ex(j) = x_ex(nd)");
    writeSource("           ey(j) = y_ex(nd)");

    for(itr.init(); !itr;++itr) {
      if(itr()->GetType() == VAR_FEM) {
	pushSource("           efem_");
	pushSource(itr()->GetName());
	pushSource("(j)=femex_");
	pushSource(itr()->GetName());
	pushSource("(nd)");
	flushSource();
      }
    }  

    writeSource("          endif");
    writeSource(" 1011   continue");
    com();
    pushSource ("        call ecal");
    pushSourceInt(sePtr->GetSolveNo());
    pushSource("_");
    pushSourceInt(sePtr->GetElemNo());
    pushSource("(");

    int ielemNodes = sePtr->GetIelemNodes();
    for(int i=0;i<ielemNodes;i++) {
      if(i != 0) pushSource(",");
      pushSource("ex(");
      pushSourceInt(i+1);
      pushSource("),");

      pushSource("ey(");
      pushSourceInt(i+1);
      pushSource(")");
    }

    list<string> strLst = sePtr->GetEcalCallValueLst();
    listIterator <string>itr2(strLst);
  
    for(itr2.init();!itr2;++itr2) {
      pushSource(",");
      string a = itr2();
      if(strindex(a,"fem_")) { // SUPER LIMITED!!! ECAL P2 OIMO oimo
	a = SuperRinjiEcalP2DRAMA(a);
      }
      pushSource(a);
    }
    pushSource(")");
    flushSource();

    COMMENTlong("Make ikp(*),jkp(*)");

    writeSource("      do 1012 j=1,NDF");
    writeSource("       jp   = ienp(j)+ipos_from-1");
    writeSource("       ind  = con(1,jp)");
    writeSource("       ipe  = con(2,jp)");
    writeSource("       if(ipe .EQ. mypeid) then");
    writeSource("        ikp(j) = ipd(ind)+iedp(j)");
    writeSource("        jkp(j) = ikp(j)  +myeqfrom-1");
    writeSource("       else");
    writeSource("        nd = ndsearch_ex(ind,ipe,ndno,peno,nouter)");
    writeSource("        ikp(j) = 0");
    writeSource("        jkp(j) = ipdex(nd)+iedp(j)+isumup(ipe+1)");
    writeSource("       endif");
    writeSource("1012  continue");
  }  // end of MY_ELEMENT case
  else {
    // start of OTHER_ELEMENT case
  
    writeSource("      ipos_from = enptr_ex(1,i  )");
    writeSource("      ipos_to   = enptr_ex(1,i+1)-1");
    writeSource("      ietype    = enptr_ex(2,i  )");
    writeSource("      nodes     = ipos_to-ipos_from+1");
    com();
    writeSource("***** if(ietype .EQ. 1) then");  // P2 limit
    writeSource("        do 2011 j=1,nodes");
    writeSource("          jp=j-1+ipos_from");
    writeSource("          if(con_ex(2,jp) .eq. mypeid) then");
    writeSource("           ex(j)=x(con_ex(1,jp))");
    writeSource("           ey(j)=y(con_ex(1,jp))");

    for(itr.init(); !itr;++itr) {
      if(itr()->GetType() == VAR_FEM) {
	pushSource("           efem_");
	pushSource(itr()->GetName());
	pushSource("(j)=fem_");
	pushSource(itr()->GetName());
	pushSource("(con_ex(1,jp))");
	flushSource();
      }
    }  

    writeSource("          else");
    writeSource("           nd = ndsearch_ex(con_ex(1,jp),");
    writeSource("     $                      con_ex(2,jp),ndno,peno,nouter)");
    writeSource("           ex(j) = x_ex(nd)");
    writeSource("           ey(j) = y_ex(nd)");

    for(itr.init(); !itr;++itr) {
      if(itr()->GetType() == VAR_FEM) {
	pushSource("           efem_");
	pushSource(itr()->GetName());
	pushSource("(j)=femex_");
	pushSource(itr()->GetName());
	pushSource("(nd)");
	flushSource();
      }
    }  

    writeSource("          endif");
    writeSource(" 2011   continue");
    com();
    pushSource ("        call ecal");
    pushSourceInt(sePtr->GetSolveNo());
    pushSource("_");
    pushSourceInt(sePtr->GetElemNo());
    pushSource("(");

    int ielemNodes = sePtr->GetIelemNodes();
    for(int i=0;i<ielemNodes;i++) {
      if(i != 0) pushSource(",");
      pushSource("ex(");
      pushSourceInt(i+1);
      pushSource("),");

      pushSource("ey(");
      pushSourceInt(i+1);
      pushSource(")");
    }

    list<string> strLst = sePtr->GetEcalCallValueLst();
    listIterator <string>itr2(strLst);
  
    for(itr2.init();!itr2;++itr2) {
      pushSource(",");
      string a = itr2();
      if(strindex((char *)a,"fem_")) { // SUPER LIMITED!!! ECAL P2 OIMO oimo
	a = SuperRinjiEcalP2DRAMA(a);
      }
      pushSource(a);
    }
    pushSource(")");
    flushSource();

    COMMENTlong("Make ikp(*),jkp(*)");

    writeSource("      do 2012 j=1,NDF");
    writeSource("       jp   = ienp(j)+ipos_from-1");
    writeSource("       ind  = con_ex(1,jp)");
    writeSource("       ipe  = con_ex(2,jp)");
    writeSource("       if(ipe .EQ. mypeid) then");
    writeSource("        ikp(j) = ipd(ind)+iedp(j)");
    writeSource("        jkp(j) = ikp(j)  +myeqfrom-1");
    writeSource("       else");
    writeSource("        nd = ndsearch_ex(ind,ipe,ndno,peno,nouter)");
    writeSource("        ikp(j) = 0");
    writeSource("        jkp(j) = ipdex(nd)+iedp(j)+isumup(ipe+1)");
    writeSource("       endif");
    writeSource("2012  continue");
  }
  return;
}

void PM_feelP2DRAMA::DoElemElementLoopEnd(int flag)
{
  if(flag == MY_ELEMENT) {
    writeSource(" 100  continue");
    writeSource("*---           end of my enptr loop");
    comment();
  }
  else {
    writeSource(" 200  continue");
    writeSource("*---           end of external enptr loop");
    comment();
  }    
  return;
}

void PM_feelP2DRAMA::DoElemReturnSequence(SolveElement *sePtr)
{
  writeSource("      return");
  writeSource("      end");

  return;
}
//////////////////////////////////////////
// Dirichlet Conditions related functions
//////////////////////////////////////////
static char p2dotempbuf[BUFSIZ];
char *PM_feelP2DRAMA::dirichletP2DOTEMP( char *st )
{
  int strindex(const char *,const char *);
  int i;
  //  char buf[BUFSIZ];
  for(i=0;*st != '\0'; i++) {
    p2dotempbuf[i] = *st;
    st++;
  }
  p2dotempbuf[i] = '\0';
  
  int n;
  while( n = strindex(p2dotempbuf,"(ip)")) {
    p2dotempbuf[n-1] = '_';
    p2dotempbuf[n  ] = 'd';
    p2dotempbuf[n+1] = 'p';
    p2dotempbuf[n+2] = 't';
  }

  return(p2dotempbuf);
}

    

  

char *PM_feelP2DRAMA::GetDirichletRoutineName(int solveNo, int dcondNo)
{
  int length = stringLength("dcond?_?");
  if(solveNo > 9) {
    length++;
    if(solveNo >99) {
      cerr <<"solve number too large(GetDirichletRoutineName)\n";
      abortExit(1);
    }
  }

  if(dcondNo > 9){
    length++;
    if(dcondNo >99) {
      cerr <<"dcond number too large(GetDirichletRoutineName)\n";
      abortExit(1);
    }
  }

  char *ptr = new char[length];

  sprintf(ptr,"dcond%d_%d",solveNo,dcondNo);    // PMDependent

  return(ptr);
}


void PM_feelP2DRAMA::DoDirichletArgumentVariableDefinitionsPM(Dirichlet *dPtr)
{
  com();
  writeSource("      integer*4 dcon(2,*),dinfo(nsetnp,*)");
  com();
  writeSource("      integer*4 isumup(*)");
  writeSource("      integer*4 enptr(2,*),con(2,*)");
  writeSource("      real   *8 x(*),y(*)");
  writeSource("      integer*4 ipf(*),ipd(*)");
  com();
  writeSource("      integer*4 enptr_ex(2,*),con_ex(2,*)");
  writeSource("      integer*4 ndno(*),peno(*)");
  writeSource("      real   *8 x_ex(*),y_ex(*)");
  writeSource("      integer*4 ipfex(*),ipdex(*)");

  orderedPtrList <Variable *> varPtrLst = dPtr->GetVariablePtrLst();
  ArgumentVariableDeclarationLst(varPtrLst);

  // FEM variables for EX 
  listIterator <Variable *>itr(varPtrLst);
  for(itr.init(); !itr; ++itr ){
    if(itr()->GetType() != VAR_FEM) continue;

    pushSource("      real   *8 ");
    pushFEMVariableExternalInCalled(itr());
    pushSource("(*)");
    flushSource();
  }
  comment();

  return;
}

void PM_feelP2DRAMA::doDirichletAutoVariableDefinitionsPM(Dirichlet *dPtr)
{
  doNothingNow("void PM_feelP2DRAMA::DoDirichletAutoVariableDefinitionsPM(Dirichlet *dPtr)");

  return;
}


void PM_feelP2DRAMA::DoDirichletReturnSequencePM(Dirichlet *dPtr)
{
  writeSource("      return");
  writeSource("      end");

  return;
}




//////////////////////////////////////////
// Neumann Conditions related functions
//////////////////////////////////////////
char *PM_feelP2DRAMA::GetNeumannRoutineName(int solveNo, int ncondNo)
{
  int length = stringLength("ncond?_?");
  if(solveNo > 9) {
    length++;
    if(solveNo >99) {
      cerr <<"solve number too large(GetNeumannRoutineName)\n";
      abortExit(1);
    }
  }

  if(ncondNo > 9){
    length++;
    if(ncondNo >99) {
      cerr <<"ncond number too large(GetNeumannRoutineName)\n";
      abortExit(1);
    }
  }

  char *ptr = new char[length];

  sprintf(ptr,"ncond%d_%d",solveNo,ncondNo);    // PMDependent

  return(ptr);
}


void PM_feelP2DRAMA::DoNeumannParametersPM(Neumann *nPtr)
{
  /* parameter NPG */
  int oimo = nPtr->GetNPG();
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

void PM_feelP2DRAMA::DoNeumannArgumentVariableDefinitionsPM(Neumann *nPtr)
{
  com();
  writeSource("      integer*4 mypeid,nprocs");
  writeSource("      integer*4 nbedatno,nbelem");
  writeSource("      integer*4 benptr(2,*),bmatno(*),bcon(2,*)");
  writeSource("      integer*4 isumup(*),myeqfrom,myeqto,neqtotal");
  writeSource("      real   *8 x(*),y(*)");
  writeSource("      integer*4 ipf(*),ipd(*),npmax");
  writeSource("      integer*4 ndno(*),peno(*)");
  writeSource("      real   *8 xex(*),yex(*)");
  writeSource("      integer*4 ipfex(*),ipdex(*),nouter");
  
  orderedPtrList <Variable *> varPtrLst = nPtr->GetVariablePtrLst();
  ArgumentVariableDeclarationLst(varPtrLst);
  
  com();

  // FEM variables for EX 
  listIterator <Variable *>itrvar(varPtrLst);
  for(itrvar.init(); !itrvar; ++itrvar ){
    if(itrvar()->GetType() != VAR_FEM) continue;

    pushSource("      real   *8 ");
    pushFEMVariableExternalInCalled(itrvar());
    pushSource("(*)");
    flushSource();
  }
  comment();
  

  return;
}

void PM_feelP2DRAMA::DoNeumannAutoVariableDefinitionsPM(Neumann *nPtr)
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
  if(nPtr->GetMatNonZero() != 0) {   //  if(nPtr->GetBaFlag()) {
    writeSource("      dimension ba (NDF,NDF)");
  }
  writeSource("      dimension bb (NDF)");
  writeSource("      dimension ikp(NDF),jkp(NDF)");
  com();

  /* ienp,iedp */
  writeSource("      dimension ienp(NDF)");
  writeSource("      dimension iedp(NDF)");
  com();
  
  /* real *8 function */
  writeSource("      real*8    dramafemval");
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

}


void PM_feelP2DRAMA::DoNeumannInitializerPM(Neumann *nPtr)
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


void PM_feelP2DRAMA::DoNeumannBoundaryElementLoopStartPM(Neumann *nPtr)
{
  int streq(const char *, const char *);
  int testBoundaryPoints = nPtr->GetBoundaryPoints();
  writeSource("      do 200 i=1,nbelem");
  com();

  writeSource("       ipos_from = benptr(1,i  )");
  writeSource("       ipos_to   = benptr(1,i+1)-1");
  writeSource("       nodes     = ipos_to - ipos_from + 1");
  com();
  
  /* Skip if there is no relating boundary element in my PE region */
  writeSource("      iconcern = 0");
  writeSource("      do 201 j=1,nodes");
  writeSource("       if(bcon(2,ipos_from+j-1) .eq. mypeid) then");
  writeSource("        iconcern = iconcern+1");
  writeSource("       endif");
  writeSource("201   continue");
  writeSource("      if(iconcern .eq. 0) goto 200");
  com();

  for(int i=0;i<testBoundaryPoints;i++) {

    /* value for x test funcs */
    pushSource("        x");
    pushSourceInt(i+1);
    pushSource(" = dramafemval( mypeid,");
    flushSource();
    
    pushSource("     $                    bcon(1,ipos_from +");
    pushSourceInt(i+1);
    pushSource(" -1),");
    flushSource();

    pushSource("     $                    bcon(2,ipos_from +");
    pushSourceInt(i+1);
    pushSource(" -1),");
    flushSource();

    writeSource("     $                    x,npmax,xex,ndno,peno,nouter)");
    com();

    /* value for y test funcs */
    pushSource("        y");
    pushSourceInt(i+1);
    pushSource(" = dramafemval( mypeid,");
    flushSource();
    
    pushSource("     $                    bcon(1,ipos_from +");
    pushSourceInt(i+1);
    pushSource(" -1),");
    flushSource();

    pushSource("     $                    bcon(2,ipos_from +");
    pushSourceInt(i+1);
    pushSource(" -1),");
    flushSource();

    writeSource("     $                    y,npmax,yex,ndno,peno,nouter)");

    com();
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
    pushSuperDotempDRAMAneumannFEMval(itrfl(),itrfr());
    /* pushSuperDotempDRAMAneumannFEMval write several lines */
    com();
  }
  comment();

  
  if(nPtr->GetMatNonZero() != 0) {  //  if(nPtr->GetBaFlag()) {
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

  writeSource("nPtr->GetQxFlag())  at L1517");
  //  if(nPtr->GetQxFlag()) {
  //    pushSource("       qx=");
  //    pushSource(nPtr->GetQxFormula());
  //    flushSource();
  //  }

  writeSource("if(nPtr->GetQyFlag()) { at 1524");
  //  if(nPtr->GetQyFlag()) {
  //    pushSource("       qy=");
  //    pushSource(nPtr->GetQyFormula());
  //    flushSource();
  //  }
  com();

  writeSource("       ds=sqrt(dx*dx+dy*dy)*w(itp)");
  com();


  writeSource("  if(nPtr->GetBaFlag()) { at 1536");
  //  if(nPtr->GetBaFlag()) {
  //    list <int>testBaILst = nPtr->GetBaILst();
  //    list <int>testBaJLst = nPtr->GetBaJLst();
  //    list <char *>testBaFormulaLst = nPtr->GetBaFormulaLst();
  //
  //    listIterator <int>itrI(testBaILst);
  //    listIterator <int>itrJ(testBaJLst);
  //    listIterator <char *>itrFormula(testBaFormulaLst);
  //
  //    for(itrI.init(),itrJ.init(),itrFormula.init();
  //	!itrI;
  //	++itrI,++itrJ,++itrFormula) {
  //      if(streq("0.0d0",itrFormula())) continue;
  //
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
  //  }
  com();

  list <char *>testBbFormulaLst = nPtr->GetBbFormulaLst();
  listIterator<char *>itrBFormula(testBbFormulaLst);
    
  int i;
  i= 0;
  for(itrBFormula.init(); !itrBFormula; ++itrBFormula,++i) {

    if(streq("0.0d0",itrBFormula())) continue;

    pushSource("        bb(");
    pushSourceInt(i+1);
    pushSource(")=bb(");
    pushSourceInt(i+1);
    pushSource(")+(");
    pushSource(itrBFormula());
    pushSource(")*ds");
    flushSource();
  }
  com();

  /**/
  writeSource(" 300  continue");
  com();

  /**/  
  /* Prepare ikp,jkp */
  writeSource("      do 400 j=1,NDF");

  writeSource("       ind = bcon(1,ipos_from + ienp(j)-1)");
  writeSource("       ipe = bcon(2,ipos_from + ienp(j)-1)");
  com();
  writeSource("       if(ipe .NE. mypeid) then");
  com();
  writeSource("        nd = ndsearch_ex2(ind,ipe,ndno,peno,nouter)");
  writeSource("        if(nd .LT. 1) then");
  writeSource("          call abortexit(mypeid,'Cannot find ndex(ncond)')");
  writeSource("        endif");
  writeSource("        ikp(j) = 0");
  writeSource("        jkp(j) = ipdex(nd)+iedp(j)+isumup(ipe+1)");
  com();
  writeSource("       else");
  com();
  writeSource("        ikp(j) = ipd(ind)+iedp(j)");
  writeSource("        jkp(j) = ikp(j)          +isumup(ipe+1)");
  writeSource("       endif");
  com();

  writeSource(" 400  continue");
  com();

  return;
}
    
void PM_feelP2DRAMA::DoNeumannBoundaryElementLoopEndPM(Neumann *nPtr)
{
  writeSource(" 200  continue");
  com();
  return;
}

void PM_feelP2DRAMA::pushSuperDotempDRAMAneumannFEMval(char *left,char *right)
{
  char  fem_var_name[BUFSIZ];
  int   number;
  int   ctr,length;
  int   digit1,digit2;
  int   strindex(const char *,const char *);

  ctr = strindex(right,"fem_");
  if(ctr == 0) {
    pushSource(" HATENA???(pushSuperDotempDRAMAneumannFEMval)");
    return;
  }

  length = 0;
  while(*(right + ctr+3) != '(') {
    fem_var_name[length] = *(right+ctr+3);
    ctr++;
    length++;
  }
  fem_var_name[length] = '\0';

  ctr = strindex(right,"ielem(");
  if(ctr == 0) {
    pushSource(" HATENA(2)???(pushSuperDotempDRAMAneumannFEMval)");
    return;
  }

  digit1 = *(right+ctr+5);
  if(digit1 < '0' || digit1 > '9') {
    pushSource(" HATENA(3)???(pushSuperDotempDRAMAneumannFEMval)");
    return;
  }
  digit2 = *(right+ctr+6);

  if(digit2 == ',') {
    number = digit1 - '0';
  }
  else {
    if(digit2 < '0' || digit2 > '9') {
      pushSource(" HATENA(4)???(pushSuperDotempDRAMAneumannFEMval)");
      return;
    }
    else {
      number = (digit1-'0')*10 + (digit2-'0');
    }
  }

  pushSource(" dramafemval( mypeid,");
  flushSource();

  pushSource("     $                  bcon(1,ipos_from + ");
  pushSourceInt(number);
  pushSource(" -1),");
  flushSource();

  pushSource("     $                  bcon(2,ipos_from + ");
  pushSourceInt(number);
  pushSource(" -1),");
  flushSource();

  pushSource("     $                  fem_");
  pushSource(fem_var_name);
  pushSource(",npmax,femex_");
  pushSource(fem_var_name);
  pushSource(",ndno,peno,nouter)");
  flushSource();
  
  return;
}

void PM_feelP2DRAMA::DoNeumannReturnSequencePM(Neumann *nPtr)
{
  writeSource("      return");
  writeSource("      end");

  return;
}

// END OF NEUMANN RELATED FUNCTIONS


// PARALLEL VERSION
void PM_feelP2DRAMA::SubDoSolveMessageKnownFEMVars( Solve *solvePtr )
					   
{
  // Preparation for several values to make a program
  // Calculate the number of fem variables to exchange 
  // Make List for exchanging fem variables


  // Because of P2 ONLY version, ONLY ONE ENPTR ASSUMED!!!!!!!!!
  int fem_exchange_variables;
  SolveElement *sePtr = solvePtr->GetIthSolveElementPtr(0); // P2 FIXED
  orderedPtrList <Variable *> varPtrLst = sePtr->GetVariablePtrLst();
  
  fem_exchange_variables = 0;
  listIterator <Variable *> itr(varPtrLst);
  for(itr.init(); !itr;++itr) {
    if(itr()->GetType() == VAR_FEM) fem_exchange_variables++;
  }

  comment();
  writeSource("* Make exchange list (eflag/nflag)");
  comment();

  writeSource("      call f_alloc(np_eflag,'element flag',nelem,0,0)");
  writeSource("      call f_alloc(np_nflag,'element flag',npmax,0,0)");

  writeSource("      call mksendlst(feel,myrank,nprocs,");
  writeSource("     $ feel(np_e),feel(np_c),nelem,npmax,");
  writeSource("     $ feel(np_eflag),feel(np_nflag),");
  writeSource("     $ ne2send,nconsiz,nn2send)");
  com();
  writeSource("      if(myrank .eq. 0) call preportmodule('MKSENDLST')");
  comment();

  writeSource("* Calculation of necessary memory size");
  writeSource("*");
  writeSource("*  INTEGER*4 data buffer");
  writeSource("* -------");
  writeSource("*  ctrl    INTEGER*4     NCTRL_ITEMS");
  writeSource("* -------");
  writeSource("*  enptr   INTEGER*4   2*ne2send");
  writeSource("*  con     INTEGER*4   2*nconsiz");
  writeSource("*  matno   INTEGER*4     ne2send");
  writeSource("* -------");
  writeSource("*  nodeno  INTEGER*4     nn2send");
  writeSource("*  ipf     INTEGER*4     nn2send");
  writeSource("*  ipd     INTEGER*4     nn2send");
  writeSource("*-------------------------------");
  writeSource("* REAL*8 data buffer");
  writeSource("* x,y (,z) REAL*8   ndim*nn2send");
  writeSource("* KNOWN FEM variables");
  writeSource("* UNKNOWN FEM variables (nonlinear case)");
  comment();

  writeSource("      nsend_int  = NCTRL_ITEMS +");
  writeSource("     $            (ne2send+1)*2 + ne2send+nconsiz*2+");
  writeSource("     $             nn2send*3");
  com();
 
  writeSource("*     nfemvars_send   number of fem variables to send");
  pushSource ("      nfemvars_send = ");
  pushSourceInt(fem_exchange_variables);
  flushSource();		

  writeSource("      nsend_dbl  = nn2send*ndim + nn2send*nfemvars_send");
  com();

  writeSource("      call f_alloc(np_mysendibuf,'mysendifuf',nsend_int,0,0)");
  writeSource("      if(nsend_dbl .NE. 0) then");
  writeSource("        call f_alloc(np_mysenddbuf,'mysenddbuf',nsend_dbl,1,0)");
  writeSource("      else");
  writeSource("        np_mysenddbuf = 1");
  writeSource("      endif");
  com();
  writeSource("      np_ctrl_send  = np_mysendibuf");
  writeSource("      np_enptr_send = np_mysendibuf+NCTRL_ITEMS");
  writeSource("      np_con_send   = np_mysendibuf+NCTRL_ITEMS+(ne2send+1)*2");
  writeSource("      np_matno_send = np_con_send  + nconsiz   *2");
  writeSource("      np_nodeno_send= np_matno_send+ ne2send");
  writeSource("      np_ipf_send   = np_nodeno_send+nn2send");
  writeSource("      np_ipd_send   = np_ipf_send  + nn2send");
            
  writeSource("      np_x_send     = np_mysenddbuf");
  writeSource("      np_y_send     = np_mysenddbuf+nn2send*NBYTE_REAL8");
  
  int counter = 0;
  for(itr.init(); !itr;++itr) {
    if(itr()->GetType() == VAR_FEM) {
      counter++;
      pushSource("      np_");
      pushSource(itr()->GetName());
      pushSource("_send = np_mysenddbuf+nn2send*NBYTE_REAL8*");
      pushSourceInt(counter+1);
      flushSource();
    }
  }  
  comment();

  // call solveNdatsend 
  pushSource("      call solve");
  pushSourceInt(solvePtr->GetSolveNo());
  pushSource("mksdbuf(myrank,nprocs,npmax,nelem,");
  flushSource();
  
  writeSource("     $  ne2send,nconsiz,nn2send,neq,");
  writeSource("     $  feel(np_e),feel(np_c),feel(np_m),");
  writeSource("     $  feel(np_eflag),feel(np_nflag),");
  pushSource("     $  x,y,feel(np_ipf),feel(np_ipd)");

  // fem varaibles
  for(itr.init(); !itr;++itr) {
    if(itr()->GetType() == VAR_FEM) {
      string a;
      pushSource(",");
      NameVariableInCalled(itr(),a);
      pushSource(a); 
    }
  }  
  pushSource(",");
  flushSource();

  writeSource("     $  feel(np_ctrl_send),");
  writeSource("     $  feel(np_enptr_send),feel(np_con_send),feel(np_matno_send),");
  writeSource("     $  feel(np_nodeno_send),feel(np_ipf_send),feel(np_ipd_send),");


  pushSource ("     $  feel(np_x_send),feel(np_y_send)");

  for(itr.init(); !itr;++itr) {
    if(itr()->GetType() == VAR_FEM) {
      pushSource(",feel(np_");
      pushSource(itr()->GetName());
      pushSource("_send)");
    }
  }  
  pushSource(")");
  flushSource();
  com();
  
  writeSource("      if(myrank.eq.0) call preportmodule('DATSEND WRITE')");
  comment();
  
  writeSource("      call feelgathervbcast(myrank,nprocs,feel,");
  writeSource("     $     nsend_int,feel(np_mysendibuf),");
  writeSource("     $     np_intbuf,np_intcounts,np_intdispls)");
  com();
  writeSource("      call feelgathervbcastdbl(myrank,nprocs,feel,");
  writeSource("     $     nsend_dbl,feel(np_mysenddbuf),");
  writeSource("     $     np_dblbuf,np_dblcounts,np_dbldispls)");
  comment();

  return;
}


void PM_feelP2DRAMA::SubDoSolveMakeExIelem( void )  
{
  COMMENTlong("Make Exterior enptr/con");
  writeSource("      call mkielemex(feel,myrank,nprocs,NCTRL_ITEMS,");
  writeSource("     $     feel(np_e),feel(np_c),feel(np_m),nelem,");
  writeSource("     $     feel(np_intbuf),");
  writeSource("     $     feel(np_intcounts),feel(np_intdispls),");
  writeSource("     $     feel(np_dblbuf),");          
  writeSource("     $     feel(np_dblcounts),feel(np_dbldispls),");
  writeSource("     $     nelem_ex,np_enptr_ex,np_con_ex,np_matno_ex)");
  writeSource("      if(myrank.eq.0) call preportmodule('MKIELEMEX')");
  comment();

  return;
}

void PM_feelP2DRAMA::SubDoSolveMakeSumupDegree( void )  
{
  COMMENTlong("Make summed up degree of freedom");
  writeSource("      call f_alloc(np_isumup,'solve(isumup)',nprocs+1,0,0)");
  writeSource("      call sumupdegree(mypeid,nprocs,NCTRL_ITEMS,");
  writeSource("     $     feel(np_intbuf),");
  writeSource("     $     feel(np_intcounts),feel(np_intdispls),");
  writeSource("     $     feel(np_isumup),neqtotal,myeqfrom,myeqto)");
  writeSource("      if(myrank.eq.0) call preportmodule('SUMUPDEGREE')");
  comment();
  
  return;
}

void PM_feelP2DRAMA::SubDoSolveMakeExNode( Solve *solvePtr )  
{
  int fem_exchange_variables;
  SolveElement *sePtr = solvePtr->GetIthSolveElementPtr(0); // P2 FIXED
  orderedPtrList <Variable *> varPtrLst = sePtr->GetVariablePtrLst();
  
  fem_exchange_variables = 0;
  listIterator <Variable *> itr(varPtrLst);
  for(itr.init(); !itr;++itr) {
    if(itr()->GetType() == VAR_FEM) fem_exchange_variables++;
  }

  COMMENTlong("Make NODE EX");
  pushSource( "      call solve");
  pushSourceInt(solvePtr->GetSolveNo());
  pushSource("mkexnode(feel,myrank,nprocs,NCTRL_ITEMS,");
  flushSource();

  writeSource("     $     x,y,npmax,");

  // FEM variables
  pushSource( "     $ ");
  for(itr.init(); !itr;++itr) {
    if(itr()->GetType() == VAR_FEM) {
      string a;
      NameVariableInCalled(itr(),a);
      pushSource(a);
      pushSource(",");
    }
  }  
  flushSource();

  writeSource("     $  feel(np_e),feel(np_c),nelem,");
  writeSource("     $  feel(np_enptr_ex),feel(np_con_ex),nelem_ex,");
  writeSource("     $  feel(np_intbuf),");
  writeSource("     $  feel(np_intcounts),feel(np_intdispls),");
  writeSource("     $  feel(np_dblbuf),");          
  writeSource("     $  feel(np_dblcounts),feel(np_dbldispls),");
  writeSource("     $  nouter,");
  writeSource("     $  np_ndno,np_peno,np_ipfex,np_ipdex,np_xex,np_yex");
  
  pushSource( "     $  ");
  for(itr.init(); !itr;++itr) {
    if(itr()->GetType() == VAR_FEM) {
      pushSource(",npfex_");
      pushSource(itr()->GetName());
    }
  }  
  pushSource(")");
  flushSource();
  

  writeSource("      if(myrank.eq.0) call preportmodule('MAKEEXNODE')");
  comment();

  return;
}
void PM_feelP2DRAMA::GenerateCoSolveRoutines(Solve *solvePtr)
{
  GenerateCoSolveEdevRoutine(solvePtr);

  GenerateCoSolve_mksdbuf(solvePtr);    //solve#mksdbuf.f
  GenerateCoSolve_mkexnode(solvePtr);   //solve#mkexnode.f

  return;
}

void PM_feelP2DRAMA::GenerateCoSolveEdevRoutine(Solve *solvePtr)
{
  SolveElement *sePtr = solvePtr->GetIthSolveElementPtr(0); // P2 FIXED

  char  hereRoutineName[BUFSIZ];
  char *hereSourceName;

  int solveElementNo = 1;   // P2 FIXED to 1
  
  sprintf(hereRoutineName,"edev%d_%d",solvePtr->GetSolveNo(),solveElementNo);  
  hereSourceName = GetSourceName(hereRoutineName);
  OpenSource(hereSourceName,LINKLEVEL_EDEV);

  pushSource("      subroutine ");
  pushEdevRoutineName( solvePtr->GetSolveNo(), solveElementNo);
  pushSource("(myrank,resvec,ipd,enptr,con,nelem");

  pushVariableListInCalled( sePtr->GetUnknownVariablePtrLst());
  pushSource(")");

  flushSource();
  
  SourceStarters();

  writeSource("      integer*4 myrank");
  writeSource("      real   *8 resvec(*)");
  writeSource("      integer*4 ipd(*)");
  writeSource("      integer*4 enptr(2,*)");
  writeSource("      integer*4 con  (2,*)");
  writeSource("      integer*4 nelem");
  com();

  list <Variable *>varPtrLst = sePtr->GetUnknownVariablePtrLst();
  ArgumentVariableDeclarationLst(varPtrLst);
  com();

  listIterator <Variable *>itr(varPtrLst);
  for(itr.init(); !itr;++itr) {
    pushSource("      integer*4 ienp_");
    pushSource(itr()->GetName());
    pushSource("(");
    pushSourceInt(itr()->testGetElementFreedom());
    pushSource(")");
    flushSource();

    pushSource("      integer*4 iedp_");
    pushSource(itr()->GetName());
    pushSource("(");
    pushSourceInt(itr()->testGetElementFreedom());
    pushSource(")");
    flushSource();
  }
  com();

  int ienp_ptr,iedp_ptr;
  ienp_ptr = 0;
  iedp_ptr = 0;
  for(itr.init(); !itr;++itr) {
    
    pushSource("      data ienp_");
    pushSource(itr()->GetName());
    pushSource("/ ");
    for(int k=0;k<itr()->testGetElementFreedom();k++) {
      if(k != 0) { pushSource(","); }
      pushSourceInt(sePtr->GetIthIENP(ienp_ptr));
      ienp_ptr++;
    }
    pushSource("/");
    flushSource();

    pushSource("      data iedp_");
    pushSource(itr()->GetName());
    pushSource("/ ");
    for(int k=0;k<itr()->testGetElementFreedom();k++) {
      if(k != 0) { pushSource(","); }
      pushSourceInt(sePtr->GetIthIEDP(iedp_ptr));
      iedp_ptr++;
    }
    pushSource("/");
    flushSource();
  }
  comment();


  writeSource("      mypeid = myrank");
  com();
  
  writeSource("      do 100 i=1,nelem");
  writeSource("        ipos_from = enptr(1,i  )");
  writeSource("        ipos_to   = enptr(1,i+1)-1");
  writeSource("        nodes     = ipos_to-ipos_from+1");

  int ivars;
  ivars = 0;
  
  for(itr.init(); !itr;++itr) {
    com();
    pushSource("        do ");
    pushSourceInt( 110 + ivars);
    pushSource(" j=1,");
    pushSourceInt( itr()->testGetElementFreedom());
    flushSource();
    
    pushSource("        nnd = con(1,ipos_from+ienp_");
    pushSource(itr()->GetName());
    pushSource("(j)-1)");
    flushSource();

    pushSource("        npe = con(2,ipos_from+ienp_");
    pushSource(itr()->GetName());
    pushSource("(j)-1)");
    flushSource();

    pushSource("        if(npe .ne. mypeid) goto ");
    pushSourceInt(110+ivars);
    flushSource();
    
    pushSource("        fem_");
    pushSource(itr()->GetName());
    pushSource("(nnd) = resvec(ipd(nnd) + iedp_");
    pushSource(itr()->GetName());
    pushSource("(j))");
    flushSource();

    pushSourceInt(110+ivars);
    pushSource("     continue");
    flushSource();

    ivars++;
  }

  com();
  writeSource("100   continue");
  
  comment();
  
  writeSource("      return");
  writeSource("      end");
  
  
  CloseSource();
  return;

}


void PM_feelP2DRAMA::GenerateCoSolve_mksdbuf(Solve *solvePtr)
{
  // make solve#mksdbuf.f

  // Because of P2 ONLY version, ONLY ONE ENPTR ASSUMED!!!!!!!!!
  int fem_exchange_variables;
  SolveElement *sePtr = solvePtr->GetIthSolveElementPtr(0); // P2 FIXED
  orderedPtrList <Variable *> varPtrLst = sePtr->GetVariablePtrLst();
  
  fem_exchange_variables = 0;
  listIterator <Variable *> itr(varPtrLst);
  for(itr.init(); !itr;++itr) {
    if(itr()->GetType() == VAR_FEM) fem_exchange_variables++;
  }

  char  hereRoutineName[BUFSIZ];
  char *hereSourceName;
  
  sprintf(hereRoutineName,"solve%dmksdbuf",solvePtr->GetSolveNo());
  hereSourceName = GetSourceName(hereRoutineName);
  OpenSource(hereSourceName,LINKLEVEL_SUBSOLVE_DEPENDENT);

  // MAKESDBUF ROUTINE
  pushSource("      subroutine ");
  pushSource(hereRoutineName);
  pushSource("(myrank,nprocs,npmax,nelem,");
  flushSource();
  
  writeSource("     $  ne2send,nconsiz,nn2send,neq,");
  writeSource("     $  enptr,con,matno,eflag,nflag,");
  pushSource("     $  x,y,ipf,ipd");

  // fem varaibles
  for(itr.init(); !itr;++itr) {
    if(itr()->GetType() == VAR_FEM) {
      string a;
      pushSource(",");
      NameVariableInCalled(itr(),a);
      pushSource(a); 
    }
  }  
  pushSource(",");
  flushSource();

  writeSource("     $  ctrl_send,enptr_send,con_send,matno_send,");
  writeSource("     $  nodeno_send,ipf_send,ipd_send,");
  pushSource ("     $  x_send,y_send");    // 2D-limit

  for(itr.init(); !itr;++itr) {
    if(itr()->GetType() == VAR_FEM) {
      pushSource(",fem_");
      pushSource(itr()->GetName());
      pushSource("_send");
    }
  }  
  pushSource(")");
  flushSource();  
  comment();
  //
  writeSource("      real*8    x(*),y(*)");
  writeSource("      integer*4 enptr(2,*),con(2,*),matno(*)");
  writeSource("      integer*4 nflag(*),eflag(*)");
  writeSource("      integer*4 ipf(*),ipd(*)");
  for(itr.init(); !itr;++itr) {
    if(itr()->GetType() == VAR_FEM) {
      string a;
      pushSource("      real*8    ");
      NameVariableInCalled(itr(),a);
      pushSource(a); 
      pushSource("(*)");
      flushSource();
    }
  }
  com();

  writeSource("      integer*4 ctrl_send(*)");
  writeSource("      integer*4 enptr_send(2,*),con_send(2,*),matno_send(*)");
  writeSource("      integer*4 nodeno_send(*),ipf_send(*),ipd_send(*)");
  writeSource("      real   *8 x_send(*),y_send(*)");

  for(itr.init(); !itr;++itr) {
    if(itr()->GetType() == VAR_FEM) {
      pushSource("      real   *8 fem_");
      pushSource(itr()->GetName());
      pushSource("_send(*)");
      flushSource();
    }
  }  
  comment();
  writeSource("      ctrl_send(1) = ne2send");
  writeSource("      ctrl_send(2) = nconsiz");
  writeSource("      ctrl_send(3) = nn2send");
  writeSource("      ctrl_send(4) = neq");
  comment();
 
  writeSource("      if(ne2send .EQ. 0) goto 995");
  com();
  writeSource("      iptr = 0");
  writeSource("      ipos = 1");
  com();
  writeSource("      do 100 i=1,nelem");
  com();
  writeSource("        if(eflag(i) .EQ. 0) goto 100");
  writeSource("        iptr = iptr + 1");
  com();
  writeSource("        enptr_send(1,iptr) = ipos");
  writeSource("        enptr_send(2,iptr) = enptr(2,i)");
  writeSource("        matno_send(iptr  ) = matno(i)");
  com();
  writeSource("        ipos_from = enptr(1,i  )");
  writeSource("        ipos_to   = enptr(1,i+1)-1");
  com();
  writeSource("        do 110 j=ipos_from,ipos_to");
  writeSource("          con_send(1,ipos) = con(1,j)");
  writeSource("          con_send(2,ipos) = con(2,j)");
  writeSource("          ipos = ipos + 1");
  writeSource(" 110    continue");
  com();
  writeSource(" 100  continue");
  com();
  writeSource("      enptr_send(1,iptr+1) = ipos");
  writeSource("      enptr_send(2,iptr+1) = 999");
  com();
  comment();
  com();
  comment();
  writeSource(" 995  continue");
  comment();
  com();
  comment();
  writeSource("      iptr = 0");
  writeSource("      do 200 i=1,npmax");
  writeSource("        if(nflag(i) .EQ. 1) then");
  writeSource("          iptr = iptr + 1");
  writeSource("          nodeno_send(iptr) = i");
  writeSource("          ipf_send   (iptr) = ipf(i)");
  writeSource("          ipd_send   (iptr) = ipd(i)");
  writeSource("          x_send     (iptr) = x(i)");
  writeSource("          y_send     (iptr) = y(i)");
  for(itr.init(); !itr;++itr) {
    if(itr()->GetType() == VAR_FEM) {
      string a;
      pushSource("          fem_");
      pushSource(itr()->GetName());
      pushSource("_send(iptr) = ");
      NameVariableInCalled(itr(),a);
      pushSource(a); 
      pushSource("(i)");
      flushSource();
    }
  }
  writeSource("        endif");
  writeSource(" 200  continue");
  com();
  writeSource("      if(iptr .ne. nn2send) then");
  writeSource("        call abortexit(myrank,'OKASHII mksdbuf')");
  writeSource("      endif");
  comment();

  
  writeSource("      return");
  writeSource("      end");
  CloseSource();
  // end of solve#mksdbuf

  return;
}

void PM_feelP2DRAMA::GenerateCoSolve_mkexnode(Solve *solvePtr)
{
  // make solve#mkexnode.f

  // Because of P2 ONLY version, ONLY ONE ENPTR ASSUMED!!!!!!!!!
  int fem_exchange_variables;
  SolveElement *sePtr = solvePtr->GetIthSolveElementPtr(0); // P2 FIXED
  orderedPtrList <Variable *> varPtrLst = sePtr->GetVariablePtrLst();
  
  fem_exchange_variables = 0;
  listIterator <Variable *> itr(varPtrLst);
  for(itr.init(); !itr;++itr) {
    if(itr()->GetType() == VAR_FEM) fem_exchange_variables++;
  }

  char  hereRoutineName[BUFSIZ];
  char *hereSourceName;
  
  sprintf(hereRoutineName,"solve%dmkexnode",solvePtr->GetSolveNo());
  hereSourceName = GetSourceName(hereRoutineName);
  OpenSource(hereSourceName,LINKLEVEL_SUBSOLVE_DEPENDENT);

  // MAKESDBUF ROUTINE
  pushSource("      subroutine ");
  pushSource(hereRoutineName);
  pushSource("(feel,myrank,nprocs,nparams,");
  flushSource();

  pushSource("     $     x,y,npmax,");
  // FEM variables
  for(itr.init(); !itr;++itr) {
    if(itr()->GetType() == VAR_FEM) {
      string a;
      NameVariableInCalled(itr(),a);
      pushSource(a);
      pushSource(",");
    }
  }  
  flushSource();

  writeSource("     $  enptr,con,nelem,");
  writeSource("     $  enptr_ex,con_ex,nelem_ex,");
  writeSource("     $  ibuf,icount,idispl,");
  writeSource("     $  dbuf,dcount,ddispl,");
  writeSource("     $  nouter,");
  writeSource("     $  np_ndno,np_peno,np_ipfex,np_ipdex,np_xex,np_yex");
  
  pushSource( "     $  ");
  for(itr.init(); !itr;++itr) {
    if(itr()->GetType() == VAR_FEM) {
      pushSource(",npfex_");
      pushSource(itr()->GetName());
    }
  }  
  pushSource(")");
  flushSource();

  comment();
  writeSource("      parameter (MAX_PROCS = 256)");
  writeSource("      parameter (NCTRL_ITEMS_HERE = 4)");
  com();
  writeSource("      real*4    feel(*)");
  writeSource("      real   *8 x(*),y(*)");
  writeSource("      integer*4 enptr(2,*),con(2,*)");
  writeSource("      integer*4 enptr_ex(2,*),con_ex(2,*)");
  writeSource("      integer*4 ibuf(*)");
  writeSource("      real   *8 dbuf(*)");
  writeSource("      integer*4 icount(*),idispl(*)");
  writeSource("      integer*4 dcount(*),ddispl(*)");
  writeSource("*");

  // fem variables
  for(itr.init(); !itr;++itr) {
    if(itr()->GetType() == VAR_FEM) {
      string a;
      pushSource("      real   *8 ");
      NameVariableInCalled(itr(),a);
      pushSource(a);
      pushSource("(*)");
      flushSource();
    }
  }  

  writeSource("*");
  writeSource("      integer*4 procbuf(MAX_PROCS)");
  writeSource("*----------------------------------------------------------");
  writeSource("      if(MAX_PROCS .LT. nprocs) then");
  writeSource("         call abortexit(myrank,'Too many procs (makepielem)')");
  writeSource("      endif");
  com();
  writeSource("      if(NCTRL_ITEMS_HERE .NE. nparams) then");
  writeSource("         call abortexit(myrank,'Mismatch (mkexnode)')");
  writeSource("      endif");
  com();
  writeSource("      mypeid = myrank");
  writeSource("      mypeidx= myrank+1");
  writeSource("*---------------------------------------------------");
  writeSource("* Count the number of outer nodes (with duplication)");
  writeSource("*---------------------------------------------------");
  writeSource("      nouter = 0");
  writeSource("*---");
  writeSource("      do 100 i=1,nelem");
  writeSource("         ipos_from = enptr(1,i  )");
  writeSource("         ipos_to   = enptr(1,i+1)-1");
  com();
  writeSource("         do 110 j=ipos_from,ipos_to");
  writeSource("            if(con(2,j) .ne. mypeid) nouter = nouter+1");
  writeSource(" 110     continue");
  writeSource(" 100  continue");
  com();
  writeSource("      do 150 i=1,nelem_ex");
  writeSource("         ipos_from = enptr_ex(1,i  )");
  writeSource("         ipos_to   = enptr_ex(1,i+1)-1");
  com();
  writeSource("         do 160 j=ipos_from,ipos_to");
  writeSource("            if(con_ex(2,j) .ne. mypeid) nouter = nouter+1");
  writeSource(" 160     continue");
  writeSource(" 150  continue");
  com();
  writeSource("      call f_alloc_push");
  writeSource("      call f_alloc(np_ndno,'makepnode(ndno)',nouter,0,0)");
  writeSource("      call f_alloc(np_peno,'makepnode(peno)',nouter,0,0)");
  com();
  writeSource("      call mkexnd_outerlst(mypeid,");
  writeSource("     $            enptr,   con   ,nelem,");
  writeSource("     $            enptr_ex,con_ex,nelem_ex,");
  writeSource("     $            nouter  ,feel(np_ndno),feel(np_peno))");
  COMMENTlong("Memory move");
  writeSource("      call f_alloc_pop");
  com();
  writeSource("      call f_alloc(np_ndno,'makepnode(ndno.2)',nouter,0,0)");
  writeSource("      np_penobak = np_peno");
  writeSource("      call f_alloc(np_peno,'makepnode(peno.2)',nouter,0,0)");
  writeSource("      call f_move(feel(np_penobak),feel(np_peno),nouter)");
  com();
  writeSource("      call f_alloc(np_ipfex,'makenode(ipfex)',nouter,0,0)");
  writeSource("      call f_alloc(np_ipdex,'makenode(ipdex)',nouter,0,0)");
  writeSource("      call f_alloc(np_xex  ,'makenode(xex)'  ,nouter,1,0)");
  writeSource("      call f_alloc(np_yex  ,'makenode(yex)'  ,nouter,1,0)");

  char *oimo="oimo";
  
  // fem variables
  for(itr.init(); !itr;++itr) {
    if(itr()->GetType() == VAR_FEM) {
      pushSource("      call f_alloc(");
      pushSource("npfex_");
      pushSource(itr()->GetName()); 
      pushSource(",'mkexnd(");
      pushSource(itr()->GetName());   
      pushSource(")',nouter,1,0)");
      flushSource();
    }
  }  


  pushSource("      call solve");
  pushSourceInt(solvePtr->GetSolveNo());
  pushSource("mkpnd_co(nouter,feel(np_ndno),feel(np_peno),");
  flushSource();

  writeSource("     $                    feel(np_ipfex),feel(np_ipdex),");
  writeSource("     $                    feel(np_xex ),feel(np_yex ),");

  if(fem_exchange_variables >0) {
    pushSource( "     $ ");
    for(itr.init(); !itr;++itr) {
      if(itr()->GetType() == VAR_FEM) {
	pushSource("feel(");
	pushSource("npfex_");
	pushSource(itr()->GetName());
	pushSource("),");
      }
    }  
    flushSource();
  }

  writeSource("     $                    ibuf,icount,idispl,");
  writeSource("     $                    dbuf,dcount,ddispl,nparams,nprocs)");
  com();

  writeSource("      return");
  writeSource("      end");

  // Co-co-co Routin
  
  pushSource("      subroutine solve");
  pushSourceInt(solvePtr->GetSolveNo());
  pushSource("mkpnd_co(nouter,ndno,peno,");
  flushSource();

  writeSource("     $       ipfex,ipdex,xex ,yex,");

  if(fem_exchange_variables >0) {
    pushSource( "     $ ");
    for(itr.init(); !itr;++itr) {
      if(itr()->GetType() == VAR_FEM) {
	pushSource("femex_");
	pushSource(itr()->GetName());
	pushSource(",");
      }
    }  
    flushSource();
  }

  writeSource("     $       ibuf,icount,idispl,");
  writeSource("     $       dbuf,dcount,ddispl, nparams, nprocs)");


  comment();
  writeSource("      parameter (NCTRL_ITEMS_HERE = 4)");
  com();
  writeSource("      integer*4 ndno(*),peno(*)");
  writeSource("      integer*4 nd,pe,pex");
  writeSource("      integer*4 ipfex(*),ipdex(*)");
  writeSource("      real   *8 xex(*),yex(*)");

  if(fem_exchange_variables >0) {
    for(itr.init(); !itr;++itr) {
      if(itr()->GetType() == VAR_FEM) {
	pushSource( "      real   *8 ");
	pushSource("femex_");
	pushSource(itr()->GetName());
	pushSource("(*)");
	flushSource();
      }
    }  
  }

  com();

  writeSource("      integer*4 ibuf(*)");
  writeSource("      real   *8 dbuf(*)");
  writeSource("      integer*4 icount(*),idispl(*)");
  writeSource("      integer*4 dcount(*),ddispl(*)");
  writeSource("*----------------------------------------------------------");
  writeSource("      if(NCTRL_ITEMS_HERE .NE. nparams) then");
  writeSource("         call abortexit(myrank,'Mismatch parameters(makepnode1)')");
  writeSource("      endif");
  writeSource("*----------------------------------------------------------");
  writeSource("      do 100 i=1,nouter");
  writeSource("         nd = ndno(i)");
  writeSource("         pe = peno(i)");
  writeSource("         pex= pe + 1");
  com();
  writeSource("         if(pe .GE. nprocs  .OR. pe.LT.0) then");
  writeSource("           call abortexit(999,'illegal number in mkexnd_co')");
  writeSource("         endif");
  com();
  writeSource("         ne2send          = ibuf(idispl(pex)+1)");
  writeSource("         nconsiz          = ibuf(idispl(pex)+2)");
  writeSource("         nn2send          = ibuf(idispl(pex)+3)");
  writeSource("         iptr_enptr_send  = idispl(pex) + NCTRL_ITEMS_HERE+1");
  writeSource("         iptr_con_send    = idispl(pex) + NCTRL_ITEMS_HERE+");
  writeSource("     $                      2*(ne2send+1) + 1");
  writeSource("         iptr_matno_send  = iptr_con_send    + nconsiz * 2");
  writeSource("         iptr_nodeno_send = iptr_matno_send  + ne2send");
  writeSource("         iptr_ipf_send    = iptr_nodeno_send + nn2send");
  writeSource("         iptr_ipd_send    = iptr_ipf_send    + nn2send");
  com();
  writeSource("         iptr_x_send      = ddispl(pex) + 1");
  writeSource("         iptr_y_send      = ddispl(pex) + nn2send + 1");

  if(fem_exchange_variables >0) {
    int multi = 1;
    for(itr.init(); !itr;++itr) {
      if(itr()->GetType() == VAR_FEM) {
	pushSource( "         iptr_");
	pushSource(itr()->GetName());
	pushSource("_send = ddispl(pex) + nn2send*");
	multi++;
	pushSourceInt(multi);
	pushSource( "+1");
	flushSource();
      }
    }  
  }

  pushSource("         call solve");
  pushSourceInt(solvePtr->GetSolveNo());
  pushSource("mkexnd_sel(nd,");
  flushSource();

  writeSource("     $                           nn2send,");
  writeSource("     $                           ibuf(iptr_nodeno_send),");
  writeSource("     $                           ibuf(iptr_ipf_send),");
  writeSource("     $                           ibuf(iptr_ipd_send),");
  writeSource("     $                           dbuf(iptr_x_send),");
  writeSource("     $                           dbuf(iptr_y_send),");

  if(fem_exchange_variables >0) {
    for(itr.init(); !itr;++itr) {
      if(itr()->GetType() == VAR_FEM) {
	pushSource("     $                           dbuf(iptr_");
	pushSource(itr()->GetName());
	pushSource("_send),");
	flushSource();
      }
    }  
  }

  pushSource("     $        ipfex(i),ipdex(i),xex(i),yex(i)");
  if(fem_exchange_variables >0) {
    for(itr.init(); !itr;++itr) {
      if(itr()->GetType() == VAR_FEM) {
	pushSource(",femex_");
	pushSource(itr()->GetName());
	pushSource("(i)");
      }
    }  
  }
  pushSource(")");
  flushSource();
  com();
  writeSource(" 100  continue");
  com();

  writeSource("      return");
  writeSource("      end");


  // subroutine select

  pushSource("      subroutine solve");
  pushSourceInt(solvePtr->GetSolveNo());
  pushSource("mkexnd_sel(nd,nn2send,");
  flushSource();

  pushSource("     $      nodeno,ipf,ipd,x,y,");
  if(fem_exchange_variables >0) {
    for(itr.init(); !itr;++itr) {
      if(itr()->GetType() == VAR_FEM) {
	pushSource("femex_");
	pushSource(itr()->GetName());
	pushSource(",");
      }
    }  
  }
  flushSource();

  pushSource("     $      ipfex,ipdex,xex,yex");
  if(fem_exchange_variables >0) {
    for(itr.init(); !itr;++itr) {
      if(itr()->GetType() == VAR_FEM) {
	pushSource(",");
	pushSource(itr()->GetName());
	pushSource("_ex");
      }
    }  
  }
  pushSource(")");
  flushSource();

  writeSource("*-------------------------------------------------------------");
  writeSource("      integer*4 nd,nn2send");
  writeSource("      integer*4 nodeno(*),ipf(*),ipd(*)");
  writeSource("      real*8    x(*),y(*)");

  if(fem_exchange_variables >0) {
    for(itr.init(); !itr;++itr) {
      if(itr()->GetType() == VAR_FEM) {
	pushSource("      real*8    femex_");
	pushSource(itr()->GetName());
	pushSource("(*)");
	flushSource();
      }
    }  
  }

  writeSource("      integer*4 ipfex,ipdex");
  writeSource("      real*8    xex,yex");
  if(fem_exchange_variables >0) {
    for(itr.init(); !itr;++itr) {
      if(itr()->GetType() == VAR_FEM) {
	pushSource("      real*8    ");
	pushSource(itr()->GetName());
	pushSource("_ex");
	flushSource();
      }
    }  
  }
  comment();

  writeSource("      do 100 i=1,nn2send");
  writeSource("         if(nodeno(i) .eq. nd) then");
  writeSource("            ipfex = ipf(i)");
  writeSource("            ipdex = ipd(i)");
  writeSource("            xex   =   x(i)");
  writeSource("            yex   =   y(i)");

  if(fem_exchange_variables >0) {
    for(itr.init(); !itr;++itr) {
      if(itr()->GetType() == VAR_FEM) {
	pushSource("            ");
	pushSource(itr()->GetName());
	pushSource("_ex = femex_");
	pushSource(itr()->GetName());
	pushSource("(i)");
	flushSource();
      }
    }  
  }

  writeSource("            return");
  writeSource("         endif");
  writeSource(" 100  continue");
  com();
  writeSource("      call abortexit(999,'cannot find node in makepnode1')");
  writeSource("      end");

  CloseSource();
  return;

}


string PM_feelP2DRAMA::SuperRinjiEcalP2DRAMA( char *s)
{
  char  femname[BUFSIZ];
  char  number [BUFSIZ];
  char  val    [BUFSIZ];
  int   ptr;
  ptr = 4;
  while(*(s+ptr) != '(') {
    femname[ptr-4] = *(s+ptr);
    ptr++;
  }
  femname[ptr-4] = '\0';
  
  ptr += 7;
  int base = ptr;
  while(*(s+ptr) != ',') {
    number[ptr-base] = *(s+ptr);
    ptr++;
  }
  number[ptr-base]='\0';

  sprintf(val,"efem_%s(%s)",femname,number);

  string ret = val;
  return(ret);
}
