/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 2000
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : feelfem90_dirichlet.cpp
 *  Date     : 2000/12/08
 *  Modified : 2001/02/02 orderedPtrList
 *             2002/03/06 dirichlet data formula routine
 *  
 *  Purpose  : feelfem90 programming style implementation 
 *             scalar model (derived from DRAMA double index parallel version)
 *
 *             DIRICHLET related generator routines
 *
 *
 *  feelfem2 (modernized/ported)
 *  Copyright (C) 2025-2026 Hidehiro Fujio and contributors
 *  SPDX-License-Identifier: BSD-3-Clause
 *  Repository: https://github.com/oimokoimo/feelfem2
 *
 *
 *  Notes:
 */
#include <cassert>

#include "feelfuncs.hpp"
#include "feeldef.hpp"
#include "Dirichlet.hpp"
#include "PM_feelfem90.hpp"

#include "TermConvert.hpp"

// Routine name

void PM_feelfem90::pushDirichletRoutineName(int solveNo, int dcondNo)
{
  char buf[BUFSIZ];
  sprintf(buf,"dcond%d_%d",solveNo,dcondNo);
  pushSource(buf);

  return;
}

void PM_feelfem90::F90useDirichletPM()
{
  F90useFEMDataType();
  F90useAlways();

  return;
}

//////////////////////////////////////////
// Dirichlet Conditions related functions
//////////////////////////////////////////


const char *PM_feelfem90::GetDirichletRoutineName(int solveNo, int dcondNo)
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


void PM_feelfem90::DoDirichletArgumentVariableDefinitionsPM(Dirichlet *dPtr)
{
  writeInteger4In("nsetno");  //integer,intent(in)           :: nsetno

  pushTypeDefCC("type(nsetList),pointer"); 
  pushSource("firstNsetPtr");   //type(nsetList),pointer  :: firstNsetPtr
  flushSource();
  com();

  writeInteger4In("neq");     //integer,intent(in)           :: neq
  com();

  writeInteger4In("npmax");   //integer,intent(in)           :: npmax");
  CoordinateVariableDeclaration();

  //  integer,dimension(npmax) :: ipf,ipd 
  writeInteger4sc("ipf(npmax),ipd(npmax)");
  com();

  
  // ipdinfo
  pushInteger4sc();
  pushSource("ipd_");
  Variable *dvarPtr = dPtr->GetDcondVariablePtr();
  pushSource(dvarPtr->GetName());
  pushSource("(npmax)");
  flushSource();

  
  orderedPtrList <Variable *> varPtrLst = dPtr->GetVariablePtrLst();
  ArgumentVariableDeclarationLst(varPtrLst);

  return;
}

void PM_feelfem90::doDirichletAutoVariableDefinitionsPM(Dirichlet *dPtr)
{
  COMMENTlong(" auto variables for dirichlet");
  writeInteger4sc("nd");
  writeInteger4sc("ieq");
  writeInteger4sc("nodes");
  writeInteger4sc("np");
  writeInteger4Ptr2("inset");
  com(); 

  switch(getSpaceDimension()) {
  case 1:
    writeReal8sc("x_dpt,u");
    break;
  case 2:
    writeReal8sc("x_dpt,y_dpt,u");
    break;
  case 3:
    writeReal8sc("x_dpt,y_dpt,z_dpt,u");
    break;
  }
  orderedPtrList <Variable *> varPtrLst = dPtr->GetVariablePtrLst();
  // FEM variables for EX 
  listIterator <Variable *>itr(varPtrLst);
  for(itr.init(); !itr; ++itr ){
    if(itr()->GetType() != VAR_FEM) continue;

    pushReal8sc();
    pushFEMVariableInCalled(itr());
    pushSource("_dpt");
    flushSource();
  }
  com();

  return;
}

void PM_feelfem90::DoDirichletReturnSequencePM(Dirichlet *dPtr)
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

// This routine is called from matrix data dependent routine MT_**dcond.cpp

void PM_feelfem90::doSetDirichletValue(Dirichlet *dPtr)
{
  pushSource( "  u = ");

  // Make termconvert

  TermConvert tc;

  tc.storeConvertPair("x","x_dpt");
  tc.storeConvertPair("y","y_dpt");
  tc.storeConvertPair("z","z_dpt");

  listIterator <Variable *>itrV(dPtr->GetVariablePtrLst());

  char from[MAX_VARNAME_LENGTH],to[MAX_VARNAME_LENGTH];
  
  for(itrV.init(); !itrV ; ++itrV ) {
    
    switch(itrV()->GetType() ) {
      
    case VAR_FEM:
      sprintf(from,"%s%c",itrV()->GetName(),'\0');
      sprintf(to  ,"fem_%s_dpt%c",itrV()->GetName(),'\0');
      tc.storeConvertPair(from,to);
      break;

    case VAR_DOUBLE:
    case VAR_CONST:
    case VAR_INT:
      sprintf(from,"%s%c",itrV()->GetName(),'\0');
      sprintf(to  ,"sc_%s%c",itrV()->GetName(),'\0');
      tc.storeConvertPair(from,to);
      break;

    default:
      assert(1==0);
    }
  }

  pushSource( tc.convertExpressionString( dPtr->GetExprStr() ));
  flushSource();  
  com();

  return;
}

void PM_feelfem90::DoDirichletInitializer(Dirichlet *dPtr)
{
  com();
  writeSource("call setP2nset(nsetno,firstNsetPtr,nodes,np,inset)");
  
  return;
}


void PM_feelfem90::DoDirichletLoopStart(Dirichlet *dPtr)
{
  comment();
  writeSource("do i=1,nodes");
  
  com();

  return;
}

void PM_feelfem90::DoDirichletCalcBoundaryValue(Dirichlet *dPtr)
{
  // used several times
  Variable *dvPtr = dPtr->GetDcondVariablePtr();

  writeSource("  nd  = inset(1,i)");

  COMMENTlong("Skip if no d.o.f is assigned at this node.");
  pushSource("  if(ipd_");
  pushSource(dvPtr->GetName());
  pushSource("(nd) == -1) cycle");
  flushSource();
  com();

  pushSource("  ieq = ipd(nd)+ipd_");    // ipdinfo
  pushSource(dvPtr->GetName());
  pushSource("(nd)");
  flushSource();
  com();

  switch(getSpaceDimension()) {
  case 1:
    writeSource("  x_dpt = x(nd)");
    break;

  case 2:
    writeSource("  x_dpt = x(nd)");
    writeSource("  y_dpt = y(nd)");
    break;

  case 3:
    writeSource("  x_dpt = x(nd)");
    writeSource("  y_dpt = y(nd)");
    writeSource("  z_dpt = z(nd)");
    break;
  }


  orderedPtrList <Variable *>varPtrLst = dPtr->GetVariablePtrLst();
  listIterator <Variable *>itr(varPtrLst);
  for(itr.init(); !itr; ++itr ){
    if(itr()->GetType() != VAR_FEM) continue;    // only fem var for dcond
    
    pushSource("  ");
    pushFEMVariableInCalled(itr());
    pushSource("_dpt = ");
    pushFEMVariableInCalled(itr());              // own variable
    pushSource("(nd)");
    flushSource();
  }
  com();
  // in PM
  doSetDirichletValue(dPtr);

  return;
}

void PM_feelfem90::DoDirichletLoopEnd(Dirichlet *dPtr)
{
  com();
  writeSource("end do   !(boundary node loop)");
  comment();

  return;
}


void PM_feelfem90::doDirichletArgumentSequencePM(Dirichlet *dPtr)
{
  pushSource("(nsetno,              &");
  flushSource();
  
  writeSource("  firstNsetPtr,              &");

  pushSource( "  ");
  pushCoordinateSource();
  pushSource(",ipf,ipd,ipd_");    // ipdinfo
  
  Variable *vPtr = dPtr->GetDcondVariablePtr();
  pushSource(vPtr->GetName());

  pushSource(",npmax           &");
  flushSource();

  /* Additional variables */
  orderedPtrList   <Variable *>varPtrLst = dPtr->GetVariablePtrLst();
  listIterator <Variable *>itr(varPtrLst);

  pushVariableListInCalled( varPtrLst);

  return;
}

void PM_feelfem90::doIthDirichletCallInSolvePM(Solve *solvePtr,int i)
{
  comment();
  pushSource("! No.");
  pushSourceInt(i+1);
  flushSource();
  com();

  pushSource("bdatSetPtr => solveInfoPtr%dlst(");
  pushSourceInt(i+1);
  pushSource(")");
  flushSource();
  com();

  writeSource("do i=1,bdatSetPtr%nofsets");
  com();

  writeSource("  no = bDatSetPtr%datlist(i)");
  pushSource("  call ");
  pushDirichletRoutineName(solvePtr->GetSolveNo(),i+1);
  pushSource("(no,firstNsetPtr,          &");
  flushSource();

  pushSource( "       ");
  pushCoordinateSource();
  pushSource(",ipf,ipd,ipd_");
  
  Dirichlet *dPtr = solvePtr->GetIthDirichletDataPtr(i);  //ipdinfo
  Variable  *vPtr = dPtr->GetDcondVariablePtr();
  pushSource(vPtr->GetName());

  pushSource(",npmax                     &");
  flushSource();

  pushSource("       ");
  pushVariableListInCalled(solvePtr->GetIthDirichletVariablePtrLst(i));

  return;
}

void PM_feelfem90::doIthDirichletCallInSolvePM2(Solve *solvePtr,int i)
{
  writeSource("end do");
  com();
}
  
