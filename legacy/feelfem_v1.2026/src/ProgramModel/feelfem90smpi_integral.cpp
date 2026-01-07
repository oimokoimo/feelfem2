/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2003
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : feelfem90smpi_ewquad.cpp
 *  Date     : 2003/01/04 (copied from feelfem90)
 *  
 *  Purpose  : assignment for integral calculation
 *  
 */

#include <assert.h>
#include <iostream.h>
#include <stdio.h>

#include "feeldef.hpp"
#include "feelfuncs.hpp"

#include "Assign.hpp"
#include "PM_feelfem90smpi.hpp"

#include "Element.hpp"
#include "Quadrature.hpp"
#include "EwiseQuadEcalInfo.hpp"

void PM_feelfem90smpi::DoAssignInitializeIntegral(Assign *asPtr)
{

  writeSource("!---------------------------");
  writeSource("! calculate only on host PE.");
  writeSource("!---------------------------");
  writeSource("if(myrank .eq. 0) then");

  comment();
  writeSource("edatno = meshDat%mainEdatNo");
  writeSource("call setP2edat(edatno,firstEdatPtr,nelem,np,netype,ielem,matno)");
  com();
  writeSource("if(np .ne. NDP) then");
  writeSource("  write(*,*) '**************************************'");
  writeSource("  write(*,*) '*          MESH ERROR                *'");
  writeSource("  write(*,*) '*  Number of nodes in one element is *'");
  writeSource("  write(*,*) '*  not what is expected.  Maybe mesh *'");
  writeSource("  write(*,*) '*  data mismatch.                    *'");
  writeSource("  write(*,*) '**************************************'");
  writeSource("end if");
  com();

  Variable *leftVarPtr = asPtr->GetLeftVarPtr();  

  pushSource("sc_");
  pushSource(leftVarPtr->GetName());
  pushSource(" = 0.0d0");
  flushSource();
  com();
  com();

  return;
}

void PM_feelfem90smpi::DoAssignAssignmentIntegral(Assign *asPtr)
{
  
  // for x,y,z
  int  parametricFreedom = asPtr->GetNodesForParametric();
  int *parametricPattern = asPtr->GetNodeInfoParametric();

  if(asPtr->IsUseX()) {
    for(int i=0;i<parametricFreedom;i++) {
      pushSource("ex(");
      pushSourceInt(i+1);
      pushSource(")=x(ielem(");
      pushSourceInt( *(parametricPattern + i ) );
      pushSource(",i))");
      flushSource();
    }
    com();
  }
  if(asPtr->IsUseY()) {
    for(int i=0;i<parametricFreedom;i++) {
      pushSource("ey(");
      pushSourceInt(i+1);
      pushSource(")=y(ielem(");
      pushSourceInt( *(parametricPattern + i ) );
      pushSource(",i))");
      flushSource();
    }
    com();
  }
  if(asPtr->IsUseZ()) {
    for(int i=0;i<parametricFreedom;i++) {
      pushSource("ez(");
      pushSourceInt(i+1);
      pushSource(")=z(ielem(");
      pushSourceInt( *(parametricPattern + i ) );
      pushSource(",i))");
      flushSource();
    }
    com();
  }

  delete [] parametricPattern;


  int  nodes;
  int *pattern;

  listIterator <Variable *>itrArgV( asPtr->GetVarPtrList() );
  for(itrArgV.init(); !itrArgV ; ++itrArgV ) {
    switch(itrArgV()->GetType()) {

    case VAR_FEM:
      nodes   = asPtr->GetNodesForVariable( itrArgV() );
      pattern = asPtr->GetNodeInfoVariable( itrArgV() );
      for(int i=0;i<nodes;i++) {
	pushSource("efem_");
	pushSource( itrArgV()->GetName());
	pushSource("(");
	pushSourceInt(i+1);
	pushSource(")=fem_");
	pushSource( itrArgV()->GetName());
	pushSource("(ielem(");
	pushSourceInt( *(pattern + i ) );
	pushSource(",i))");
	flushSource();
      }
      delete [] pattern;
      com();
      break;

    case VAR_VFEM:
      assert(1==0);
      break;

    default:
      break;
    }
  }      

  // calling sequence to colet
  pushSource(" call ");
  pushAssignCoRoutineName(asPtr);
  pushSource("(");

  // left var
  Variable *leftVarPtr = asPtr->GetLeftVarPtr();
  pushSource("sc_");
  pushSource(leftVarPtr->GetName());



  if(asPtr->IsUseX()) {
    for(int i=0;i<parametricFreedom;i++) {

      pushSource(",");
      pushSource("ex(");
      pushSourceInt(i+1);
      pushSource(")");
    }
  }
  if(asPtr->IsUseY()) {
    for(int i=0;i<parametricFreedom;i++) {

      pushSource(",");

      pushSource("ey(");
      pushSourceInt(i+1);
      pushSource(")");
    }
  }
  if(asPtr->IsUseZ()) {
    for(int i=0;i<parametricFreedom;i++) {

      pushSource(",");

      pushSource("ez(");
      pushSourceInt(i+1);
      pushSource(")");
    }
  }

  for(itrArgV.init(); !itrArgV ; ++itrArgV ) {

    if(itrArgV() == leftVarPtr) continue;

    switch(itrArgV()->GetType()) {

    case VAR_FEM:
      nodes   = asPtr->GetNodesForVariable( itrArgV() );
      for(int i=0;i<nodes;i++) {

	pushSource(",");

	pushSource("efem_");
	pushSource( itrArgV()->GetName());
	pushSource("(");
	pushSourceInt(i+1);
	pushSource(")");
      }
      break;

    case VAR_VFEM:
      assert(1==0);
      break;

    case VAR_EWISE:
      pushSource(",");
      pushSource("ew_");
      pushSource( itrArgV()->GetName());
      pushSource("(i)");
      break;

    case VAR_MATERIAL:
      pushSource(",");
      pushSource("m_");
      pushSource( itrArgV()->GetName());
      pushSource("(matno(i))");
      break;

    case VAR_EWISE_A:
      pushSource(",");
      pushSource("ew_");
      pushSource( itrArgV()->GetName());
      pushSource("(1:");
      pushSourceInt( itrArgV()->GetFreedom());
      pushSource(",i)");
      break;

    case VAR_DOUBLE:
    case VAR_INT:
      if(leftVarPtr == itrArgV()) break;   // left var
      pushSource(",");
      pushSource("sc_");
      pushSource( itrArgV()->GetName());
      break;

    case VAR_CONST:
      pushSource(",");
      pushSource("co_");
      pushSource( itrArgV()->GetName());
      break;

    default:
      assert(1==0);
    }
  }
  pushSource(")");
  flushSource();
  com();
  
  return;
}


// CoRoutines
void PM_feelfem90smpi::DoAssignCoRoutineHeaderIntegral( Assign *asPtr)
{
  // module sentence
  pushSource("module mod_");
  pushAssignCoRoutineName(asPtr);
  flushSource();

  // contains
  writeSource("contains");
  
  // subroutine sentence
  pushSource("subroutine ");
  pushAssignCoRoutineName(asPtr);
  pushSource("(");

  // left var
  Variable *leftVarPtr = asPtr->GetLeftVarPtr();

  // integral  
  pushSource("sc_");
  pushSource(leftVarPtr->GetName());


  // for x,y,z coordinates
  int  parametricFreedom = asPtr->GetNodesForParametric();
  if(asPtr->IsUseX()) {
    for(int i=0;i<parametricFreedom;i++) {

      pushSource(",");
      pushSource("x");
      pushSourceInt(i+1);
    }
  }
  if(asPtr->IsUseY()) {
    for(int i=0;i<parametricFreedom;i++) {

      pushSource(",");

      pushSource("y");
      pushSourceInt(i+1);
    }
  }
  if(asPtr->IsUseZ()) {
    for(int i=0;i<parametricFreedom;i++) {

      pushSource(",");
      pushSource("z");
      pushSourceInt(i+1);
    }
  }


  listIterator <Variable *>itrArgV( asPtr->GetVarPtrList() );
  int nodes;

  for(itrArgV.init(); !itrArgV ; ++itrArgV ) {
    switch(itrArgV()->GetType()) {

    case VAR_FEM:

      nodes   = asPtr->GetNodesForVariable( itrArgV() );
      for(int i=0;i<nodes;i++) {

	pushSource(",");

	pushSource("fem_");
	pushSource( itrArgV()->GetName());
	pushSource("_");
	pushSourceInt(i+1);
      }
      break;

    case VAR_VFEM:
      assert(1==0);
      break;

    case VAR_EWISE:
      pushSource(",");
      pushSource("ew_");
      pushSource( itrArgV()->GetName());
      break;

    case VAR_MATERIAL:
      pushSource(",");
      pushSource("m_");
      pushSource( itrArgV()->GetName());
      break;

    case VAR_EWISE_A:
      pushSource(",");
      pushSource("ew_");
      pushSource( itrArgV()->GetName());
      break;

    case VAR_DOUBLE:
    case VAR_INT:
      if(leftVarPtr == itrArgV()) break;   // left var
      pushSource(",");
      pushSource("sc_");
      pushSource( itrArgV()->GetName());
      break;

    case VAR_CONST:
      pushSource(",");
      pushSource("sc_");                         // in ECAL class routine,
      pushSource( itrArgV()->GetName());         // constant is sc_
      break;

    default:
      assert(1==0);
    }
  }
  pushSource(")");
  flushSource();
  com();

  //use
  SourceStarters();
  com();

  F90useAlways();
  com();

  // user function
  listIterator<string>itrufs(asPtr->GetUsedUserFuncStrList());
  for(itrufs.init();!itrufs;++itrufs) {
    pushSource("use mod_");
    pushSource(itrufs());
    flushSource();
  }

  // implicit
  fortImplicit();  // this is in colet
  com();

  return;
}

void PM_feelfem90smpi::DoAssignLoopEndIntegral(Assign *asPtr)
{
  writeSource("end do");
  com();

  writeSource("end if   ! myrank == 0");
  com();
  com();

  
  pushSource("call MPI_BCAST(");
  Variable *leftVarPtr = asPtr->GetLeftVarPtr();
  pushSource("sc_");
  pushSource(leftVarPtr->GetName());
  pushSource(",1,MPI_DOUBLE_PRECISION,0,MPI_COMM_WORLD,ierror)");
  flushSource();


  com();
  return;
}

// void PM_feelfem90smpi::DoAssignCoRoutineParametersEwQuad  ( Assign *asPtr)
// {
//   comment();
//     // for NPG, number of gauss points
//   Quadrature *qPtr = asPtr->GetQuadraturePtr();
// 
//   pushInteger4pm();
//   pushSource("NPG =");
//   pushSourceInt(qPtr->GetQuadraturePoints());
//   pushSource("  !  [");
//   pushSource(qPtr->GetName());
//   pushSource("]");
//   flushSource();
//   com();
// 
//   return;
// }

void PM_feelfem90smpi::DoAssignCoRoutineVariableDefinitionsIntegral( Assign *asPtr)
{

  // left var
  Variable *leftVarPtr = asPtr->GetLeftVarPtr();
  pushReal8sc();
  pushSource("sc_");
  pushSource(leftVarPtr->GetName());
  flushSource();


  // for x,y,z coordinates
  int  parametricFreedom = asPtr->GetNodesForParametric();
  if(asPtr->IsUseX()) {
    for(int i=0;i<parametricFreedom;i++) {

      pushReal8sc();
      pushSource("x");
      pushSourceInt(i+1);
      flushSource();
    }
  }
  if(asPtr->IsUseY()) {
    for(int i=0;i<parametricFreedom;i++) {

      pushReal8sc();
      pushSource("y");
      pushSourceInt(i+1);
      flushSource();
    }
  }
  if(asPtr->IsUseZ()) {
    for(int i=0;i<parametricFreedom;i++) {

      pushReal8sc();
      pushSource("z");
      pushSourceInt(i+1);
      flushSource();
    }
  }


  listIterator <Variable *>itrArgV( asPtr->GetVarPtrList() );
  int nodes;

  for(itrArgV.init(); !itrArgV ; ++itrArgV ) {

    if(itrArgV() == leftVarPtr) continue;

    switch(itrArgV()->GetType()) {

    case VAR_FEM:

      nodes   = asPtr->GetNodesForVariable( itrArgV() );
      for(int i=0;i<nodes;i++) {

	pushReal8sc();
	pushSource("fem_");
	pushSource( itrArgV()->GetName());
	pushSource("_");
	pushSourceInt(i+1);
	flushSource();
      }
      break;

    case VAR_VFEM:
      assert(1==0);
      break;

    case VAR_EWISE:
      pushReal8sc();
      pushSource("ew_");
      pushSource( itrArgV()->GetName());
      flushSource();
      break;

    case VAR_MATERIAL:
      pushReal8sc();
      pushSource("m_");
      pushSource( itrArgV()->GetName());
      flushSource();
      break;

    case VAR_EWISE_A:
      if(leftVarPtr == itrArgV()) break;   // left var

      pushReal8Array1();
      pushSource("ew_");
      pushSource( itrArgV()->GetName());
      flushSource();
      break;

    case VAR_DOUBLE:
      pushReal8sc();
      pushSource("sc_");
      pushSource( itrArgV()->GetName());
      flushSource();
      break;

    case VAR_INT:
      pushInteger4sc();
      pushSource("sc_");
      pushSource( itrArgV()->GetName());
      flushSource();
      break;

    case VAR_CONST:
      pushReal8sc();
      pushSource("sc_");                         // this is special for ecal
      pushSource( itrArgV()->GetName());         // type, not co_ but sc_
      flushSource();
      break;

    default:
      assert(1==0);
    }
  }
  com();
  comment();  // auto variable
  
  writeInteger4sc("i,itp");

  // Jacobian (for integral, it is set at SNassignment_InfoGenerate.cpp)
  if(asPtr->IsUseDifferential1st() ||
     asPtr->IsUseDifferential2nd()    ) {  // 2nd is future option
    assert(spaceDim > 1  && spaceDim <4);
    if(spaceDim == 2) {
      writeReal8sc("rj(2,2),rij(2,2),det");
    }
    if(spaceDim == 3) {
      writeReal8sc("rj(3,3),rij(3,3),det");
    }
    com();
  }

  // for assign forumulas
  EwiseQuadEcalInfo *ewqeiPtr = asPtr->GetEwQEcalInfoPtr();
  
  if(ewqeiPtr->IsUseXVal()) {
    writeReal8sc("qx");
  }
  if(ewqeiPtr->IsUseYVal()) {
    writeReal8sc("qy");
  }
  if(ewqeiPtr->IsUseZVal()) {
    writeReal8sc("qz");
  }

  // var.
  listIterator<VariableEvalPair *>itr(ewqeiPtr->GetVariableEvalPairPtrList());
  for(itr.init();!itr;++itr ) {
    if(itr()->IsElementType()) {
      if(itr()->GetVarType() == VAR_FEM) {
	pushReal8sc();
	pushSource("qfem_");
      }
      else if(itr()->GetVarType() == VAR_EWISE_A) {
	pushReal8sc();
	pushSource("qew_");
      }
      else {
	// vfem?
	assert(1==0);
      }
      Variable *vPtr = itr()->GetVariablePtr();
      pushSource(vPtr->GetName());
      
      switch(itr()->GetDiffType()) {

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
      flushSource();
    }
  }
  com();

      

  // quadrature related
  pushReal8sc();
  pushSource("gx(NPG)");
  if(spaceDim >1) { pushSource(",gy(NPG)"); }
  if(spaceDim >2) { pushSource(",gz(NPG)"); }
  flushSource();

  pushReal8sc();
  pushSource("wt(NPG)");
  flushSource();
  com();

  // for function itself, first define r***

  listIterator <Element *>itrE0( ewqeiPtr -> GetUsedElementPtrList());
  for(itrE0.init(); !itrE0 ; ++itrE0) {
    int freedom = itrE0()->GetElementFreedom();
    for(int i=0;i<freedom;i++) {
      pushReal8sc();
      pushSource("r");
      pushSource(itrE0()->GetName());
      pushSource("_");
      pushSourceInt(i+1);
      pushSource("(NPG)");
      flushSource();
    }
  }
  com();

  // r series for first derivative  (set in InfoGenerate)
  listIterator <Element *>itrE1( ewqeiPtr -> GetUsedD1ElementPtrList());
  for(itrE1.init(); !itrE1 ; ++itrE1) {
    int freedom = itrE1()->GetElementFreedom();
    for(int i=0;i<freedom;i++) {
      pushReal8sc();
      pushSource("r");
      pushSource(itrE1()->GetName());
      pushSource("_");
      pushSourceInt(i+1);
      pushSource("_x(NPG)");
      flushSource();

      if(spaceDim >1) {
	pushReal8sc();
	pushSource("r");
	pushSource(itrE1()->GetName());
	pushSource("_");
	pushSourceInt(i+1);
	pushSource("_y(NPG)");
	flushSource();
      } 

      if(spaceDim >2) {
	pushReal8sc();
	pushSource("r");
	pushSource(itrE1()->GetName());
	pushSource("_");
	pushSourceInt(i+1);
	pushSource("_z(NPG)");
	flushSource();
      }
    }
  }
  com();

  // q series
  for(itrE0.init(); !itrE0 ; ++itrE0) {
    int freedom = itrE0()->GetElementFreedom();
    for(int i=0;i<freedom;i++) {
      pushReal8sc();
      pushSource("q");
      pushSource(itrE0()->GetName());
      pushSource("_");
      pushSourceInt(i+1);
      flushSource();
    }
  }
  com();

  // q series for first derivative
  for(itrE1.init(); !itrE1 ; ++itrE1) {
    int freedom = itrE1()->GetElementFreedom();
    for(int i=0;i<freedom;i++) {
      pushReal8sc();
      pushSource("q");
      pushSource(itrE1()->GetName());
      pushSource("_");
      pushSourceInt(i+1);
      pushSource("_x");
      flushSource();

      if(spaceDim >1) {
	pushReal8sc();
	pushSource("q");
	pushSource(itrE1()->GetName());
	pushSource("_");
	pushSourceInt(i+1);
	pushSource("_y");
	flushSource();
      } 

      if(spaceDim >2) {
	pushReal8sc();
	pushSource("q");
	pushSource(itrE1()->GetName());
	pushSource("_");
	pushSourceInt(i+1);
	pushSource("_z");
	flushSource();
      }
    }
  }  
  com();

  writeInteger4sc("comeyet");
  com();
  writeSource("data comeyet/0/");
  com();
  comment();
  return;
}


// void PM_feelfem90smpi::DoAssignCoRoutineQuadratureSettingsEwQuad  ( Assign *asPtr)
// {
//   writeSource("if(comeyet == 0) then");
//   writeSource("  comeyet = 1");
//   com();
// 
//   Quadrature *qPtr = asPtr->GetQuadraturePtr();
// 
//   int points; 
//   int dim;
// 
//   points = qPtr->GetQuadraturePoints();
//   dim    = qPtr->GetDimension();
// 
//   for(int ip=0;ip<points;ip++) {
//     
//     // gx
//     pushSource("  gx");
//     pushSource("(");
//     pushSourceInt( ip+1 );
//     pushSource(") =");
//     pushSourceDbl( qPtr->GetIthXi( ip ) );
//     flushSource();
// 
//     // gy
//     if(dim > 1) {
//       pushSource("  gy");
//       pushSource("(");
//       pushSourceInt( ip+1 );
//       pushSource(") =");
//       pushSourceDbl( qPtr->GetIthEta( ip ) );
//       flushSource();
//     }
// 
//     // gz
//     if(dim > 2) {
//       pushSource("  gz");
//       pushSource("(");
//       pushSourceInt( ip+1 );
//       pushSource(") =");
//       pushSourceDbl( qPtr->GetIthZeta( ip ) );
//       flushSource();
//     }
//   }
// 
//   comment();
// 
//   // loop for Quadrature
//   pushSource("  do itp=1,NPG");
//   flushSource();
//   com();
// 
//   EwiseQuadEcalInfo *ewqeiPtr = asPtr->GetEwQEcalInfoPtr();
//   listIterator <Element *>itrE0( ewqeiPtr -> GetUsedElementPtrList());
//   listIterator <Element *>itrE1( ewqeiPtr -> GetUsedD1ElementPtrList());
// 
//   for(itrE0.init(); !itrE0 ; ++itrE0) {
//     doAssignEwquadCalcInterpolation( itrE0() , TYPE_DIFF_ZERO );
//   }
// 
//   for(itrE1.init(); !itrE1 ; ++itrE1) {
//     doAssignEwquadCalcInterpolation( itrE1() , TYPE_DIFF_X );
// 
//     if( spaceDim >1) {
//       doAssignEwquadCalcInterpolation( itrE1() , TYPE_DIFF_Y );
//     }
// 
//     if( spaceDim >2) {
//       doAssignEwquadCalcInterpolation( itrE1() , TYPE_DIFF_Z );
//     }
//   }
//   com();
//   writeSource("  end do");
//   com();
//   writeSource("end if  ! (comeyet)");
//   comment();
//   com();
//   com();
// 
//   return;
// }
// 
// void PM_feelfem90smpi::doAssignEwquadCalcInterpolation(Element *ePtr,
//  				                   int      type )
// {
//   int freedom = ePtr->GetElementFreedom();
//   
//   // Make TermConvert
// 
//   TermConvert tc;
// 
//   char buf[38];
// 
//   // for r  ===> _m1
//   //  sprintf(buf,"gx(itp)",quadNo);
//   tc.StoreMetaPair( "r" , "gx(itp)");
// 
//   // for s  ===> _m2
//   tc.StoreMetaPair( "s" , "gy(itp)");
// 
//   // for t  ===> _m3
//   tc.StoreMetaPair( "t" , "gz(itp)");
// 
// 
//   for(int i=0;i<freedom;i++) {
//     Interpolation *iPtr = ePtr->GetIthInterpolationPtr(i);
// 
//     pushSource("  ");
//     pushSource("r");
//     pushSource(ePtr->GetName());
//     pushSource("_");
//     pushSourceInt(i+1);
// 
//     switch(type) {
// 
//     case TYPE_DIFF_ZERO:
//       break;
// 
//     case TYPE_DIFF_X:
//       pushSource("_x");
//       break;
// 
//     case TYPE_DIFF_Y:
//       pushSource("_y");
//       break;
// 
//     case TYPE_DIFF_Z:
//       pushSource("_z");
//       break;
// 
//     default:
//       assert(1==0);
//     }
// 
//     pushSource("(itp)=");
// 
// 
//     string exprStrForGinac = tc.convertExpressionString(iPtr->GetExprString());
// 
//     void esetDerivative(char *,int,char *,int);
//     char exprBuf[MAX_FORMULA_BUF];
// 
//     switch(type) {
//     case TYPE_DIFF_ZERO:
//       exprStrForGinac = tc.ReverseConvertExpressionString(exprStrForGinac);
//       break;
// 
//     case TYPE_DIFF_X:
//     case TYPE_DIFF_Y:
//     case TYPE_DIFF_Z:
// 
//       esetDerivative( exprStrForGinac, type, exprBuf,MAX_FORMULA_BUF );
//       exprStrForGinac = tc.ReverseConvertExpressionString(exprBuf);
//       break;
// 
//     default:
//       assert(1==0);
//     }
// 
//     pushSourceHAT(exprStrForGinac);
//     flushSource();
//   }
//   return;
// }


 
void PM_feelfem90smpi::DoAssignCoRoutineStatementIntegral( Assign *asPtr)
{

  comment();
  writeSource("do itp=1,NPG");

  com();

  // Jacobian check
  if(asPtr->IsUseDifferential1st() ||
     asPtr->IsUseDifferential2nd()    ) {  // 2nd is future option
    
    // write jacobian
    doAssignEwquadJacobian(asPtr);
  }

  // convert r->q
  doAssignEwquadRQconv(asPtr);

  // evaluation at gaussP
  doAssignEwquadEvalAtGaussP(asPtr);

  // assign statement
  doAssignIntegral(asPtr);

  writeSource("end do");  // co routine

  com();


  return;
}

void PM_feelfem90smpi::doAssignIntegral(Assign *asPtr)
{

  com();
  comment();
  com();

  pushSource("  ");
  pushVariableInCalled(asPtr->GetLeftVarPtr());
  pushSource("=");
  pushVariableInCalled(asPtr->GetLeftVarPtr());
  pushSource("+(");
  
  TermConvert tc;
  EwiseQuadEcalInfo *ewqeiPtr = asPtr->GetEwQEcalInfoPtr();    

  char bfrom[VARIABLE_TERMCONVERT_BUFSIZ];
  char bto  [VARIABLE_TERMCONVERT_BUFSIZ];
  listIterator<VariableEvalPair *>itr(ewqeiPtr->GetVariableEvalPairPtrList());
  for(itr.init();!itr;++itr ) {
    Variable *vPtr = itr()->GetVariablePtr();
    if(itr()->IsElementType()) continue;
    
    switch(itr()->GetVarType()) {
    case VAR_INT:
    case VAR_DOUBLE:
    case VAR_CONST:    // const value has also sc_ and it is treated in arg.
      break;

    case VAR_EWISE:
      sprintf(bfrom,"ew_%s_m%c"  ,vPtr->GetName(),'\0');
      sprintf(bto  ,"ew_%s%c",vPtr->GetName(),'\0');
      tc.storeConvertPair( bfrom, bto );
      break;

    case VAR_EWISE_A:
      sprintf(bfrom,"ew_%s_q%c"  ,vPtr->GetName(),'\0');
      sprintf(bto  ,"ew_%s(itp)%c",vPtr->GetName(),'\0');
      tc.storeConvertPair( bfrom, bto );
      break;

    case VAR_MATERIAL:
      break;

    case VAR_FEM:
      cerr << "ewise variable must not be appeared here.\n";
      assert(1==0);  
      break;

    case VAR_VFEM:
      cerr << "Not implemented...???\n";
      assert(1==0);

    default:
      assert(1==0);

    }
  }

  string exprF90Str = tc.convertExpressionString(asPtr->GetExprString());
  pushSourceHAT( exprF90Str );

  pushSource(")*det*wt(itp)");
  flushSource();    
      
  tc.~TermConvert();
  com();  
  comment();
  com();
  
  return;
}

// void PM_feelfem90smpi::doAssignEwquadEvalAtGaussP(Assign *asPtr)
// {
//   EwiseQuadEcalInfo *ewqeiPtr = asPtr->GetEwQEcalInfoPtr();  
//   
//   if(ewqeiPtr->IsUseXVal()) {
//     Element *elemPtr = asPtr->GetParametricElementPtr();
//     int freedom      = elemPtr->GetElementFreedom();
//     pushSource("  qx = ");
//     for(int i=0;i<freedom;i++) {
//       if(i!=0) pushSource("+");
//       pushSource("x");
//       pushSourceInt(i+1);     // Not node pattern for ewise quad
//       pushSource("*q");
//       pushSource(elemPtr->GetName());
//       pushSource("_");
//       pushSourceInt(i+1);
//     }
//     flushSource();
//     com();
//   }
// 
//   if(ewqeiPtr->IsUseYVal()) {
//     Element *elemPtr = asPtr->GetParametricElementPtr();
//     int freedom      = elemPtr->GetElementFreedom();
//     pushSource("  qy = ");
//     for(int i=0;i<freedom;i++) {
//       if(i!=0) pushSource("+");
//       pushSource("y");
//       pushSourceInt(i+1);     // Not node pattern for ewise quad
//       pushSource("*q");
//       pushSource(elemPtr->GetName());
//       pushSource("_");
//       pushSourceInt(i+1);
//     }
//     flushSource();
//     com();
//   }
// 
//   if(ewqeiPtr->IsUseZVal()) {
//     Element *elemPtr = asPtr->GetParametricElementPtr();
//     int freedom      = elemPtr->GetElementFreedom();
//     pushSource("  qz = ");
//     for(int i=0;i<freedom;i++) {
//       if(i!=0) pushSource("+");
//       pushSource("z");
//       pushSourceInt(i+1);     // Not node pattern for ewise quad
//       pushSource("*q");
//       pushSource(elemPtr->GetName());
//       pushSource("_");
//       pushSourceInt(i+1);
//     }
//     flushSource();
//     com();
//   }
// 
//   listIterator<VariableEvalPair *>itr(ewqeiPtr->GetVariableEvalPairPtrList());
//   for(itr.init();!itr;++itr ) {
//     if(itr()->IsElementType()) {
//       if(itr()->GetVarType() == VAR_FEM) {
// 	pushSource("  qfem_");
//       }
//       else if(itr()->GetVarType() == VAR_EWISE_A) {
// 	pushSource("  qew_");
//       }
//       else {
// 	// vfem?
// 	assert(1==0);
//       }
//       Variable *vPtr = itr()->GetVariablePtr();
//       pushSource(vPtr->GetName());
// 
//       Element  *ePtr = itr()->GetElementPtr();
//       
//       
//       switch(itr()->GetDiffType()) {
// 
//       case TYPE_DIFF_ZERO:
// 	break;
// 
//       case TYPE_DIFF_X:
// 	pushSource("_x");
// 	break;
//       
//       case TYPE_DIFF_Y:
// 	pushSource("_y");
// 	break;
//       
//       case TYPE_DIFF_Z:
// 	pushSource("_z");
// 	break;
// 	
//       default:
// 	assert(1==0);
//       }
//       
//       // =
//       pushSource("=");
//       
//       int freedom = ePtr->GetElementFreedom();
//       for(int i=0;i<freedom;i++) {
// 	if(i != 0) pushSource("+");
// 
// 	//fem variable
// 	if(itr()->GetVarType() == VAR_FEM) {
// 	  pushSource("fem_");
// 	  pushSource(vPtr->GetName());
// 	  pushSource("_");
// 	  pushSourceInt(i+1);
// 	}
// 	else if(itr()->GetVarType() == VAR_EWISE_A) {
// 	  pushSource("ew_");
// 	  pushSource(vPtr->GetName());
// 	  pushSource("(");
// 	  pushSourceInt(i+1);
// 	  pushSource(")");
// 	}
// 	else {
// 	  assert(1==0); // vfem
// 	}
// 
// 	pushSource("*");
// 	
// 	pushSource("q");
// 	pushSource(ePtr->GetName());
// 	pushSource("_");
// 	pushSourceInt(i+1);
// 	
// 	switch(itr()->GetDiffType()) {
// 
// 	case TYPE_DIFF_ZERO:
// 	  break;
// 
// 	case TYPE_DIFF_X:
// 	  pushSource("_x");
// 	  break;
//       
// 	case TYPE_DIFF_Y:
// 	  pushSource("_y");
// 	  break;
//       
// 	case TYPE_DIFF_Z:
// 	  pushSource("_z");
// 	  break;
// 	
// 	default:
// 	  assert(1==0);
// 	}
//       }
//       flushSource();
//       com();
//     }
//   }
//   com();
// }
// 
// void PM_feelfem90smpi::doAssignEwquadRQconv(Assign *asPtr)
// {
//   EwiseQuadEcalInfo *ewqeiPtr = asPtr->GetEwQEcalInfoPtr();
//   listIterator <Element *>itrE0( ewqeiPtr -> GetUsedElementPtrList());
//   listIterator <Element *>itrE1( ewqeiPtr -> GetUsedD1ElementPtrList());
// 
//   for(itrE0.init(); !itrE0 ; ++itrE0) {
//     int  freedom = itrE0()->GetElementFreedom();
//     for(int i=0;i<freedom;i++) {
//       pushSource("  q");
//       pushSource(itrE0()->GetName());
//       pushSource("_");
//       pushSourceInt(i+1);
//       pushSource(" = r");
//       pushSource(itrE0()->GetName());
//       pushSource("_");
//       pushSourceInt(i+1);
//       pushSource("(itp)");
//       flushSource();
//     }
//     com();
//   }
// 
//   for(itrE1.init(); !itrE1 ; ++itrE1) {
//     int freedom = itrE1()->GetElementFreedom();
// 
//     for(int i=0;i<freedom;i++) {
//       pushEwquadDiffSub_1st(itrE1(), spaceDim, i+1,TYPE_DIFF_X);
//     }
//     if(spaceDim >1) {
//       for(int i=0;i<freedom;i++) {
// 	pushEwquadDiffSub_1st(itrE1(), spaceDim, i+1,TYPE_DIFF_Y);
//       }
//     }
//     if(spaceDim >2) {
//       for(int i=0;i<freedom;i++) {
// 	pushEwquadDiffSub_1st(itrE1(), spaceDim, i+1,TYPE_DIFF_Z);
//       }
//     }
//     com();
//   }
// }
// 
// void PM_feelfem90smpi::doAssignEwquadJacobian(Assign *asPtr)
// {
//   EwiseQuadEcalInfo *ewqeiPtr = asPtr->GetEwQEcalInfoPtr();
//   Element *parametricElemPtr= ewqeiPtr->GetParametricElementPtr();
//   int      freedom   = asPtr->GetNodesForParametric();
//   int     *ndPattern = asPtr->GetNodeInfoParametric();
// 
//   for(int i=0;i<freedom;i++) {
//     assert(*(ndPattern + i) == i+1);     // this is the difference from ecal
//   }
// 
//   switch(spaceDim) {
// 
//   case 1:
//     assert(1==0);
//     break;
// 
//   case 2:
//     // for rj(1,1)
//     pushSource(            "  rj(1,1) = ");
//     pushEwquadJacobiSub(freedom,ndPattern,"x","x",parametricElemPtr->GetName());
//     flushSource();
// 
//     // for rj(1,2)
//     pushSource(            "  rj(1,2) = ");
//     pushEwquadJacobiSub(freedom,ndPattern,"y","x",parametricElemPtr->GetName());
//     flushSource();
// 
//     // for rj(2,1)
//     pushSource(            "  rj(2,1) = ");
//     pushEwquadJacobiSub(freedom,ndPattern,"x","y",parametricElemPtr->GetName());
//     flushSource();
// 
//     // for rj(2,2)
//     pushSource(            "  rj(2,2) = ");
//     pushEwquadJacobiSub(freedom,ndPattern,"y","y",parametricElemPtr->GetName());
//     flushSource();
// 
//     com();
// 
//     writeSource("  det = rj(1,1)*rj(2,2)-rj(1,2)*rj(2,1)");
//     com();
// 
//     writeSource("  rij(1,1) =  rj(2,2)/det");
//     writeSource("  rij(2,2) =  rj(1,1)/det");
//     writeSource("  rij(1,2) = -rj(1,2)/det");
//     writeSource("  rij(2,1) = -rj(2,1)/det");
//     com();
// 
//     break;
// 
//   case 3:
//     // for rj(1,1)
//     pushSource(            "  rj(1,1) = ");
//     pushEwquadJacobiSub(freedom,ndPattern,"x","x",parametricElemPtr->GetName());
//     flushSource();
// 
//     // for rj(1,2)
//     pushSource(            "  rj(1,2) = ");
//     pushEwquadJacobiSub(freedom,ndPattern,"y","x",parametricElemPtr->GetName());
//     flushSource();
// 
//     // for rj(1,3)
//     pushSource(            "  rj(1,3) = ");
//     pushEwquadJacobiSub(freedom,ndPattern,"z","x",parametricElemPtr->GetName());
//     flushSource();
// 
//     // for rj(2,1)
//     pushSource(            "  rj(2,1) = ");
//     pushEwquadJacobiSub(freedom,ndPattern,"x","y",parametricElemPtr->GetName());
//     flushSource();
// 
//     // for rj(2,2)
//     pushSource(            "  rj(2,2) = ");
//     pushEwquadJacobiSub(freedom,ndPattern,"y","y",parametricElemPtr->GetName());
//     flushSource();
// 
//     // for rj(2,3)
//     pushSource(            "  rj(2,3) = ");
//     pushEwquadJacobiSub(freedom,ndPattern,"z","y",parametricElemPtr->GetName());
//     flushSource();
// 
//     // for rj(3,1)
//     pushSource(            "  rj(3,1) = ");
//     pushEwquadJacobiSub(freedom,ndPattern,"x","z",parametricElemPtr->GetName());
//     flushSource();
// 
//     // for rj(3,2)
//     pushSource(            "  rj(3,2) = ");
//     pushEwquadJacobiSub(freedom,ndPattern,"y","z",parametricElemPtr->GetName());
//     flushSource();
// 
//     // for rj(3,3)
//     pushSource(            "  rj(3,3) = ");
//     pushEwquadJacobiSub(freedom,ndPattern,"z","z",parametricElemPtr->GetName());
//     flushSource();
//     
//     com();
// 
//     writeSource("  det =  rj(1,1)*rj(2,2)*rj(3,3)  &");
//     writeSource("       + rj(1,2)*rj(2,3)*rj(3,1)  &");
//     writeSource("       + rj(1,3)*rj(2,1)*rj(3,2)  &");
//     writeSource("       - rj(1,1)*rj(2,3)*rj(3,2)  &");
//     writeSource("       - rj(1,2)*rj(2,1)*rj(3,3)  &");
//     writeSource("       - rj(1,3)*rj(2,2)*rj(3,1)");
//     com();
// 
//     writeSource("  rij(1,1)=      (rj(2,2)*rj(3,3)-rj(2,3)*rj(3,2))/det");
//     writeSource("  rij(1,2)= -1.0*(rj(1,2)*rj(3,3)-rj(1,3)*rj(3,2))/det");
//     writeSource("  rij(1,3)=      (rj(1,2)*rj(2,3)-rj(1,3)*rj(2,2))/det");
//     writeSource("  rij(2,1)= -1.0*(rj(2,1)*rj(3,3)-rj(2,3)*rj(3,1))/det");
//     writeSource("  rij(2,2)=      (rj(1,1)*rj(3,3)-rj(1,3)*rj(3,1))/det");
//     writeSource("  rij(2,3)= -1.0*(rj(1,1)*rj(2,3)-rj(1,3)*rj(2,1))/det");
//     writeSource("  rij(3,1)=      (rj(2,1)*rj(3,2)-rj(2,2)*rj(3,1))/det");
//     writeSource("  rij(3,2)= -1.0*(rj(1,1)*rj(3,2)-rj(1,2)*rj(3,1))/det");
//     writeSource("  rij(3,3)=      (rj(1,1)*rj(2,2)-rj(1,2)*rj(2,1))/det");
//     com();
//     break;
// 
//   default:
//     assert(1==0);
//   }
//   delete [] ndPattern;
// 
//   return;
// }
// 
// // Caution,  ndPattern must not be used here,,,   this func comes from ecal.
// void PM_feelfem90smpi::pushEwquadJacobiSub(int freedom,int *ndPattern,
// 				       const char *coor, 
// 				       const char*derivative, const char*nm)
// {
//   for(int i=0;i<freedom;i++) {
//     if(i != 0) {
//       pushSource("+");
//     }
// 
//     pushSource(coor);                // x
//     pushSourceInt(*(ndPattern+i));   // 2
//     pushSource("*");                 // *
//     pushSource("r");                 // r
//     pushSource(nm);                  // P1
//     pushSource("_");                 // _
//     pushSourceInt(i+1);              // 2     
//     pushSource("_");
//     pushSource(derivative);
//     pushSource("(itp)");
//   }
//   return;
// }
// 
// void PM_feelfem90smpi::pushEwquadDiffSub_1st(Element *ePtr,
// 					 int dim,int no,int diffType )
// {
//   pushSource("  q");
//   pushSource(ePtr->GetName());
//   pushSource("_");  
//   pushSourceInt(no);
//   pushSource("_");
//   
//   switch( diffType ) {
//   case TYPE_DIFF_X:
//     pushSource("x");
//     break;
// 
//   case TYPE_DIFF_Y:
//     pushSource("y");
//     break;
// 
//   case TYPE_DIFF_Z:
//     pushSource("z");
//     break;
// 
//   default:
//     assert(1==0);
//   }
// 
//   // first (dx)
//   pushSource(" = r");
//   pushSource(ePtr->GetName());
//   pushSource("_");
//   pushSourceInt(no);
//   pushSource("_x");
//   switch( diffType ) {
//   case TYPE_DIFF_X:
//     pushSource("(itp)*rij(1,1)");
//     break;
// 
//   case TYPE_DIFF_Y:
//     pushSource("(itp)*rij(2,1)");
//     break;
// 
//   case TYPE_DIFF_Z:
//     pushSource("(itp)*rij(3,1)");
//     break;
// 
//   default:
//     assert(1==0);
//   }
// 
//   assert(dim == 2 || dim == 3);
// 
//   // second (dy)
//   pushSource("+r");
//   pushSource(ePtr->GetName());
//   pushSource("_");
//   pushSourceInt(no);
//   pushSource("_y");
//   switch( diffType ) {
//   case TYPE_DIFF_X:
//     pushSource("(itp)*rij(1,2)");
//     break;
// 
//   case TYPE_DIFF_Y:
//     pushSource("(itp)*rij(2,2)");
//     break;
// 
//   case TYPE_DIFF_Z:
//     pushSource("(itp)*rij(3,2)");
//     break;
// 
//   default:
//     assert(1==0);
//   }
//   
//   if(dim == 3) {
//     // second (dz)
//     pushSource("+r");
//     pushSource(ePtr->GetName());
//     pushSource("_");
//     pushSourceInt(no);
//     pushSource("_z");
//     switch( diffType ) {
//     case TYPE_DIFF_X:
//       pushSource("(itp)*rij(1,3)");
//       break;
// 
//     case TYPE_DIFF_Y:
//       pushSource("(itp)*rij(2,3)");
//       break;
// 
//     case TYPE_DIFF_Z:
//       pushSource("(itp)*rij(3,3)");
//       break;
// 
//     default:
//       assert(1==0);
//     }
//   }  // if(dim == 3)
//   flushSource();
// 
//   return;
// }
