/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 2000-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : aistpcp90_neumann.cpp
 *  Date     : 2002/06/28 (copy from feelfem90)
 *  Modified : 
 *  
 *  Purpose  : aistpcp90 programming style implementation 
 *             derived from DRAMA double index parallel version
 *
 *  1. I/O related routines
 *
 *
 *
 */

#include "feelfuncs.hpp"

#include "Neumann.hpp"
#include "PM_aistpcp90.hpp"

#include "Quadrature.hpp"

#include "DiscretizedComponent.hpp"

#include "EsetInfo.hpp"
#include "EcalInfo.hpp"

#include "BoundaryElementNodePattern.hpp"


// 1. I/O related routine

char *PM_aistpcp90::GetNeumannRoutineName(int solveNo, int ncondNo)
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

void PM_aistpcp90::pushNeumannRoutineName(int solveNo, int ncondNo)
{
  char buf[BUFSIZ];
  sprintf(buf,"ncond%d_%d",solveNo,ncondNo);
  pushSource(buf);

  return;
}


// 2. parameter block

void PM_aistpcp90::DoNeumannParametersPM(Neumann *nPtr)
{
  /* parameter NPG */
  COMMENTlong("Neumann parameters (NPG quadrature pts, NDF degree of freedom");

  pushInteger4pm();
  pushSource("NPG = ");
  pushSourceInt(nPtr->GetNPG());
  flushSource();

  /* parameter NDF */
  pushInteger4pm();
  pushSource("NDF = ");
  pushSourceInt(nPtr->GetNDF());
  flushSource();

  com();

  return;
}

void PM_aistpcp90::F90useNeumannPM()
{
  F90useFEMDataType();
  F90useAlways();
}


void PM_aistpcp90::DoNeumannArgumentVariableDefinitionsPM(Neumann *nPtr)
{
  //MPI related
  writeInteger4In("myrank,nprocs");    // mpi
  com();

  writeInteger4In("nbedatno");
  writeInteger4Ptr1("IEDOM");          // IEDOM
  writeInteger4In("NDF_PCP");          // NDF restriction in PCP

  writeSource("type(edatList),pointer                  :: firstEdatPtr");
  com();

  writeInteger4In("neq");
  writeInteger4In("npmax");
  CoordinateVariableDeclaration();
  writeInteger4sc("ipf(npmax),ipd(npmax)");
  com();

  // FEM/(EWISE)/SCALAR variables
  orderedPtrList <Variable *> varPtrLst = nPtr->GetVariablePtrLst();
  ArgumentVariableDeclarationLst(varPtrLst);

  return;

}

void PM_aistpcp90::DoNeumannAutoVariableDefinitionsPM(Neumann *nPtr)
{
  COMMENTlong("auto variables");
  if(nPtr->GetMatNonZero() != 0) {
    writeInteger4sc("i,j,k,l");     // integer         :: i,j,k,l
    writeInteger4sc("ip,jp");       // integer         :: ip,jp
  }
  else {
    writeInteger4sc("i,j");         // integer         :: i,j
  }

  writeInteger4sc("itp");           // integer         :: itp
  com();

  writeInteger4sc("nd");            // integer         :: nd
  writeInteger4sc("nbelem,nbp");    // integer         :: nbelem,nbp
  writeInteger4sc("netype");        // integer         :: netype
  writeInteger4Ptr2("bielem");      // integer,dimension(:,:),pointer :: bielem
  writeInteger4Ptr1("bmatno");      // integer,dimension(:),pointer   :: bmatno
  
  /* variables defined in ncond routine */
  
  switch(getSpaceDimension()) {
  case 1:
    break;

  case 2:
    writeReal8sc("gx(NPG),w(NPG)");
    writeReal8sc("dxdr,dydr,ds");
    break;

  case 3:
    writeReal8sc("gx(NPG),gy(NPG),w(NPG)");
    writeReal8sc("dxdr,dxds");
    writeReal8sc("dydr,dyds");
    writeReal8sc("dzdr,dzds");
    writeReal8sc("ds");
    break;
  }
  com();

  if(nPtr->IsUseX()) { writeReal8sc("qx"); }
  if(nPtr->IsUseY()) { writeReal8sc("qy"); }
  if(nPtr->IsUseZ()) { writeReal8sc("qz"); }

  if(nPtr->IsUseNX() || nPtr->IsUseNY() || nPtr->IsUseNZ() ) {
    writeReal8sc("qnx,qny,qnz");
    writeReal8sc("ns");
  }    

  int boundaryIelemNodes = nPtr->GetNodes();
  
  writeSource("! coordinates");

  pushReal8sc();  //   real(kind=REAL8)    ::
  for(int i=0;i<boundaryIelemNodes;i++) {
    if(i != 0) pushSource(",");
    pushSource("x");
    pushSourceInt(i+1);
  }
  flushSource();

  pushReal8sc();  //   real(kind=REAL8)    ::
  for(int i=0;i<boundaryIelemNodes;i++) {
    if(i != 0) pushSource(",");
    pushSource("y");
    pushSourceInt(i+1);
  }
  flushSource();

  if(getSpaceDimension() == 3) {

    pushReal8sc();  //   real(kind=REAL8)    ::
    for(int i=0;i<boundaryIelemNodes;i++) {
      if(i != 0) pushSource(",");
      pushSource("z");
      pushSourceInt(i+1);
    }
    flushSource();
  }
  com();
  
  // known Variables
  orderedPtrList <Variable *> varPtrLst = nPtr->GetVariablePtrLst();
  listIterator <Variable *>itrvar(varPtrLst);

  writeSource("! known variables");
  for(itrvar.init(); !itrvar; ++itrvar ){
    if(itrvar()->GetType() != VAR_FEM) continue;

    pushReal8sc();  //   real(kind=REAL8)    ::
    for(int i=0;i<boundaryIelemNodes;i++) {
      if(i != 0) pushSource(",");
      pushSource(itrvar()->GetName());
      pushSource("_");
      pushSourceInt(i+1);
    }
    flushSource();
  }
  com();

  // Arrays for quadrature
  COMMENTlong("Quadrature terms");
  EcalInfo *ecalInfoPtr = nPtr->GetEcalInfoPtr();
  listIterator <string>itrEset(ecalInfoPtr->GetCommonTermLst());
  for(itrEset.init();!itrEset;++itrEset) {
    pushReal8sc();
    pushSource(itrEset());
    pushSource("(NPG)");
    flushSource();
  }
  com();

  // arrays for integrand terms
  COMMENTlong("Integrand terms");
  listIterator <string>itrVI( nPtr->GetEcalIntegrandTermLst() );
  for(itrVI.init(); !itrVI; ++itrVI) {
    pushReal8sc();
    flushSource(itrVI());
  }  
  com();
  
  /* ba,bb related */
  COMMENTlong("Boundary element matrix and load vector");
  if(nPtr->GetMatNonZero() != 0) {
    pushReal8sc();
    flushSource("ba(NDF,NDF)"); // real(kind=REAL8),dimension(NDF,NDF) :: ba
  }

  pushReal8sc();
  flushSource("bb(NDF)"); //real(kind=REAL8),dimension(NDF) :: bb
  com();

  COMMENTlong("Information arrays");
  pushInteger4sc();
  flushSource("ikp(NDF)");  // integer ikp(NDF)
  com();

  // allocate ienp,iedp
  pushInteger4sc();
  flushSource("ienp(NDF),iedp(NDF)");//integer,dimension(NDF)  :: ienp,iedp
  comment();

  // DATA IENP,IEDP
  int commaflag = 0;
  BoundaryElementNodePattern *benpPtr;
  benpPtr = nPtr->GetBoundaryElementNodePatternPtr();
  
  int totalFreedom = benpPtr->GetTotalFreedom();
  int *ptr;

  // for ienp
  ptr = benpPtr->MakeIENPcopy();
  pushSource("data ienp/");

  for(int i=0;i<totalFreedom;i++) {
    if(commaflag) pushSource(",");
    commaflag = 1;
    pushSourceInt(*(ptr+i));               // ienp data
  }
  pushSource("/");
  flushSource();
  delete [] ptr;

  // for iedp
  ptr = benpPtr->MakeIEDPcopy();
  commaflag = 0;

  pushSource("data iedp/");
  for(int i=0;i<totalFreedom;i++) {
    if(commaflag) pushSource(",");
    commaflag = 1;
    pushSourceInt(*(ptr+i));               // ienp data
  }
  pushSource("/");
  flushSource();
  
  delete [] ptr;
    
  comment();

  return;
}

void PM_aistpcp90::DoNeumannInitializerPM(Neumann *nPtr)
{
  int no;

  COMMENTlong("get boundary EDAT set");
  writeSource("call setP2edat(nbedatno,firstEdatPtr,nbelem,nbp,netype,&");
  writeSource("               bielem,bmatno                            )");
  com();


  //////////////////////////////////////////////////////////////////
  COMMENTlong("Boundary integration intialize");
  Quadrature *qPtr = nPtr->GetQuadraturePtr();
  int points = qPtr->GetQuadraturePoints();
  int dim    = qPtr->GetDimension();

  pushSource("! quadrature method [");
  pushSource(qPtr->GetName());
  pushSource("](");
  pushSourceInt(points);
  pushSource(")");
  flushSource();
  com();

  for(int ip=0;ip<points;ip++) {
    // gx
    pushSource("gx(");
    pushSourceInt( ip+1 );
    pushSource(") =");
    pushSourceDbl( qPtr->GetIthXi( ip ) );
    flushSource();

    // gy
    if(dim > 1) {
      pushSource("gy(");
      pushSourceInt( ip+1 );
      pushSource(") =");
      pushSourceDbl( qPtr->GetIthEta( ip ) );
      flushSource();
    }

    // gz
    if(dim > 2) {
      pushSource("gz(");
      pushSourceInt( ip+1 );
      pushSource(") =");
      pushSourceDbl( qPtr->GetIthZeta( ip ) );
      flushSource();
    }
      
    pushSource(" w(");
    pushSourceInt( ip+1 );
    pushSource(") =");
    pushSourceDbl( qPtr->GetIthWeight( ip ) );
    flushSource();
      
    com();
  }
   
  comment();

  // set quadrature values
  writeSource("do itp=1,NPG");
  com();

  EcalInfo *ecalInfoPtr = nPtr->GetEcalInfoPtr();
  listIterator <EcalEvalPair *>itrEEP( ecalInfoPtr->GetEcalEvalPairPtrLst());
  for(itrEEP.init(); !itrEEP ; ++itrEEP) {
    Element *bePtr    = itrEEP()->GetElementPtr();   // Boundary element
    int      diffType = itrEEP()->GetType();         // differential type
    
    doNeumannEsetCalcInterpolationSub( nPtr, bePtr, diffType);
  }
  com();

  writeSource("end do");
  com();

  return;
}


void PM_aistpcp90::DoNeumannBoundaryElementLoopStartPM(Neumann *nPtr)
{
  int streq(const char *, const char *);


  int boundaryNodes = nPtr->GetNodes();
  writeSource("do i=1,nbelem");   // former  do 200 loop

  // PCP loop
  writeSource(" if(IEDOM(bmatno(i)) == myrank) then");


  com();

  for(int i=0;i<boundaryNodes;i++) {

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

  // Set known FEM vars in boundary
  orderedPtrList <Variable *> varPtrLst = nPtr->GetVariablePtrLst();
  listIterator <Variable *>itrvar(varPtrLst);

  writeSource("! known variables");
  for(itrvar.init(); !itrvar; ++itrvar ){
    if(itrvar()->GetType() == VAR_EWISE   ||
       itrvar()->GetType() == VAR_EWISE_A ||
       itrvar()->GetType() == VAR_VFEM        ) {
      cerr << "EWISE,VFEM in boundary is not implemented." << endl;
      abortExit("Not implemented functionality used.");
    }
    if(itrvar()->GetType() != VAR_FEM) continue;  // for scalar vars

    // element var only
    Element *ePtr  = itrvar()->GetElementPtr();
    Element *bePtr = ePtr->AcquireBoundaryElementPtr();

    int *ndPattern  = nPtr->GetNodePatternForEcal( bePtr );
    int  femFreedom = bePtr->GetElementFreedom();
    for(int i=0;i<femFreedom;i++) {

      // known fem varaible set 
      pushSource("  ");
      pushSource(itrvar()->GetName());
      pushSource("_");
      pushSourceInt(i+1);
      pushSource(" = ");
      pushSource("fem_"); pushSource(itrvar()->GetName());
      pushSource("(bielem(");
      pushSourceInt(*(ndPattern + i));
      pushSource(",i))");
      flushSource();
    }
    com();
  }
  com();

  

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
  
  if(nPtr->GetMatNonZero() != 0) {  
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

  // quadrature loop
  writeSource("  do itp =1,NPG");
  com();


  switch(nPtr->GetSpaceDimension()) {
  case 1:
    abortExit("Not implemented 1dim neumann cond.");
    break;

  case 2:
    pushSource("   dxdr=");
    pushNeumannCoordDiff( nPtr, "x","x");    // first is real, second is ref
    flushSource();
    
    pushSource("   dydr=");
    pushNeumannCoordDiff( nPtr, "y","x");
    flushSource();

    writeSource("   ds  = sqrt(dxdr*dxdr + dydr*dydr) * w(itp)");
    break;


  case 3:
    pushSource("   dxdr=");
    pushNeumannCoordDiff( nPtr,"x","x");
    flushSource();

    pushSource("   dxds=");
    pushNeumannCoordDiff( nPtr,"x","y");
    flushSource();
    com();

    pushSource("   dydr=");
    pushNeumannCoordDiff( nPtr,"y","x");
    flushSource();

    pushSource("   dyds=");
    pushNeumannCoordDiff( nPtr,"y","y");
    flushSource();
    com();

    pushSource("   dzdr=");
    pushNeumannCoordDiff( nPtr,"z","x");
    flushSource();

    pushSource("   dzds=");
    pushNeumannCoordDiff( nPtr,"z","y");
    flushSource();

    com();

    writeSource("   ds  =sqrt((dydr*dzds-dyds*dzdr)**2 +           &");
    writeSource("             (dzdr*dxds-dzds*dxdr)**2 +           &");
    writeSource("             (dxdr*dyds-dxds*dydr)**2   )*w(itp)");
    break;

  default:
    assert(1==0);
  }
  com();

  // set qx,qy,qz, nx,ny,nz
  doNeumannEcalSetValAtGaussP( nPtr);
  com();


  // ba,bb block

  EcalInfo *ecalInfoPtr       = nPtr->GetEcalInfoPtr();
  DiscretizedComponent *dcPtr = nPtr->GetDiscretizedComponentPtr();

  // ba
  if(nPtr->GetMatNonZero() != 0) {  

    int rows    = dcPtr->GetRows();
    int columns = dcPtr->GetColumns();
  
    for(int i=0;i<rows;i++) {
      for(int j=0; j< columns; j++) {
	
	if(dcPtr->IsZeroMatCoeff(i+1,j+1)) {
	  pushSource("!  ba(");      
	  pushSourceInt(i+1);
	  pushSource(",");
	  pushSourceInt(j+1);
	  pushSource(") is ");
	  pushSourceHAT(dcPtr->GetElementMatIJ(i+1,j+1));  //conversion ^ -> **
	  flushSource();
	}
	else {
	  pushSource("   ba(");
	  pushSourceInt(i+1);
	  pushSource(",");
	  pushSourceInt(j+1);
	  pushSource(")=ba(");
	  pushSourceInt(i+1);
	  pushSource(",");
	  pushSourceInt(j+1);
	  pushSource(")+(");
	
	  pushSourceHAT(dcPtr->GetElementMatIJ(i+1,j+1)); //conversion ^ -> **
	  flushSource(")*ds");
	}
      }
      com();
    }
  }     // end of ba block
  com();

  //bb block
  int rows    = dcPtr->GetRows();
  for(int i=0;i<rows;i++) {
    if(dcPtr->IsZeroRHSVec( i+1 ) == YES) {
      pushSource("!  bb(");
      pushSourceInt(i+1);
      pushSource(") is ");
      pushSourceHAT(dcPtr->GetElementLoadI(i+1));   // conversion ^ -> **
      flushSource();
    }
    else {
      pushSource("   bb(");
      pushSourceInt(i+1);
      pushSource(")=bb(");
      pushSourceInt(i+1);
      pushSource(")+(");
      pushSourceHAT(dcPtr->GetElementLoadI(i+1));   // conversion ^ -> **
      flushSource(")*ds");
    }
  }
  com();

  // end of numerical integration
  writeSource("  end do    ! itp loop");
  com();

  return;
}
    
void PM_aistpcp90::DoNeumannBoundaryElementLoopEndPM(Neumann *nPtr)
{
  // for IEDOM(bmatno(i)) == myrank
  writeSource(" end if  ! for IEDOM and myrank if block"); 

  writeSource("end do");  // loop 200 (
  com();
  return;
}

void PM_aistpcp90::pushSuperDotempneumannFEMval(char *left,char *right)
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

void PM_aistpcp90::DoNeumannReturnSequencePM(Neumann *nPtr)
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


void PM_aistpcp90::doNeumannEsetCalcInterpolationSub(Neumann *nPtr,
						     Element *bePtr,
						     int      diffType   )
{
  int freedom = bePtr->GetElementFreedom();  // must be boundary element
  
  // Make TermConvert

  TermConvert tc;

  char buf[38];

  // for r  ===> _m1
  sprintf(buf,"gx(itp)");
  tc.StoreMetaPair( "r" , buf);

  // for s  ===> _m2
  sprintf(buf,"gy(itp)");
  tc.StoreMetaPair( "s" , buf);

  // for t  ===> _m3
  sprintf(buf,"gz(itp)");
  tc.StoreMetaPair( "t" , buf);


  for(int i=0;i<freedom;i++) {

    int bno = bePtr->GetIthOriginalIplus1( i );
    Interpolation *iPtr = bePtr->GetIthInterpolationPtr(bno-1);

    pushSource("  ");
    pushSource("r");
    pushSource(bePtr->GetName());
    pushSource("_");
    pushSourceInt(bno);               // boundary 

    switch(diffType) {

    case TYPE_DIFF_ZERO:
      break;

    case TYPE_DIFF_X:
      pushSource("_x");
      break;

    case TYPE_DIFF_Y:
      pushSource("_y");
      break;

    case TYPE_DIFF_Z:
      pushSource("_z");
      break;

    default:
      assert(1==0);
    }

    pushSource("(itp)=");

    string exprStrForGinac = tc.convertExpressionString(iPtr->GetExprString());

    void esetDerivative(char *,int,char *,int);
    char exprBuf[MAX_FORMULA_BUF];

    switch(diffType) {
    case TYPE_DIFF_ZERO:
      exprStrForGinac = tc.ReverseConvertExpressionString(exprStrForGinac);
      break;

    case TYPE_DIFF_X:
    case TYPE_DIFF_Y:
    case TYPE_DIFF_Z:
      esetDerivative( exprStrForGinac, diffType, exprBuf,MAX_FORMULA_BUF );
      exprStrForGinac = tc.ReverseConvertExpressionString(exprBuf);
      break;

    default:
      assert(1==0);
    }

    pushSourceHAT(exprStrForGinac);
    flushSource();
  }

  return;
}

void PM_aistpcp90::doNeumannEcalSetValAtGaussP( Neumann *nPtr )
{
  DiscretizedComponent *dcPtr        = nPtr->GetDiscretizedComponentPtr();
  EcalInfo             *ecalInfoPtr  = nPtr->GetEcalInfoPtr();
  //Element              *paraEPtr     = nPtr->GetParametricElementPtr();
  //Element              *bparaEPtr    = paraEPtr->AcquireBoundaryElementPtr();
  
  comment();

  // for qx,qy,qz
  if(nPtr->IsUseX() == YES) {
    pushSource("   qx=");
    pushNeumannEcalCoordSub(nPtr, "x");
    flushSource();
  }
  if(nPtr->IsUseY() == YES) {
    pushSource("   qy=");
    pushNeumannEcalCoordSub(nPtr, "y");
    flushSource();
  }
  if(nPtr->IsUseZ() == YES) {
    pushSource("   qz=");
    pushNeumannEcalCoordSub(nPtr, "z");
    flushSource();
  }

  if(nPtr->IsUseX() == YES ||
     nPtr->IsUseY() == YES ||
     nPtr->IsUseZ() == YES   ){
    com();
  }

  // nx,ny,nz is not yet.....
  if(nPtr->IsUseNX() == YES ||
     nPtr->IsUseNY() == YES ||
     nPtr->IsUseNZ() == YES   ){

    switch(nPtr->GetSpaceDimension()) {
    case 2:
      writeSource("   qnx = -dydr");
      writeSource("   qny =  dxdr");
      writeSource("   ns  =  sqrt(qnx*qnx+qny*qny)");
      writeSource("   qnx =  qnx/ns");
      writeSource("   qny =  qny/ns");
      break;

    case 3:
      writeSource("   qnx = dydr*dzds-dyds*dzdr");
      writeSource("   qny = dzdr*dxds-dzds*dxdr");
      writeSource("   qnz = dxdr*dyds-dxds*dydr");
      writeSource("   ns  = sqrt(qnx*qnx+qny*qny+qnz*qnz)");
      writeSource("   qnx = -qnx/ns");                         // minus
      writeSource("   qny = -qny/ns");                         // minus
      writeSource("   qnz = -qnz/ns");                         // minus
      break;

    default:
      assert(1==0);
    }
    com();
  }  
  

  comment();

  // for integrands (FEM variables)
  string term;
  listIterator <Element *>itrE(dcPtr->GetUsedElementPtrList());

  for(itrE.init(); !itrE ; ++itrE) {
    char buf[TERM_LENGTH];    // defined in DiscretizedComponent.hpp =256
    int freedom;

    freedom = itrE()->GetElementFreedom();

    // function itself
    for(int i=0;i<freedom;i++) {
      sprintf(buf,"q%s_%d",itrE()->GetName(), i+1);
      term = buf;

      if(dcPtr->IsUsedIntegrandTerm( term )) {
	
	pushSource("   q");
	pushSource(itrE()->GetName());
	pushSource("_");
	pushSourceInt(i+1);

	pushSource("= r");
	pushSource(itrE()->GetName());
	pushSource("_");
	pushSourceInt(i+1);
	flushSource("(itp)");
      }
    }

    // function dx
    for(int i=0;i<freedom;i++) {
      sprintf(buf,"q%s_%d_x",itrE()->GetName(), i+1);
      term = buf;

      if(dcPtr->IsUsedIntegrandTerm( term )) {

	cerr << "NOT IMPLEMENTED BOUNDARY DIFFERENTIAL TERM\n";
	assert(1==0);
	
	//neumann pushEcalDiffSub_1st(quadNo,itrE(),spaceDim,i+1,TYPE_DIFF_X);
	//flushSource();
      }
    }

    // function itself  dy
    for(int i=0;i<freedom;i++) {
      sprintf(buf,"q%s_%d_y",itrE()->GetName(), i+1);
      term = buf;

      if(dcPtr->IsUsedIntegrandTerm( term )) {

	cerr << "NOT IMPLEMENTED BOUNDARY DIFFERENTIAL TERM\n";
	assert(1==0);

	//neumann pushEcalDiffSub_1st(quadNo,itrE(),spaceDim,i+1,TYPE_DIFF_Y);
	//	flushSource();
      }	
    }
    
    // function itself  dz
    if(spaceDim == 3) {
      for(int i=0;i<freedom;i++) {
	sprintf(buf,"q%s_%d_z",itrE()->GetName(), i+1);
	term = buf;

	if(dcPtr->IsUsedIntegrandTerm( term )) {

	  cerr << "NOT IMPLEMENTED BOUNDARY DIFFERENTIAL TERM\n";
	  assert(1==0);
	
	  //neumannpushEcalDiffSub_1st(quadNo,itrE(),spaceDim,i+1,TYPE_DIFF_Z);
	  //	  flushSource();
	}
      }
    }
  }  
  return;

}

void PM_aistpcp90::pushNeumannEcalCoordSub(Neumann    *nPtr,
					   const char *coord)
{
  Element  *paraElemPtr = nPtr->GetParametricElementPtr();
  Element *bparaElemPtr = paraElemPtr->AcquireBoundaryElementPtr();

  int  freedom;
  int *ndPattern;
  
  freedom   = bparaElemPtr->GetElementFreedom();
  ndPattern = nPtr->GetNodePatternForEcal(bparaElemPtr);

  for(int i=0;i<freedom;i++) {

    int bno = bparaElemPtr->GetIthOriginalIplus1( i );

    if(i != 0) {
      pushSource("+");
    }
    pushSource(coord);                // x
    pushSourceInt(*(ndPattern+i));   // 2
    pushSource("*");                 // *
    pushSource("r");                 // r
    pushSource(paraElemPtr->GetName());     // P1
    pushSource("_");                 // _
    pushSourceInt(bno);              // 2     
    pushSource("(itp)");
  }

  delete [] ndPattern;

  return;
}

void PM_aistpcp90::pushNeumannCoordDiff(Neumann *nPtr,
					const char *dx,const char *dr)
{
  Element *paraElemPtr  = nPtr->GetParametricElementPtr();
  Element *bparaElemPtr = paraElemPtr->AcquireBoundaryElementPtr();

  int  freedom = bparaElemPtr->GetElementFreedom();
  int *ndPattern = nPtr->GetNodePatternForEcal(bparaElemPtr);
  for(int i=0;i<freedom;i++) {

    int bno = bparaElemPtr->GetIthOriginalIplus1( i );
    if(i != 0) {
      pushSource("+");
    }
    pushSource(dx);                  // x
    pushSourceInt(*(ndPattern+i));   // 2
    pushSource("*");                 // *
    pushSource("r");                 // r
    pushSource(paraElemPtr->GetName());     // P1
    pushSource("_");                 // _
    pushSourceInt(bno);              // 2     
    pushSource("_");
    pushSource(dr);
    pushSource("(itp)");
  }
  delete [] ndPattern;

  return;
}


void PM_aistpcp90::doIthNeumannCallInSolvePM(Solve *solvePtr, int i)
{
  // called from MT_ff90XXXX  DoSolveCallLinearNeumannData

  comment();
  pushSource("! No.");
  pushSourceInt(i+1);
  flushSource();
  com();
  
  pushSource("bdatSetPtr => solveInfoPtr%nlst(");
  pushSourceInt(i+1);
  pushSource(")");
  flushSource();
  com();

  writeSource("do i=1,bdatSetPtr%nofsets");
  com();

  writeSource("  no = bDatSetPtr%datlist(i)");
  pushSource("  call ");
  pushNeumannRoutineName(solvePtr->GetSolveNo(),i+1);
  pushSource("(myrank,nprocs,no,IEDOM,NDF_PCP,firstEdatPtr, &");
  flushSource();

  pushSource("     npmax,");
  pushCoordinateSource();
  pushSource(",ipf,ipd                             &");
  flushSource();  

  pushSource("    ");
  /* Additional variables */
  orderedPtrList<Variable *>varPtrLst = solvePtr->GetIthNeumannVariablePtrLst(i);
  listIterator <Variable *>itr(varPtrLst);

  /* Domain variables */
  pushVariableListInSolve( varPtrLst );

  return;
}

void PM_aistpcp90::doIthNeumannCallInSolvePM2(Solve *solvePtr, int i)
{
  writeSource("end do");
  com();
}
  

// END OF NEUMANN RELATED FUNCTIONS
