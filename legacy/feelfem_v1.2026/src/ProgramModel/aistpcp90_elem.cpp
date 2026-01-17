/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : aistpcp90_elem.cpp
 *  Date     : 2002/06/28  (copy from feelfem90)
 *  Modified : 
 *  
 *  Purpose  : elem related routine generator for aistpcp90 model
 *             (derived from drama model)
 *  
 *  1. I/O related. (get/push routine name)
 *  
 *  
 */
#include "feelfuncs.hpp"

#include "Quadrature.hpp"
#include "PM_aistpcp90.hpp"
#include "ElemGeneratorTemplate.hpp"


// 0. Special rinji routines

string PM_aistpcp90::SuperRinjiEcalP2DRAMA(const  char *s)
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


// 1. I/O related.

char *PM_aistpcp90::GetElemRoutineName( int solveNo )
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

void PM_aistpcp90::pushElemRoutineName(int solveNo)
{
  char *ptr;
  ptr = GetElemRoutineName(solveNo);
  pushSource(ptr);
  delete ptr;

  return;
}

void PM_aistpcp90::F90useElemPM(SolveElement *sePtr)
{
  // use sentence for ecal routine
  pushSource("use mod_");
  pushEcalRoutineName( sePtr );
  flushSource();
  com();

  // use sentence for eset routines
  for(int i=0;i<sePtr->GetQuadratures();i++) {
    pushSource("use mod_");
    pushEsetRoutineName( sePtr->GetSolveNo(),
			 sePtr->GetElemNo(),
			 i + 1);
    flushSource();
  }
  com();

  return;
}

// ###  Variable definitons
void PM_aistpcp90::doElemDeclareArgumentVariablesPM(SolveElement *sePtr)
{
  writeInteger4sc("myrank,nprocs");
  writeInteger4Ptr1("IEDOM");
  writeInteger4Ptr2("ielem"); // integer,dimension(:,:),pointer    :: ielem
  writeInteger4Ptr1("matno"); // integer,dimension(:),pointer      :: matno
  writeInteger4In("nelem,np");// integer,intent(in)                :: nelem,np
  CoordinateVariableDeclaration();
  writeInteger4Ptr1("ipf,ipd");//integer,dimension(:),pointer      :: ipf,ipd
  writeInteger4In("npmax");    //integer,intent(in)                :: npmax
  writeInteger4In("neq");      //integer,intent(in)                :: neq
  com();

  // fem,ewise,scalar variables
  orderedPtrList <Variable *> varPtrLst = sePtr->GetVariablePtrLst();
  ArgumentVariableDeclarationLst(varPtrLst);
  com();

  return;
}


void PM_aistpcp90::DoElemVariableDefinitionsPM(SolveElement *sePtr)
{
  int strindex(const char *, const char *);
  orderedPtrList <Variable *> varPtrLst = sePtr->GetVariablePtrLst();
  listIterator <Variable *> itr(varPtrLst);

  COMMENTlong("Auto variables");
  writeInteger4sc("i,j,k,l");

  writeReal8sc("ex(NDP)");
  if(spaceDim >1) writeReal8sc("ey(NDP)");
  if(spaceDim >2) writeReal8sc("ez(NDP)");


  // interface to ecal routine
  for(itr.init(); !itr;++itr) {

    // fem variables
    if(itr()->GetType() == VAR_FEM) {
      pushReal8sc();
      pushSource("efem_");
      pushSource(itr()->GetName());
      pushSource("(NDP)");
      flushSource();
    }

    // ewise-fem varaibles (02-02-20)
    if(itr()->GetType() == VAR_EWISE_A) {
      if(itr()->GetEwiseType() == EWISE_TYPE_INTERPOLATION) {
	pushReal8sc();
	pushSource("eew_");
	pushSource(itr()->GetName());
	pushSource("(NDP)");
	flushSource();
      }	
    }
  }  

  com();
  writeInteger4sc("ienp(NDF)");// real(kind=REAL8)         :: ienp(NDF)
  writeInteger4sc("iedp(NDF)");// real(kind=REAL8)         :: iedp(NDF)
  writeInteger4sc("ikp(NDF)"); // real(kind=REAL8)         :: ikp(NDF)

  // real(kind=REAL8)         :: ea,eb
  EcalElementMatRHSVariableDeclaration(sePtr->GetSolveNo(),
				       sePtr->GetElemNo () );
  comment();

  // common block for ea, eb
  EcalElementMatRHSCommon(sePtr->GetSolveNo(),
			  sePtr->GetElemNo () );
  comment();

  return;
}

// ###

void PM_aistpcp90::doElemStarters()
{
  SourceStarters();
  return;
}

// ###

void PM_aistpcp90::DoElemParameters(SolveElement *sePtr)
{

  COMMENTlong("Problem dependent parameters");
  pushInteger4pm();
  pushSource("NDF = ");
  pushSourceInt(sePtr->GetNdf());
  flushSource();

  pushInteger4pm();
  pushSource("NDP = ");
  pushSourceInt(sePtr->GetIelemNodes());
  flushSource();

  pushInteger4pm();
  pushSource("NDF_NODE =");
  pushSourceInt(sePtr->GetNumberOfUnknowns());
  pushSource("   ! NDF in PCP");
  flushSource();


  for(int i=0;i<sePtr->GetQuadratures();i++) {

    Quadrature *qPtr;
    qPtr = sePtr->GetIthQuadraturePtr(i);

    pushInteger4pm();
    pushSource("NPG");
    pushSourceInt(i+1);
    pushSource(" =  ");
    pushSourceInt(qPtr->GetQuadraturePoints());
    pushSource("  ! No.");
    pushSourceInt(i+1);
    pushSource(" [");
    pushSource(qPtr->GetName());
    pushSource("]");
    flushSource();

  }
  comment();
  return;

}




// ### Initializer 

void PM_aistpcp90::DoElemInitializer(SolveElement *sePtr)
{
  /* data statement for ienp */
  pushSource("data ienp/");
  for(int i=0;i<sePtr->GetNdf();i++) {
    if(i!=0) pushSource(",");
    pushSourceInt(sePtr->GetIthIENP(i));
  }
  pushSource("/");
  flushSource();

  /* data statement for iedp */
  pushSource("data iedp/");
  for(int i=0;i<sePtr->GetNdf();i++) {
    if(i!=0) pushSource(",");
    pushSourceInt(sePtr->GetIthIEDP(i));
  }
  pushSource("/");
  flushSource();

  comment();

  for(int i=0;i<sePtr->GetQuadratures();i++) {
    pushSource("call eset");
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

// ### loop start
  
void PM_aistpcp90::DoElemElementLoopStart(int flag)
{
  writeSource("do i=1,nelem");   
  com();
}


void PM_aistpcp90::DoElemCallEcalRoutine(SolveElement *sePtr,int flag)
{
  int strindex(const char *, const char *);
  orderedPtrList <Variable *> varPtrLst = sePtr->GetVariablePtrLst();
  listIterator <Variable *> itr(varPtrLst);
  
  writeSource("! nodes should have ielem(np,nelems");
  com();
  writeSource("!**** if(ietype .EQ. 1) then");  // P2 limit
  writeSource("  do j=1,np");
  writeSource(                    "    ex(j)=x(ielem(j,i))");
  if(spaceDim > 1) {  writeSource("    ey(j)=y(ielem(j,i))"); }
  if(spaceDim > 2) {  writeSource("    ez(j)=z(ielem(j,i))"); }

  for(itr.init(); !itr;++itr) {
    if(itr()->GetType() == VAR_FEM) {
      pushSource("    efem_");
      pushSource(itr()->GetName());
      pushSource("(j)=fem_");
      pushSource(itr()->GetName());
      pushSource("(ielem(j,i))");
      flushSource();
    }

    // Additional for ewise-fem variable
    if(itr()->GetType() == VAR_EWISE_A) {
      if(itr()->GetEwiseType() == EWISE_TYPE_INTERPOLATION) {
	pushSource("    eew_");
	pushSource(itr()->GetName());
	pushSource("(j)=ew_");
	pushSource(itr()->GetName());
	pushSource("(ielem(j,i))");
	flushSource();
      }
    }
  }  
  writeSource("  end do");
  com();


  // Call ecal routine
  pushSource ("  call ");
  pushEcalRoutineName( sePtr );    // ecal1_1, etc.
  pushSource("(");

  int ielemNodes = sePtr->GetIelemNodes();
  for(int i=0;i<ielemNodes;i++) {
    if(i != 0) pushSource(",");
    pushSource("ex(");
    pushSourceInt(i+1);
    pushSource(")");

    if(spaceDim > 1) {
      pushSource(",ey(");
      pushSourceInt(i+1);
      pushSource(")");
    }

    if(spaceDim > 2) {
      pushSource(",ez(");
      pushSourceInt(i+1);
      pushSource(")");
    }
  }

  // p2 interface
  // list<string> strLst = sePtr->GetEcalCallValueLst();
  //  listIterator <string>itr2(strLst);
  //  
  //  for(itr2.init();!itr2;++itr2) {
  //    pushSource(",");
  //    string a = itr2();
  //    if(strindex(a,"fem_")) { // SUPER LIMITED!!! ECAL P2 OIMO oimo
  //      a = SuperRinjiEcalP2DRAMA(a);
  //    }
  //    pushSource(a);
  //  }

  pushEcalArgumentLstInElem( sePtr, varPtrLst );   //  aistpcp90_ecal.cpp

  pushSource(")");
  flushSource();
  com();

  writeSource(" do j=1,NDF");
  writeSource("   ikp(j) = ipd(ielem(ienp(j),i))+iedp(j)");
  writeSource(" end do");
  com();

  return;
}


void PM_aistpcp90::DoElemElementLoopEnd(int flag)
{
  writeSource("end do   ! for element loop");
  com();
  //  com();
  //  COMMENTlong("Force vector justification");    // comment out (02/12/10)
  //  writeSource("do i=1,neq");
  //  writeSource(" do j=2,nprocs");
  //  writeSource("  NPP(1,i)=NPP(1,i)+NPP(j,i)");
  //  writeSource(" end do");
  //  writeSource("end do");
  //  com();

  //  writeSource("do i=1,neq");
  //  writeSource(" VFG(i)=VFG(i)/DBLE(NPP(1,i))");
  //  writeSource("end do");
  //  com();
  return;
}

void PM_aistpcp90::DoElemReturnSequence(SolveElement *sePtr)
{
  pushSource("end subroutine ");
  pushElemRoutineName(sePtr->GetSolveNo());
  flushSource();

  pushSource("end module mod_");
  pushElemRoutineName(sePtr->GetSolveNo());
  flushSource();
  
  return;
}
