/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999,2000
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : feelfem90vec_elem.cpp
 *  Date     : 2000/11/29 (copy from feelfem90_elem.cpp)
 *  Modified : 
 *  
 *  Purpose  : elem related routine generator for feelfem90vec model
 *  
 *  1. I/O related. (get/push routine name)
 *  
 *  
 */
#include "feelfuncs.hpp"

#include "Quadrature.hpp"
#include "PM_feelfem90vec.hpp"
#include "ElemGeneratorTemplate.hpp"


// 0. Special rinji routines

string PM_feelfem90vec::SuperRinjiEcalP2DRAMA(const  char *s)
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

char *PM_feelfem90vec::GetElemRoutineName( int solveNo )
{
  int length = stringLength("velem?");
  if(solveNo > 9) {
    length++;
    if(solveNo >99) {
      cerr <<"solve number too large(GetElemRoutineName)\n";
      abortExit(1);
    }
  }

  char *ptr = new char[length];

  sprintf(ptr,"velem%d",solveNo);

  return(ptr);
}

void PM_feelfem90vec::pushElemRoutineName(int solveNo)
{
  char *ptr;
  ptr = GetElemRoutineName(solveNo);
  pushSource(ptr);
  delete ptr;

  return;
}

// ###  Variable definitons
void PM_feelfem90vec::DoElemDeclareArgumentVariablesPM(SolveElement *sePtr)
{
  writeSource("integer,dimension(:,:),pointer    :: ielem");
  writeSource("integer,dimension(:),pointer      :: matno");
  writeSource("integer,intent(in)                :: nelem,np");
  CoordinateVariableDeclaration();
  writeSource("integer,dimension(:),pointer      :: ipf,ipd");
  writeSource("integer,intent(in)                :: npmax");
  writeSource("integer,intent(in)                :: neq");
  com();

  // fem,ewise,scalar variables
  orderedPtrList <Variable *> varPtrLst = sePtr->GetVariablePtrLst();
  ArgumentVariableDeclarationLst(varPtrLst);
  com();

  return;
}


void PM_feelfem90vec::DoElemVariableDefinitionsPM(SolveElement *sePtr)
{
  int strindex(const char *, const char *);
  orderedPtrList <Variable *> varPtrLst = sePtr->GetVariablePtrLst();
  listIterator <Variable *> itr(varPtrLst);

  COMMENTlong("Auto variables");
  writeSource("integer                           :: i,j,k,l");
  writeSource("integer                           :: ip,jp");
  writeSource("integer                           :: iptf,iptt");

  writeSource("real(kind=REAL8),dimension(NDP) :: ex,ey");
  for(itr.init(); !itr;++itr) {
    if(itr()->GetType() == VAR_FEM) {
      pushSource("real(kind=REAL8),dimension(NDP) :: efem_");
      pushSource(itr()->GetName());
      flushSource();
    }
  }  
  com();


  COMMENTlong("Arrays for vector processing");

  writeSource("real(kind=REAL8),dimension(:,:,:),pointer :: ea");
  writeSource("real(kind=REAL8),dimension(:,:)  ,pointer :: eb");
  com();

  switch(getSpaceDimension()) {
  case 1:
    writeSource("! 1D is not supported.");
    break;
    
  case 2:
    writeSource("real(kind=REAL8),dimension(:,:)  ,pointer :: rj11,rj12");
    writeSource("real(kind=REAL8),dimension(:,:)  ,pointer :: rj21,rj22");
    com();

    writeSource("real(kind=REAL8),dimension(:,:)  ,pointer :: rij11,rij12");
    writeSource("real(kind=REAL8),dimension(:,:)  ,pointer :: rij21,rij22");
    com();

    writeSource("real(kind=REAL8),dimension(:,:)  ,pointer :: det");
    com();
    break;

  case 3:
    writeSource("real(kind=REAL8),dimension(:,:)  ,pointer :: rj11,rj12,rj13");
    writeSource("real(kind=REAL8),dimension(:,:)  ,pointer :: rj21,rj22,rj23");
    writeSource("real(kind=REAL8),dimension(:,:)  ,pointer :: rj31,rj32,rj33");
    com();

    writeSource("real(kind=REAL8),dimension(:,:)  ,pointer :: rij11,rij12,rij13");
    writeSource("real(kind=REAL8),dimension(:,:)  ,pointer :: rij21,rij22,rij23");
    writeSource("real(kind=REAL8),dimension(:,:)  ,pointer :: rij31,rij32,rij33");
    com();

    writeSource("real(kind=REAL8),dimension(:,:)  ,pointer :: det");    
    com();
    break;

  default:
    writeSource("ERR");
    break;
  }

  //  pushSource("common /em");
  //  pushSourceInt(sePtr->GetSolveNo());
  //  pushSource("_");
  //  pushSourceInt(sePtr->GetElemNo());
  //  pushSource("/ ea(NDF,NDF),eb(NDF)");
  //  flushSource();
  //  comment();

  return;
}

// ###

void PM_feelfem90vec::doElemStarters()
{
  SourceStarters();
  return;
}

// ###

void PM_feelfem90vec::DoElemParameters(SolveElement *sePtr)
{

  COMMENTlong("Problem dependent parameters");
  pushSource("integer,parameter       :: NDF = ");
  pushSourceInt(sePtr->GetNdf());
  flushSource();

  pushSource("integer,parameter       :: NDP = ");
  pushSourceInt(sePtr->GetIelemNodes());
  flushSource();



  for(int i=0;i<sePtr->GetQuadratures();i++) {

    Quadrature *qPtr;
    qPtr = sePtr->GetIthQuadraturePtr(i);

    pushSource("integer,parameter       :: NPG");
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

void PM_feelfem90vec::DoElemInitializer(SolveElement *sePtr)
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


  // allocate nelem*[element element stiffness] array
  writeSource("!-------------------------------------------");
  writeSource("! allocate all element-wise stiffness matrix");
  writeSource("!-------------------------------------------");

  writeSource("allocate(ea(nelem,NDF,NDF),eb(nelem,NDF))");
  com();

  // allocate Jacobi matrix
  
  writeSource("! Jacobi matrix allocation");
  switch(getSpaceDimension()) {
  case 1:
    writeSource(" NOW feelfem90vec_elem.cpp for 1D is not supported.");
    break;

    
  case 2:
    writeSource("allocate(rj11(nelem),rj12(nelem))");
    writeSource("allocate(rj21(nelem),rj22(nelem))");
    com();
    writeSource("allocate(rij11(nelem),rij12(nelem))");
    writeSource("allocate(rij21(nelem),rij22(nelem))");
    com();
    writeSource("allocate(det(nelem))");
    com();

    break;

  case 3:
    writeSource("allocate(rj11(nelem),rj12(nelem),rj13(nelem))");
    writeSource("allocate(rj21(nelem),rj22(nelem),rj23(nelem))");
    writeSource("allocate(rj31(nelem),rj32(nelem),rj33(nelem))");
    com();

    writeSource("allocate(rij11(nelem),rij12(nelem),rij13(nelem))");
    writeSource("allocate(rij21(nelem),rij22(nelem),rij23(nelem))");
    writeSource("allocate(rij31(nelem),rij32(nelem),rij33(nelem))");
    com();

    writeSource("allocate(det(nelem))");
    com();

    break;

  default:
    cerr << "NEVER COME... feelfem90vec_elem.cpp\n";
    break;
  }


  return;
}

// ### loop start
  
void PM_feelfem90vec::DoElemQuadratureLoopStart
(SolveElement *solveElementPtr,int quadNo)
{
  COMMENTlong("Quadrature loop");

  pushSource("do itp=1,NPG");         // just this!  ^^;
  pushSourceInt(quadNo + 1);
  pushSource("   ! Quadrature No.");
  pushSourceInt(quadNo + 1);
  flushSource();
  com();

  return;
}

void PM_feelfem90vec::DoElemQuadLoopPreparation(SolveElement *sePtr,int quadNo)
{
  switch(getSpaceDimension()) {
  case 1:
    writeSource(" NOW feelfem90vec_elem.cpp for 1D is not supported.");
    break;
    
  case 2:
    writeSource("  do j=1,nelem");
    com();

    writeSource("     rj11(j)=x(ielem(1,j))*qP1_1_x_1(itp)+   &");
    writeSource("     x(ielem(2,j))*qP1_2_x_1(itp)+   &");
    writeSource("     x(ielem(3,j))*qP1_3_x_1(itp)");
    com();
    
    writeSource("     rj21(j)=x(ielem(1,j))*qP1_1_y_1(itp) + &");
    writeSource("     x(ielem(2,j))*qP1_2_y_1(itp) + &");
    writeSource("     x(ielem(3,j))*qP1_3_y_1(itp)");
    com();
    
    writeSource("  end do");
    com();
    com();

    writeSource("  do j=1,nelem");
    com();

    writeSource("     rj12(j)=y(ielem(1,j))*qP1_1_x_1(itp) + &");
    writeSource("     y(ielem(2,j))*qP1_2_x_1(itp) + &");
    writeSource("     y(ielem(3,j))*qP1_3_x_1(itp)");
    com();

    writeSource("     rj22(j)=y(ielem(1,j))*qP1_1_y_1(itp) + &");
    writeSource("     y(ielem(2,j))*qP1_2_y_1(itp) + &");
    writeSource("     y(ielem(3,j))*qP1_3_y_1(itp)");
    writeSource("  end do");
    com();
    
    writeSource("  do j=1,nelem");
    writeSource("     det(j) = rj11(j)*rj22(j)-rj12(j)*rj21(j)");
    writeSource("  end do");
    com();

    writeSource("  do j=1,nelem");
    writeSource("     rij11(j)= rj22(j)/det(j)");
    writeSource("     rij22(j)= rj11(j)/det(j)");
    writeSource("     rij12(j)=-rj12(j)/det(j)");
    writeSource("     rij21(j)=-rj21(j)/det(j)");
    writeSource("  end do");
    com();

    break;
    

  case 3:
    com();
    writeSource("  do j=1,nelem");
    com();

    writeSource("     rj11(j)=x(ielem(1,j))*qP1_1_x_1(itp)+   &");
    writeSource("     x(ielem(2,j))*qP1_2_x_1(itp)+   &");
    writeSource("     x(ielem(3,j))*qP1_3_x_1(itp)");
    com();
    
    writeSource("     rj21(j)=x(ielem(1,j))*qP1_1_y_1(itp) + &");
    writeSource("     x(ielem(2,j))*qP1_2_y_1(itp) + &");
    writeSource("     x(ielem(3,j))*qP1_3_y_1(itp)");
    com();

    writeSource("     rj31(j)=x(ielem(1,j))*qP1_1_y_1(itp) + &");
    writeSource("     x(ielem(2,j))*qP1_2_y_1(itp) + &");
    writeSource("     x(ielem(3,j))*qP1_3_y_1(itp)");
    com();
    
    writeSource("  end do");
    com();
    com();

    writeSource("  do j=1,nelem");
    com();

    writeSource("     rj12(j)=y(ielem(1,j))*qP1_1_x_1(itp) + &");
    writeSource("     y(ielem(2,j))*qP1_2_x_1(itp) + &");
    writeSource("     y(ielem(3,j))*qP1_3_x_1(itp)");
    com();

    writeSource("     rj22(j)=y(ielem(1,j))*qP1_1_y_1(itp) + &");
    writeSource("     y(ielem(2,j))*qP1_2_y_1(itp) + &");
    writeSource("     y(ielem(3,j))*qP1_3_y_1(itp)");
    com();

    writeSource("     rj32(j)=y(ielem(1,j))*qP1_1_z_1(itp) + &");
    writeSource("             y(ielem(2,j))*qP1_2_z_1(itp) + &");
    writeSource("             y(ielem(3,j))*qP1_3_z_1(itp)");
    writeSource("  end do");
    com();
    com();


    // 3D Jacobian on z
    writeSource("  do j=1,nelem");
    com();

    writeSource("     rj13(j)=z(ielem(1,j))*qP1_1_x_1(itp) + &");
    writeSource("     z(ielem(2,j))*qP1_2_x_1(itp) + &");
    writeSource("     z(ielem(3,j))*qP1_3_x_1(itp)");
    com();

    writeSource("     rj23(j)=z(ielem(1,j))*qP1_1_y_1(itp) + &");
    writeSource("     z(ielem(2,j))*qP1_2_y_1(itp) + &");
    writeSource("     z(ielem(3,j))*qP1_3_y_1(itp)");
    com();

    writeSource("     rj33(j)=z(ielem(1,j))*qP1_1_y_1(itp) + &");
    writeSource("     z(ielem(2,j))*qP1_2_y_1(itp) + &");
    writeSource("     z(ielem(3,j))*qP1_3_y_1(itp)");
    writeSource("  end do");
    com();

    // 3D determinant
    writeSource("  do j=1,nelem");
    writeSource("     det(j) =   rj11(j)*rj22(j)*rj33(j)  &");
    writeSource("              + rj12(j)*rj23(j)*rj31(j)  &");
    writeSource("              + rj13(j)*rj21(j)*rj32(j)  &");

    writeSource("              - rj11(j)*rj23(j)*rj32(j)  &");
    writeSource("              - rj12(j)*rj21(j)*rj33(j)  &");
    writeSource("              - rj13(j)*rj22(j)*rj31(j)");
    writeSource("  end do");
    com();

    writeSource("  do j=1,nelem");
    writeSource("     detinv  = 1.0d0  /det(j)");

    writeSource("     rij11(j)=   detinv * (rj22(j)*rj33(j)-rj23(j)*rj32(j))");
    writeSource("     rij12(j)= - detinv * (rj12(j)*rj33(j)-rj13(j)*rj32(j))");
    writeSource("     rij13(j)=   detinv * (rj21(j)*rj23(j)-rj13(j)*rj22(j))");

    writeSource("     rij21(j)= - detinv * (rj21(j)*rj33(j)-rj23(j)*rj31(j))");
    writeSource("     rij22(j)=   detinv * (rj11(j)*rj33(j)-rj13(j)*rj31(j))");
    writeSource("     rij23(j)= - detinv * (rj11(j)*rj23(j)-rj13(j)*rj21(j))");

    writeSource("     rij31(j)=   detinv * (rj21(j)*rj32(j)-rj22(j)*rj31(j))");
    writeSource("     rij32(j)= - detinv * (rj11(j)*rj32(j)-rj12(j)*rj31(j))");
    writeSource("     rij33(j)=   detinv * (rj11(j)*rj22(j)-rj12(j)*rj21(j))");

    writeSource("  end do");
    com();

    break;


  default:
    break;

  }
  comment();

}

void PM_feelfem90vec::
    DoElemQuadLoopMakeAllElement(SolveElement *sePtr,int quadNo)
{
  com();
  com();
  com();

  return;
}


void PM_feelfem90vec::DoElemQuadratureLoopEnd
(SolveElement *solveElementPtr,int quadNo)
{
  pushSource("end do  ! Quadrature No.");
  pushSourceInt(quadNo + 1);
  flushSource();
  com();
  com();

  return;
}


void PM_feelfem90vec::DoElemReturnSequence(SolveElement *sePtr)
{

  com();
  com();
  pushSource("end subroutine ");
  pushElemRoutineName(sePtr->GetSolveNo());
  flushSource();

  pushSource("end module mod_");
  pushElemRoutineName(sePtr->GetSolveNo());
  flushSource();
  
  return;
}
