/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : feelfem90_ecal.cpp
 *  Date     : 2002/02/19
 *  Modified : 
 *  
 *  Purpose  : ecal related program generator
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

#include <cassert>

#include "feelfuncs.hpp"
#include "PM_feelfem90.hpp"
#include "Quadrature.hpp"

//c++20 requires
#include "Element.hpp"
#include "DiscretizedComponent.hpp"
#include "EcalInfo.hpp"

#include "EcalGeneratorTemplate.hpp"


const char *PM_feelfem90::GetEcalRoutineName( int solveNo, int elemNo) 
{
  int stringLength(const char *);
  int length = stringLength("ecal?");
  if(solveNo > 9) {
    length++;
    if(solveNo >99) {
	    std::cerr <<"solve number too large(GetElemRoutineName)\n";
      abortExit(1);
    }
  }

  char *ptr = new char[length];

  sprintf(ptr,"ecal%d",solveNo);

  return(ptr);
}

void PM_feelfem90::pushEcalRoutineName(SolveElement *sePtr)
{
  pushSource("ecal");
  pushSourceInt(sePtr->GetSolveNo());
  pushSource("_");
  pushSourceInt(sePtr->GetElemNo());
  return;
}


// Ecal related functions
void PM_feelfem90::pushEcalArgumentLstInElem(SolveElement *sePtr,
					     orderedPtrList<Variable *>vPtrLst)
{
  listIterator <Variable *>itrV(vPtrLst);
  
  int  femVarFreedom;  // also used for EWISE_A && EWISE_TYPE_INTERPOLATION
  int *nodePattern;

  for(itrV.init(); !itrV ; ++itrV) {

    switch(itrV()->GetType()) {
      
    case VAR_FEM:
      femVarFreedom = itrV()->GetFEMFreedom();
      nodePattern   = sePtr->GetNodePatternForEcal( itrV() );
      for(int i=0;i<femVarFreedom;i++) {
	pushSource(",");
	pushSource("efem_");
	pushSource(itrV()->GetName());
	pushSource("(");
	pushSourceInt(*(nodePattern+i));
	pushSource(")");
      }
      delete [] nodePattern;
      break;

    case VAR_EWISE:              // i is loop variable for element loop
      pushSource(",");
      pushSource("ew_");
      pushSource(itrV()->GetName());
      pushSource("(i)");                   // i is loop variable
      break;

    case VAR_MATERIAL:
      pushSource(",");
      pushSource("m_");
      pushSource(itrV()->GetName());
      pushSource("(matno(i))");            // matno(i) 
      break;

    case VAR_EWISE_A:
      
      if(itrV()->GetEwiseType() == EWISE_TYPE_GAUSSPOINT) {
	pushSource(",");
	pushSource("ew_");
	pushSource(itrV()->GetName());
	pushSource("(1:");                         // partial array of F90
	pushSourceInt(itrV()->GetEWISEFreedom());  
	pushSource(",i)");                         // i is loop variable 
      }
      else {
	femVarFreedom = itrV()->GetEWISEFreedom();
	nodePattern   = sePtr->GetNodePatternForEcal( itrV() );
	for(int i=0;i<femVarFreedom;i++) {
	  pushSource(",");
	  pushSource("eew_");
	  pushSource(itrV()->GetName());
	  pushSource("(");
	  pushSourceInt(*(nodePattern+i));
	  pushSource(")");
	}
	delete [] nodePattern;
      }
      break;

    case VAR_DOUBLE:
    case VAR_INT:
      pushSource(",");
      pushSource("sc_");
      pushSource(itrV()->GetName());
      break;
    
    case VAR_CONST:
      pushSource(",");
      pushSource("co_");
      pushSource(itrV()->GetName());
      break;

    default:
      assert(1==0);
    }
  }
  return;
}

// dependent on TermConvert
void PM_feelfem90::pushEcalArgumentLstInEcal(SolveElement *sePtr,
					     orderedPtrList<Variable *>vPtrLst)
{
  listIterator <Variable *>itrV(vPtrLst);
  
  int  femVarFreedom;  // also used for EWISE_A && EWISE_TYPE_INTERPOLATION
  int *nodePattern;

  for(itrV.init(); !itrV ; ++itrV) {

    switch(itrV()->GetType()) {
      
    case VAR_FEM:
      femVarFreedom = itrV()->GetFEMFreedom();
      nodePattern   = sePtr->GetNodePatternForEcal( itrV() );
      for(int i=0;i<femVarFreedom;i++) {
	pushSource(",");
	pushSource("fem_");
	pushSource(itrV()->GetName());
	pushSource("_");
	pushSourceInt(i+1);
      }
      delete [] nodePattern;
      break;

    case VAR_EWISE:             // material ewise variable (_m is added)
      pushSource(",");
      pushSource("ew_");
      pushSource(itrV()->GetName());
      pushSource("_m");
      break;

    case VAR_MATERIAL:
      pushSource(",");
      pushSource("m_");
      pushSource(itrV()->GetName());
      break;



    case VAR_EWISE_A:
      
      if(itrV()->GetEwiseType() == EWISE_TYPE_GAUSSPOINT) {
	pushSource(",");
	pushSource("ew_");
	pushSource(itrV()->GetName());
      }
      else {
	femVarFreedom = itrV()->GetEWISEFreedom();
	nodePattern   = sePtr->GetNodePatternForEcal( itrV() );
	for(int i=0;i<femVarFreedom;i++) {
	  pushSource(",");
	  pushSource("ew_");
	  pushSource(itrV()->GetName());
	  pushSource("_");
	  pushSourceInt(i+1);
	}
	delete [] nodePattern;
      }
      break;

    case VAR_DOUBLE:
    case VAR_INT:
      pushSource(",");
      pushSource("sc_");
      pushSource(itrV()->GetName());
      break;
    
    case VAR_CONST:
      pushSource(",");
      pushSource("sc_");                      // now co_ is replaced by sc_
      pushSource(itrV()->GetName());
      break;

    default:
      assert(1==0);
    }
  }
  return;
}

// dependent on TermConvert
void PM_feelfem90::EcalArgumentVariableDeclarationLst(SolveElement *sePtr,
						      orderedPtrList
						      <Variable *>&vPtrLst)
{
  listIterator <Variable *>itrV(vPtrLst);
  
  int  femVarFreedom;  // also used for EWISE_A && EWISE_TYPE_INTERPOLATION
  int *nodePattern;

  for(itrV.init(); !itrV ; ++itrV) {
 
    switch(itrV()->GetType()) {
      
    case VAR_FEM:
      femVarFreedom = itrV()->GetFEMFreedom();
      nodePattern   = sePtr->GetNodePatternForEcal( itrV() );
      for(int i=0;i<femVarFreedom;i++) {
	pushReal8sc();
	pushSource("fem_");
	pushSource(itrV()->GetName());
	pushSource("_");
	pushSourceInt(i+1);
	flushSource();
      }
      delete [] nodePattern;
      break;

    case VAR_EWISE:    // material ewise variable (_m is added)         
      pushReal8sc();
      pushSource("ew_");
      pushSource(itrV()->GetName());
      pushSource("_m");
      flushSource();
      break;

    case VAR_MATERIAL:
      pushReal8sc();
      pushSource("m_");
      pushSource(itrV()->GetName());
      flushSource();
      break;

    case VAR_EWISE_A:
      
      if(itrV()->GetEwiseType() == EWISE_TYPE_GAUSSPOINT) {
	pushReal8Array1();                  // F90 partial array, not pointer
	pushSource("ew_");
	pushSource(itrV()->GetName());
	flushSource();
      }
      else {
	femVarFreedom = itrV()->GetEWISEFreedom();
	nodePattern   = sePtr->GetNodePatternForEcal( itrV() );
	for(int i=0;i<femVarFreedom;i++) {
	  pushReal8sc();
	  pushSource("ew_");
	  pushSource(itrV()->GetName());
	  pushSource("_");
	  pushSourceInt(i+1);
	  flushSource();
	}
	delete [] nodePattern;
      }
      break;

    case VAR_DOUBLE:
      pushReal8sc();
      pushSource("sc_");
      pushSource(itrV()->GetName());
      flushSource();
      break;

    case VAR_INT:
      pushInteger4sc();
      pushSource("sc_");
      pushSource(itrV()->GetName());
      flushSource();
      break;
    
    case VAR_CONST:
      pushReal8sc();
      pushSource("sc_");                      // now co_ is replaced by sc_
      pushSource(itrV()->GetName());
      flushSource();
      break;

    default:
      assert(1==0);
    }
  }
  return;
}

// Scheme correspondings
void PM_feelfem90::DoEcalRoutineHeader(SolveElement *sePtr)
{
  doEcalArgumentSequence(sePtr);
  SourceStarters();
  
  // use
  F90useAlways();
  fortImplicit();

  doEcalDeclareArgumentVariables( sePtr );
  //  doEcalVariableDefinition(sePtr);
  return;
}

void PM_feelfem90::doEcalArgumentSequence(SolveElement *sePtr)
{
  pushSource("module mod_");
  pushEcalRoutineName(sePtr);
  flushSource();
  writeSource("contains");
  com();

  pushSource("subroutine ");
  pushEcalRoutineName( sePtr );
  pushSource("(");
  
  int ielemNodes = sePtr->GetIelemNodes();
  for(int i=0;i<ielemNodes;i++) {
    if(i != 0) pushSource(",");
    // x
    pushSource("x");
    pushSourceInt(i+1);

    // y
    if(spaceDim > 1) {
      pushSource(",y");
      pushSourceInt(i+1);
    }

    // z
    if(spaceDim > 2) {
      pushSource(",z");
      pushSourceInt(i+1);
    }
  }  

  orderedPtrList <Variable *> varPtrLst = sePtr->GetVariablePtrLst();
  pushEcalArgumentLstInEcal( sePtr, varPtrLst);
  pushSource(")");

  flushSource();
  return;
}

void PM_feelfem90::doEcalDeclareArgumentVariables(SolveElement *sePtr)
{
  int ielemNodes = sePtr->GetIelemNodes();

  com();

  for(int i=0;i<ielemNodes;i++) {
    pushReal8sc();
    // x
    pushSource("x");
    pushSourceInt(i+1);

    // y
    if(spaceDim > 1) {
      pushSource(",y");
      pushSourceInt(i+1);
    }

    // z
    if(spaceDim > 2) {
      pushSource(",z");
      pushSourceInt(i+1);
    }
    flushSource();
  }  
  com();

  orderedPtrList <Variable *> varPtrLst = sePtr->GetVariablePtrLst();
  EcalArgumentVariableDeclarationLst( sePtr, varPtrLst);
  com();

  return;
}



void PM_feelfem90::DoEcalParameters(SolveElement *sePtr)
{
  // parameters (element freedom and 
  COMMENTlong("Problem dependent parameters");
  pushInteger4pm();
  pushSource("NDF = ");
  pushSourceInt(sePtr->GetNdf());
  flushSource();

  pushInteger4pm();
  pushSource("NDP = ");
  pushSourceInt(sePtr->GetIelemNodes());
  flushSource();

  // parameter for quadratures
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

// auto variables for ecal routine
void PM_feelfem90::DoEcalVariableDefinitions(SolveElement *sePtr )
{
  int solveNo = sePtr->GetSolveNo();
  int elemNo  = sePtr->GetElemNo();

  COMMENTlong("auto variables");

  pushInteger4sc();
  flushSource("i,j");

  pushInteger4sc();
  flushSource("itp");
  com();

  switch(spaceDim) {
  case 1:
    writeSource("1dim????????");
    break;
    
  case 2:
    pushReal8sc();
    flushSource("rj(2,2),rij(2,2)");
    break;
    
  case 3:
    pushReal8sc();
    flushSource("rj(3,3),rij(3,3)");
    break;

  default:
    assert(1==0);
  }

  pushReal8sc();
  flushSource("det,wt,val");

  pushReal8sc();
  if(spaceDim == 1)   flushSource("qx");
  if(spaceDim == 2)   flushSource("qx,qy");
  if(spaceDim == 3)   flushSource("qx,qy,qz");

  com();


  // real(kind=REAL8)   :: ea,eb  (dimension is declared in common block)
  EcalElementMatRHSVariableDeclaration(solveNo,elemNo);
    

  // Quadrature (itp) related variable definition
  COMMENTlong("Gauss-point terms");
  int quadratures = sePtr->GetQuadratures();
  for(int i=0;i<quadratures;i++) {
    DiscretizedComponent *dcPtr;
    dcPtr = sePtr->GetIthDiscretizedComponentPtr(i);
    EcalQuadArgumentVariableDeclaration(sePtr,dcPtr,
					solveNo,elemNo,i+1);
    com();
  }

  // for integrands related variable definition (fem variables)
  COMMENTlong("Integrand terms");
  listIterator <string>itrVI( sePtr->GetEcalIntegrandTermLst() );
  for(itrVI.init(); !itrVI; ++itrVI) {
    pushReal8sc();
    flushSource(itrVI());
  }
  
  // for integrands related variable definition (EWISE_A variables)
  orderedPtrList <Variable *> varPtrLst = sePtr->GetVariablePtrLst();
  listIterator <Variable *>itrV(varPtrLst);
  for(itrV.init(); !itrV; ++itrV ) {
    if(itrV()->GetType() == VAR_EWISE_A) {
      if(itrV()->GetEwiseType() == EWISE_TYPE_GAUSSPOINT) {
	pushReal8sc();
	pushSource("ew_");
	pushSource(itrV()->GetName());
	flushSource("_q");
      }
    }
  }

  // common block  for ea,eb   e.g.  common /em1_1/ ea(NDF,NDF),eb(NDF)
  COMMENTlong("common block for element matrix and load vector");
  EcalElementMatRHSCommon(solveNo, elemNo);
  com();

  // common block for quadratures
  COMMENTlong("common block for quadrature");
  for(int i=0;i<sePtr->GetQuadratures();i++) {
    DiscretizedComponent *dcPtr;
    dcPtr = sePtr->GetIthDiscretizedComponentPtr(i);
    EcalQuadCommon(sePtr, dcPtr, solveNo, elemNo, i+1);
    com();
  }
  comment();
  return;
}

void PM_feelfem90::EcalElementMatRHSVariableDeclaration(int solveNo,int elemNo)
{
  pushReal8sc();
  flushSource("ea,eb");
  return;
}

void PM_feelfem90::EcalElementMatRHSCommon(int solveNo, int elemNo)
{
  pushSource("common /em");
  pushSourceInt(solveNo);
  pushSource("_");
  pushSourceInt(elemNo);
  pushSource("/ ea(NDF,NDF),eb(NDF)");
  flushSource();
}

void PM_feelfem90::
EcalQuadArgumentVariableDeclaration(SolveElement *sePtr,
				    DiscretizedComponent *dcPtr,
				    int solveNo,
				    int elemNo,
				    int quadNo) 
  // caution, quadNO starts 1
{
  // for gx
  pushReal8sc();
  pushSource("gx_");
  pushSourceInt(quadNo);
  
  // for gy
  if(spaceDim > 1) {
    pushSource(",gy_");
    pushSourceInt(quadNo);
  }

  // for gz
  if(spaceDim > 2) {
    pushSource(",gz_");
    pushSourceInt(quadNo);
  }

  // for w (weight at each quadrature point)
  pushSource(",w_");
  pushSourceInt(quadNo);
  flushSource();
  
  com();

  // for quad commons
  EcalInfo *eiPtr = sePtr->GetIthEcalInfoPtr( quadNo -1);
  listIterator <string>itrVQ( eiPtr->GetCommonTermLst());
  for(itrVQ.init(); !itrVQ ; ++itrVQ ) {
    pushReal8sc();
    flushSource(itrVQ());
  }

  return;
}


void PM_feelfem90::EcalQuadCommon(SolveElement *sePtr,
				  DiscretizedComponent *dcPtr,
				  int solveNo,int elemNo,int quadNo)
{
  //  Quadrature *qPtr;
  //  assert(quadNo >0);
  //  qPtr = sePtr->GetIthQuadraturePtr(quadNo - 1 );

  pushSource("common /em");
  pushSourceInt(sePtr->GetSolveNo());
  pushSource("_");
  pushSourceInt(sePtr->GetElemNo());
  pushSource("_");
  pushSourceInt(quadNo);
  pushSource("/");

    // first line, primitives (coordinate and  weight value, i has quad No.)

    // gx
  pushSource("gx_");
  pushSourceInt(quadNo);

  pushSource("(NPG");
  pushSourceInt(quadNo);
  pushSource(")");


  // gy
  if(spaceDim>1) {
    pushSource(",gy_");
    pushSourceInt(quadNo);

    pushSource("(NPG");
    pushSourceInt(quadNo);
    pushSource(")");

  }

  // gz
  if(spaceDim>2) {
    pushSource(",gz_");
    pushSourceInt(quadNo);

    pushSource("(NPG");
    pushSourceInt(quadNo);
    pushSource(")");
  }
    
  pushSource(",w_");
  pushSourceInt(quadNo);
  pushSource("(NPG");
  pushSourceInt(quadNo);
  pushSource(")");
    
  pushSource(" &");
  flushSource();
  //          common /em?_?_?/
  // for quad commons
  EcalInfo *eiPtr = sePtr->GetIthEcalInfoPtr( quadNo -1);
  listIterator <string>itrVQ( eiPtr->GetCommonTermLst());
  for(itrVQ.init(); !itrVQ ; ++itrVQ ) {
    pushSource(",");
    pushSource(itrVQ());
    pushSource("(NPG");
    pushSourceInt(quadNo);
    pushSource(")");
  }
  flushSource();

  return;
}

void PM_feelfem90::DoEcalReturnSequence(SolveElement *sePtr)
{
  pushSource("end subroutine ");
  pushEcalRoutineName(sePtr);
  flushSource();

  pushSource("end module mod_");
  pushEcalRoutineName(sePtr);
  flushSource();
  
  return;
}

void PM_feelfem90::DoEcalElementMatInitialize(SolveElement *sePtr)
{
  writeSource("do i=1,NDF");
  writeSource(" eb(i) = 0.0d0");
  writeSource("end do");
  com();

  writeSource("do j=1,NDF");
  writeSource(" do i=1,NDF");
  writeSource("  ea(i,j) = 0.0d0");
  writeSource(" end do");
  writeSource("end do");
  comment();
  
  return;
}

void PM_feelfem90::DoEcalQuadLoopStart(int quadNo, SolveElement *sePtr)
{
  comment();
  pushSource("! Quadrature No.");
  pushSourceInt(quadNo);
  flushSource();
  comment();

  pushSource("do itp=1,NPG");
  pushSourceInt(quadNo);
  flushSource();
  com();

  return;
}

void PM_feelfem90::DoEcalQuadLoopEnd(int quadNo, SolveElement *sePtr)
{
  com();
  pushSource("end do    ! end of Quad. No.");
  pushSourceInt(quadNo);
  flushSource();
  com();
}


void PM_feelfem90::DoEcalCalcJacobian(int quadNo, SolveElement *sePtr)
{
  Element *parametricElemPtr = sePtr->GetParametricElementPtr();
  int     *ndPattern         = sePtr->GetNodePatternForEcal(parametricElemPtr);
  int      freedom           = parametricElemPtr->GetElementFreedom();

  
  switch(spaceDim) {

  case 1:
    assert(1==0);
    break;

  case 2:
    // for rj(1,1)
    pushSource(            "  rj(1,1) = ");
    pushEcalJacobiSub(quadNo,freedom,ndPattern,"x","x",parametricElemPtr->GetName());
    flushSource();

    // for rj(1,2)
    pushSource(            "  rj(1,2) = ");
    pushEcalJacobiSub(quadNo,freedom,ndPattern,"y","x",parametricElemPtr->GetName());
    flushSource();

    // for rj(2,1)
    pushSource(            "  rj(2,1) = ");
    pushEcalJacobiSub(quadNo,freedom,ndPattern,"x","y",parametricElemPtr->GetName());
    flushSource();

    // for rj(2,2)
    pushSource(            "  rj(2,2) = ");
    pushEcalJacobiSub(quadNo,freedom,ndPattern,"y","y",parametricElemPtr->GetName());
    flushSource();

    com();

    writeSource("  det = rj(1,1)*rj(2,2)-rj(1,2)*rj(2,1)");
    com();

    writeSource("  rij(1,1) =  rj(2,2)/det");
    writeSource("  rij(2,2) =  rj(1,1)/det");
    writeSource("  rij(1,2) = -rj(1,2)/det");
    writeSource("  rij(2,1) = -rj(2,1)/det");
    com();

    break;

  case 3:
    // for rj(1,1)
    pushSource(            "  rj(1,1) = ");
    pushEcalJacobiSub(quadNo,freedom,ndPattern,"x","x",parametricElemPtr->GetName());
    flushSource();

    // for rj(1,2)
    pushSource(            "  rj(1,2) = ");
    pushEcalJacobiSub(quadNo,freedom,ndPattern,"y","x",parametricElemPtr->GetName());
    flushSource();

    // for rj(1,3)
    pushSource(            "  rj(1,3) = ");
    pushEcalJacobiSub(quadNo,freedom,ndPattern,"z","x",parametricElemPtr->GetName());
    flushSource();

    // for rj(2,1)
    pushSource(            "  rj(2,1) = ");
    pushEcalJacobiSub(quadNo,freedom,ndPattern,"x","y",parametricElemPtr->GetName());
    flushSource();

    // for rj(2,2)
    pushSource(            "  rj(2,2) = ");
    pushEcalJacobiSub(quadNo,freedom,ndPattern,"y","y",parametricElemPtr->GetName());
    flushSource();

    // for rj(2,3)
    pushSource(            "  rj(2,3) = ");
    pushEcalJacobiSub(quadNo,freedom,ndPattern,"z","y",parametricElemPtr->GetName());
    flushSource();

    // for rj(3,1)
    pushSource(            "  rj(3,1) = ");
    pushEcalJacobiSub(quadNo,freedom,ndPattern,"x","z",parametricElemPtr->GetName());
    flushSource();

    // for rj(3,2)
    pushSource(            "  rj(3,2) = ");
    pushEcalJacobiSub(quadNo,freedom,ndPattern,"y","z",parametricElemPtr->GetName());
    flushSource();

    // for rj(3,3)
    pushSource(            "  rj(3,3) = ");
    pushEcalJacobiSub(quadNo,freedom,ndPattern,"z","z",parametricElemPtr->GetName());
    flushSource();
    
    com();

    writeSource("  det =  rj(1,1)*rj(2,2)*rj(3,3)  &");
    writeSource("       + rj(1,2)*rj(2,3)*rj(3,1)  &");
    writeSource("       + rj(1,3)*rj(2,1)*rj(3,2)  &");
    writeSource("       - rj(1,1)*rj(2,3)*rj(3,2)  &");
    writeSource("       - rj(1,2)*rj(2,1)*rj(3,3)  &");
    writeSource("       - rj(1,3)*rj(2,2)*rj(3,1)");
    com();

    writeSource("  rij(1,1)=      (rj(2,2)*rj(3,3)-rj(2,3)*rj(3,2))/det");
    writeSource("  rij(1,2)= -1.0*(rj(1,2)*rj(3,3)-rj(1,3)*rj(3,2))/det");
    writeSource("  rij(1,3)=      (rj(1,2)*rj(2,3)-rj(1,3)*rj(2,2))/det");
    writeSource("  rij(2,1)= -1.0*(rj(2,1)*rj(3,3)-rj(2,3)*rj(3,1))/det");
    writeSource("  rij(2,2)=      (rj(1,1)*rj(3,3)-rj(1,3)*rj(3,1))/det");
    writeSource("  rij(2,3)= -1.0*(rj(1,1)*rj(2,3)-rj(1,3)*rj(2,1))/det");
    writeSource("  rij(3,1)=      (rj(2,1)*rj(3,2)-rj(2,2)*rj(3,1))/det");
    writeSource("  rij(3,2)= -1.0*(rj(1,1)*rj(3,2)-rj(1,2)*rj(3,1))/det");
    writeSource("  rij(3,3)=      (rj(1,1)*rj(2,2)-rj(1,2)*rj(2,1))/det");
    com();
    break;

  default:
    assert(1==0);
  }

  pushSource("  wt = det * w_");
  pushSourceInt(quadNo);
  flushSource("(itp)");
  com();
  
  delete [] ndPattern;
  return;
}

void PM_feelfem90::pushEcalJacobiSub(int quadNo,int freedom,int *ndPattern,
		       const char *coor, const char*derivative, const char*nm)
{
  for(int i=0;i<freedom;i++) {
    if(i != 0) {
      pushSource("+");
    }

    pushSource(coor);                // x
    pushSourceInt(*(ndPattern+i));   // 2
    pushSource("*");                 // *
    pushSource("r");                 // r
    pushSource(nm);                  // P1
    pushSource("_");                 // _
    pushSourceInt(i+1);              // 2     
    pushSource("_");
    pushSource(derivative);
    pushSource("_");
    pushSourceInt(quadNo);
    pushSource("(itp)");
  }
  return;
}

void PM_feelfem90::pushEcalCoordSub(int quadNo, Element *ePtr,
				    SolveElement *sePtr,const char *coord)
{
  Element *parametricElemPtr = sePtr->GetParametricElementPtr();

  int  freedom;
  int *ndPattern;
  
  freedom = parametricElemPtr->GetElementFreedom();
  ndPattern = sePtr->GetNodePatternForEcal(parametricElemPtr);

  for(int i=0;i<freedom;i++) {
    if(i != 0) {
      pushSource("+");
    }
    pushSource(coord);                // x
    pushSourceInt(*(ndPattern+i));   // 2
    pushSource("*");                 // *
    pushSource("r");                 // r
    pushSource(ePtr->GetName());     // P1
    pushSource("_");                 // _
    pushSourceInt(i+1);              // 2     
    pushSource("_");
    pushSourceInt(quadNo);
    pushSource("(itp)");
  }

  delete [] ndPattern;

  return;
}

void PM_feelfem90::DoEcalSetValAtGaussP(int quadNo, SolveElement *sePtr)
{
  DiscretizedComponent *dcPtr = sePtr->GetIthDiscretizedComponentPtr(quadNo-1);
  EcalInfo *eiPtr = sePtr->GetIthEcalInfoPtr(quadNo -1 );
  Element *parametricElemPtr = sePtr->GetParametricElementPtr();

  
  comment();

  // for qx,qy,qz
  if(eiPtr->IsUseX() == YES) {
    pushSource("  qx=");
    pushEcalCoordSub(quadNo,parametricElemPtr,sePtr, "x");
    flushSource();
  }
  if(eiPtr->IsUseY() == YES) {
    pushSource("  qy=");
    pushEcalCoordSub(quadNo,parametricElemPtr,sePtr, "y");
    flushSource();
  }
  if(eiPtr->IsUseZ() == YES) {
    pushSource("  qz=");
    pushEcalCoordSub(quadNo,parametricElemPtr,sePtr, "z");
    flushSource();
  }

  if(eiPtr->IsUseX() == YES ||eiPtr->IsUseY() == YES ||eiPtr->IsUseZ() == YES){
    com();
  }

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
	
	pushSource("  q");
	pushSource(itrE()->GetName());
	pushSource("_");
	pushSourceInt(i+1);

	pushSource("= r");
	pushSource(itrE()->GetName());
	pushSource("_");
	pushSourceInt(i+1);
	pushSource("_");
	pushSourceInt(quadNo);
	flushSource("(itp)");
      }
    }

    // function dx
    for(int i=0;i<freedom;i++) {
      sprintf(buf,"q%s_%d_x",itrE()->GetName(), i+1);
      term = buf;

      if(dcPtr->IsUsedIntegrandTerm( term )) {
	
	pushEcalDiffSub_1st(quadNo,itrE(),spaceDim,i+1,TYPE_DIFF_X);
	flushSource();
      }
    }


    // function itself  dy
    for(int i=0;i<freedom;i++) {
      sprintf(buf,"q%s_%d_y",itrE()->GetName(), i+1);
      term = buf;

      if(dcPtr->IsUsedIntegrandTerm( term )) {

	pushEcalDiffSub_1st(quadNo,itrE(),spaceDim,i+1,TYPE_DIFF_Y);
	flushSource();
      }	
    }
    
    // function itself  dz
    if(spaceDim == 3) {
      for(int i=0;i<freedom;i++) {
	sprintf(buf,"q%s_%d_z",itrE()->GetName(), i+1);
	term = buf;

	if(dcPtr->IsUsedIntegrandTerm( term )) {
	
	  pushEcalDiffSub_1st(quadNo,itrE(),spaceDim,i+1,TYPE_DIFF_Z);
	  flushSource();

	}
      }
    }
  }  


  // ewise variables (EWISE_A, TYPE_GAUSSPOINT, ewise-quad)
  orderedPtrList <Variable *> varPtrLst = sePtr->GetVariablePtrLst();
  listIterator <Variable *>itrV(varPtrLst);
  for(itrV.init(); !itrV; ++itrV ) {
    if(itrV()->GetType() == VAR_EWISE_A) {
      if(itrV()->GetEwiseType() == EWISE_TYPE_GAUSSPOINT) {
	com();
	pushSource("  ew_");
	pushSource(itrV()->GetName());
	pushSource("_q = ew_");
	pushSource(itrV()->GetName());
	flushSource("(itp)");
      }
    }
  }

  comment();

  return;

}



void PM_feelfem90::DoEcalCalcElementMatRHS(int quadNo, SolveElement *sePtr)
{
  comment();

  EcalInfo *eiPtr = sePtr->GetIthEcalInfoPtr(quadNo -1 );
  DiscretizedComponent *dcPtr = sePtr->GetIthDiscretizedComponentPtr(quadNo-1);

  int rows    = dcPtr->GetRows();
  int columns = dcPtr->GetColumns();

  for(int i=0;i<rows;i++) {
    for(int j=0;j<columns;j++) {

      // symmetry expansion comes here.
      if(dcPtr->IsZeroMatCoeff(i+1,j+1)) {
	pushSource("! ea(");      
	pushSourceInt(i+1);
	pushSource(",");
	pushSourceInt(j+1);
	pushSource(") is ");
	pushSourceHAT(dcPtr->GetElementMatIJ(i+1,j+1));   // conversion ^ -> **
	flushSource();
      }
      else {

	pushSource("  ea(");
	pushSourceInt(i+1);
	pushSource(",");
	pushSourceInt(j+1);
	pushSource(")=ea(");
	pushSourceInt(i+1);
	pushSource(",");
	pushSourceInt(j+1);
	pushSource(")+(");
	
	pushSourceHAT(dcPtr->GetElementMatIJ(i+1,j+1));   // conversion ^ -> **
	
	flushSource(")*wt");
      }
      com();
    }
  }
  com();


  for(int i=0;i<rows;i++) {

    if(dcPtr->IsZeroRHSVec( i+1 ) == YES) {

      pushSource("! eb(");
      pushSourceInt(i+1);
      pushSource(") is ");
      pushSourceHAT(dcPtr->GetElementLoadI(i+1));   // conversion ^ -> **
      flushSource();
    }
    else {
      pushSource("  eb(");
      pushSourceInt(i+1);
      pushSource(")=eb(");
      pushSourceInt(i+1);
      pushSource(")+(");

      pushSourceHAT(dcPtr->GetElementLoadI(i+1));   // conversion ^ -> **
      flushSource(")*wt");
    }

    com();
  }

  comment();

  return;
}


void PM_feelfem90::pushEcalDiffSub_1st(int quadNo,Element *ePtr,int dim,
				       int no,int diffType              )
{
  pushSource("  q");
  pushSource(ePtr->GetName());
  pushSource("_");  
  pushSourceInt(no);
  pushSource("_");
  
  switch( diffType ) {
  case TYPE_DIFF_X:
    pushSource("x");
    break;

  case TYPE_DIFF_Y:
    pushSource("y");
    break;

  case TYPE_DIFF_Z:
    pushSource("z");
    break;

  default:
    assert(1==0);
  }

  // first (dx)
  pushSource(" = r");
  pushSource(ePtr->GetName());
  pushSource("_");
  pushSourceInt(no);
  pushSource("_x_");
  pushSourceInt(quadNo);
  switch( diffType ) {
  case TYPE_DIFF_X:
    pushSource("(itp)*rij(1,1)");
    break;

  case TYPE_DIFF_Y:
    pushSource("(itp)*rij(2,1)");
    break;

  case TYPE_DIFF_Z:
    pushSource("(itp)*rij(3,1)");
    break;

  default:
    assert(1==0);
  }

  assert(dim == 2 || dim == 3);

  // second (dy)
  pushSource("+r");
  pushSource(ePtr->GetName());
  pushSource("_");
  pushSourceInt(no);
  pushSource("_y_");
  pushSourceInt(quadNo);
  switch( diffType ) {
  case TYPE_DIFF_X:
    pushSource("(itp)*rij(1,2)");
    break;

  case TYPE_DIFF_Y:
    pushSource("(itp)*rij(2,2)");
    break;

  case TYPE_DIFF_Z:
    pushSource("(itp)*rij(3,2)");
    break;

  default:
    assert(1==0);
  }
  
  if(dim == 3) {
    // second (dz)
    pushSource("+r");
    pushSource(ePtr->GetName());
    pushSource("_");
    pushSourceInt(no);
    pushSource("_z_");
    pushSourceInt(quadNo);
    switch( diffType ) {
    case TYPE_DIFF_X:
      pushSource("(itp)*rij(1,3)");
      break;

    case TYPE_DIFF_Y:
      pushSource("(itp)*rij(2,3)");
      break;

    case TYPE_DIFF_Z:
      pushSource("(itp)*rij(3,3)");
      break;

    default:
      assert(1==0);
    }
  }  // if(dim == 3)
  return;
}
