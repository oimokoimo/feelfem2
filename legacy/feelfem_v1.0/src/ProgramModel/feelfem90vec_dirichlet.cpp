/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 2000
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : feelfem90vec_dirichlet.cpp
 *  Date     : 2001/11/29 (copy from feelfem90_dirichlet.cpp)
 *  Modified : 
 *  
 *  Purpose  : feelfem90 programming style implementation 
 *             scalar model (derived from DRAMA double index parallel version)
 *
 *             DIRICHLET related generator routines
 */

#include "feelfuncs.hpp"
#include "Dirichlet.hpp"
#include "PM_feelfem90vec.hpp"

// Routine name

void PM_feelfem90vec::pushDirichletRoutineName(int solveNo, int dcondNo)
{
  char buf[BUFSIZ];
  sprintf(buf,"dcond%d_%d",solveNo,dcondNo);
  pushSource(buf);

  return;

}

void PM_feelfem90vec::F90useDirichletPM()
{
  F90useFEMDataType();
  F90useAlways();
}

//////////////////////////////////////////
// Dirichlet Conditions related functions
//////////////////////////////////////////
char *PM_feelfem90vec::dirichletP2DOTEMP( char *st )
{
  int strindex(const char *,const char *);
  int i;
  static char buf[BUFSIZ];
  for(i=0;*st != '\0'; i++) {
    buf[i] = *st;
    st++;
  }
  buf[i] = '\0';
  
  int n;
  while( n = strindex(buf,"(ip)")) {
    buf[n-1] = '_';
    buf[n  ] = 'd';
    buf[n+1] = 'p';
    buf[n+2] = 't';
  }

  return(buf);
}


char *PM_feelfem90vec::GetDirichletRoutineName(int solveNo, int dcondNo)
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


void PM_feelfem90vec::DoDirichletArgumentVariableDefinitionsPM(Dirichlet *dPtr)
{
  writeSource("integer,intent(in)           :: nsetno");
  writeSource("type(nsetList),pointer  :: firstNsetPtr");
  com();

  writeSource("integer,intent(in)           :: neq");
  com();

  writeSource("integer,intent(in)           :: npmax");
  CoordinateVariableDeclaration();
  writeSource("integer,dimension(npmax)     :: ipf,ipd");
  com();
  
  orderedPtrList <Variable *> varPtrLst = dPtr->GetVariablePtrLst();
  ArgumentVariableDeclarationLst(varPtrLst);

  return;
}

void PM_feelfem90vec::doDirichletAutoVariableDefinitionsPM(Dirichlet *dPtr)
{
  COMMENTlong(" auto variables for dirichlet");
  writeSource("integer                        :: i,j,k");
  writeSource("integer                        :: nd");
  writeSource("integer                        :: ieq");
  writeSource("integer                        :: nodes");
  writeSource("integer                        :: np");
  writeSource("integer,dimension(:,:),pointer :: inset");
  com(); 



  com(); 

  switch(getSpaceDimension()) {
  case 1:
    writeSource("real(kind=REAL8)               :: x_dpt,u");
    break;
  case 2:
    writeSource("real(kind=REAL8)               :: x_dpt,y_dpt,u");
    break;
  case 3:
    writeSource("real(kind=REAL8)               :: x_dpt,y_dpt,z_dpt,u");
    break;
  }
  orderedPtrList <Variable *> varPtrLst = dPtr->GetVariablePtrLst();
  // FEM variables for EX 
  listIterator <Variable *>itr(varPtrLst);
  for(itr.init(); !itr; ++itr ){
    if(itr()->GetType() != VAR_FEM) continue;
    pushSource("real(kind=REAL8)               :: ");
    pushFEMVariableInCalled(itr());
    pushSource("_dpt");
    flushSource();
  }
  com();


  return;
}




void PM_feelfem90vec::DoDirichletReturnSequencePM(Dirichlet *dPtr)
{
  com();
  pushSource("end subroutine ");
  pushSource(GetDirichletRoutineName(dPtr->GetSolveNo(),dPtr->GetDcondNo() ));
  flushSource();

  pushSource("end module mod_");
  pushSource(GetDirichletRoutineName(dPtr->GetSolveNo(),dPtr->GetDcondNo() ));
  flushSource();

  return;
}
