/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 2000
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : feelfem90vec_neumann.cpp
 *  Date     : 2001/11/29 (Copy from feelfem90_neumann.cpp)
 *  Modified : 
 *  
 *  Purpose  : feelfem90 programming style implementation 
 *             
 *
 *  1. I/O related routines
 *
 *
 *
 */

#include "feelfuncs.hpp"

#include "Neumann.hpp"
#include "PM_feelfem90vec.hpp"


// 1. I/O related routine

char *PM_feelfem90vec::GetNeumannRoutineName(int solveNo, int ncondNo)
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

void PM_feelfem90vec::pushNeumannRoutineName(int solveNo, int ncondNo)
{
  char buf[BUFSIZ];
  sprintf(buf,"ncond%d_%d",solveNo,ncondNo);
  pushSource(buf);

  return;
}


// 2. parameter block

void PM_feelfem90vec::DoNeumannParametersPM(Neumann *nPtr)
{
  /* parameter NPG */
  int oimo = nPtr->GetNPG();
  nPtr->check();
  

  COMMENTlong("Neumann parameters (NPG quadrature pts, NDF degree of freedom");

  pushSource("integer,parameter  :: NPG = ");
  pushSourceInt(nPtr->GetNPG());
  flushSource();

  /* parameter NDF */
  pushSource("integer,parameter  :: NDF = ");
  pushSourceInt(nPtr->GetNDF());
  flushSource();

  com();

  return;
}

void PM_feelfem90vec::F90useNeumannPM()
{
  F90useFEMDataType();
  F90useAlways();
}


void PM_feelfem90vec::DoNeumannArgumentVariableDefinitionsPM(Neumann *nPtr)
{
  writeSource("integer,intent(in)                       :: nbedatno");
  writeSource("type(edatList),pointer                   :: firstEdatPtr");
  com();

  writeSource("integer,intent(in)                       :: neq");
  com();

  writeSource("integer,intent(in)                       :: npmax");
  CoordinateVariableDeclaration();
  writeSource("integer,dimension(npmax)                 :: ipf,ipd");
  com();

  // FEM/(EWISE)/SCALAR variables
  orderedPtrList <Variable *> varPtrLst = nPtr->GetVariablePtrLst();
  ArgumentVariableDeclarationLst(varPtrLst);

  return;

}

void PM_feelfem90vec::DoNeumannAutoVariableDefinitionsPM(Neumann *nPtr)
{
  COMMENTlong("auto variables");
  if(nPtr->GetMatNonZero() != 0) {
    writeSource("integer                                  :: i,j,k,l");
    writeSource("integer                                  :: ip,jp");
  }
  else {
    writeSource("integer                                  :: i,j");
  }

  writeSource("integer                                  :: itp");
  writeSource("integer                                  :: iptf,iptt ! for crs");
  com();

  writeSource("integer                                  :: nd");
  writeSource("integer                                  :: nbelem,nbp");
  writeSource("integer                                  :: netype");
  writeSource("integer,dimension(:,:),pointer           :: bielem");
  writeSource("integer,dimension(:),pointer             :: bmatno");
  
  /* variables defined in ncond routine */
  
  switch(getSpaceDimension()) {
  case 1:
    writeSource("real(kind=REAL8)                         :: S");
    writeSource("real(kind=REAL8)                         :: qx");
    break;

  case 2:
    writeSource("real(kind=REAL8),dimension(NPG)          :: gx,w");
    writeSource("real(kind=REAL8)                         :: S,R");
    writeSource("real(kind=REAL8)                         :: dx,dy,ds");
    writeSource("real(kind=REAL8)                         :: qx,qy");
    break;

  case 3:
    writeSource("real(kind=REAL8),dimension(NPG)          :: gx,gy,w");
    writeSource("real(kind=REAL8)                         :: S,R,T");
    writeSource("real(kind=REAL8)                         :: dx,dy,dz,ds");
    writeSource("real(kind=REAL8)                         :: qx,qy,qz");
    break;
  }
  com();

  int testBoundaryPoints = nPtr->GetBoundaryPoints();
  pushSource("real(kind=REAL8)                         :: ");
  for(int i=0;i<testBoundaryPoints;i++) {
    if(i != 0) pushSource(",");
    pushSource("x");
    pushSourceInt(i+1);
  }
  flushSource();

  pushSource("real(kind=REAL8)                         :: ");
  for(int i=0;i<testBoundaryPoints;i++) {
    if(i != 0) pushSource(",");
    pushSource("y");
    pushSourceInt(i+1);
  }
  flushSource();

  if(getSpaceDimension() == 3) {
    pushSource("real(kind=REAL8)                         :: ");
    for(int i=0;i<testBoundaryPoints;i++) {
      if(i != 0) pushSource(",");
      pushSource("z");
      pushSourceInt(i+1);
    }
    flushSource();
  }

  orderedPtrList <Variable *> varPtrLst = nPtr->GetVariablePtrLst();
  listIterator <Variable *>itrvar(varPtrLst);
  for(itrvar.init(); !itrvar; ++itrvar ){
    if(itrvar()->GetType() != VAR_FEM) continue;

    pushSource("real(kind=REAL8)                         :: ");
    for(int i=0;i<testBoundaryPoints;i++) {
      if(i != 0) pushSource(",");
      pushSource(itrvar()->GetName());
      pushSource("_");
      pushSourceInt(i+1);
    }
    flushSource();
  }

  list <char *> testQuadratureArrayLst = nPtr->GetQuadratureArrayLst();
  listIterator <char *> itr(testQuadratureArrayLst);
  for(itr.init();!itr;++itr) {
    pushSource("real(kind=REAL8),dimension(NPG)          :: ");
    pushSource(itr());
    flushSource();
  }
  com();
  
  /* ba,bb related */
  if(nPtr->GetMatNonZero() != 0) {
    writeSource("real(kind=REAL8),dimension(NDF,NDF)      :: ba");
  }

  writeSource("real(kind=REAL8),dimension(NDF)          :: bb");
  writeSource("integer,dimension(NDF)                   :: ikp");
  com();

  /* ienp,iedp */
  writeSource("integer,dimension(NDF)                   :: ienp,iedp");
  com();
  
  int commaflag;

  list <int> testIENPLst = nPtr->GetIENPLst();
  listIterator <int> itr2(testIENPLst);
  commaflag = 0;
  pushSource("data ienp/");
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
  pushSource("data iedp/");
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

void PM_feelfem90vec::DoNeumannInitializerPM(Neumann *nPtr)
{
  int no;

  list <char *> testGXArrayLst = nPtr->GetGXArrayLst();
  list <char *> testWArrayLst  = nPtr->GetWArrayLst();

  listIterator <char *> itr1(testGXArrayLst);
  listIterator <char *> itr2(testWArrayLst );


  COMMENTlong("get boundary EDAT set");
  writeSource("call setP2edat(nbedatno,firstEdatPtr,nbelem,nbp,netype,&");
  writeSource("               bielem,bmatno                            )");
  com();
  
  
  COMMENTlong("Boundary integration initialize");
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
  writeSource("do i=1,NPG");
  com();

  writeSource(" R=gx(i)");

  list <char *>testTermsLeftLst  = nPtr->GetTermsLeftLst();
  list <char *>testTermsRightLst = nPtr->GetTermsRightLst();

  listIterator <char *>itr3(testTermsLeftLst );
  listIterator <char *>itr4(testTermsRightLst);

  com();
  for(itr3.init(),itr4.init(); !itr3; ++itr3,++itr4) {
    pushSource(" ");
    pushSource(itr3());      // this contains (i) in Read77
    pushSource("=");
    pushSource(itr4());
    flushSource();
  }
  com();

  writeSource("end do");
  com();

  return;
}


void PM_feelfem90vec::DoNeumannBoundaryElementLoopStartPM(Neumann *nPtr)
{
  int streq(const char *, const char *);
  int testBoundaryPoints = nPtr->GetBoundaryPoints();
  writeSource("do i=1,nbelem");   // former  do 200 loop
  com();

  com();
  
  for(int i=0;i<testBoundaryPoints;i++) {

    /* value for x test funcs */
    pushSource("  x");
    pushSourceInt(i+1);
    pushSource(" = x(bielem(");
    pushSourceInt(i+1);
    pushSource(",i))");
    flushSource();

    /* value for y test funcs */
    pushSource("  y");
    pushSourceInt(i+1);
    pushSource(" = y(bielem(");
    pushSourceInt(i+1);
    pushSource(",i))");
    flushSource();

    /* value for z test funcs */
    if(getSpaceDimension() == 3) {
      com();
      pushSource("  z");
      pushSourceInt(i+1);
      pushSource(" = z(bielem(");
      pushSourceInt(i+1);
      pushSource(",i))");
      flushSource();
    }
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
    pushSuperDotempneumannFEMval(itrfl(),itrfr());
    /* pushSuperDotempDRAMAneumannFEMval write several lines */
    com();
  }
  comment();
  
  if(nPtr->GetMatNonZero() != 0) {  // this is fixed
    writeSource("  do j=1,NDF");
    writeSource("   do k=1,NDF");
    writeSource("     ba(j,k)=0.0d0");
    writeSource("   end do");
    writeSource("  end do");
    com();
  }

  writeSource("  do j=1,NDF");
  writeSource("   bb(j) = 0.0d0");
  writeSource("  end do");
  com();

  /**/
  writeSource("  do itp =1,NPG");
  com();

  pushSource("   dx=");
  pushSource(nPtr->GetDxFormula());
  flushSource();

  pushSource("   dy=");
  pushSource(nPtr->GetDyFormula());
  flushSource();
  com();

  writeSource("NOT COMPLETE HERE\n");
  //  if(nPtr->GetQxFlag()) {
  //    pushSource("   qx=");
  //    pushSource(nPtr->GetQxFormula());
  //    flushSource();
  //  }

  //  if(nPtr->GetQyFlag()) {
  //    pushSource("   qy=");
  //    pushSource(nPtr->GetQyFormula());
  //    flushSource();
  //  }
  //  com();
  //
  //  writeSource("   ds=sqrt(dx*dx+dy*dy)*w(itp)");
  //  com();

  
  writeSource("BA(*,*) assignment\n");
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
  //      pushSource("   ba(");
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

    pushSource("   bb(");
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
  writeSource("  end do");
  com();


  return;
}
    
void PM_feelfem90vec::DoNeumannBoundaryElementLoopEndPM(Neumann *nPtr)
{
  writeSource(" end do");  // loop 200
  com();
  return;
}

void PM_feelfem90vec::pushSuperDotempneumannFEMval(char *left,char *right)
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

  pushSource("fem_");
  pushSource(fem_var_name);

  pushSource("(bielem(");
  pushSourceInt(number);
  pushSource(",i))");
  flushSource();

  return;
}

void PM_feelfem90vec::DoNeumannReturnSequencePM(Neumann *nPtr)
{
  com();
  pushSource("end subroutine ");
  pushSource(GetNeumannRoutineName(nPtr->GetSolveNo(), nPtr->GetNcondNo()));
  flushSource();
  com();
  
  pushSource("end module mod_");
  pushSource(GetNeumannRoutineName(nPtr->GetSolveNo(), nPtr->GetNcondNo()));
  flushSource();

  return;
}

// END OF NEUMANN RELATED FUNCTIONS
