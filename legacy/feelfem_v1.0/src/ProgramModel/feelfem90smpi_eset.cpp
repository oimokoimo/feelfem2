/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2003
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : feelfem90smpi_eset.cpp
 *  Date     : 2003/01/04 (copied from feelfem90)
 *  Modified : 
 *  
 *  Purpose  : eset generator
 *  
 */

#include <stdio.h>   // for BUFSIZ
#include "PM_feelfem90smpi.hpp"
#include "Quadrature.hpp"
#include "Element.hpp"
#include "EcalInfo.hpp"

#define  ESET_NAME  "eset%d_%d_%d"
#define  ESET_FNAME  "eset%d_%d_%d.f90"


void PM_feelfem90smpi::GenerateCoSolveEcalRoutines(SolveElement *sePtr)
{
  GenerateEsetRoutines( sePtr );
  return;
}

void PM_feelfem90smpi::pushEsetRoutineName(int solveNo,int solveElementNo,
				       int quadNo                      )
{
  char buf[BUFSIZ];
  sprintf(buf,ESET_NAME,solveNo,solveElementNo,quadNo);
  pushSource(buf);

  return;
}

void PM_feelfem90smpi::GenerateEsetRoutines(SolveElement *sePtr)
{

  int solveNo        = sePtr->GetSolveNo();
  int solveElementNo = sePtr->GetElemNo();

  int quads          = sePtr->GetQuadratures();


  for(int i=0;i<quads;i++) {
    int quadNo;
    quadNo = i + 1;

    EsetInfo *esetInfoPtr = sePtr->GetIthEsetInfoPtr(i);

    char fname[BUFSIZ];
    sprintf(fname,ESET_FNAME,solveNo,solveElementNo,quadNo);
    OpenSource(fname,LINKLEVEL_ESET);

    pushSource("module mod_");
    pushEsetRoutineName(solveNo,solveElementNo,quadNo);
    flushSource();
    
    writeSource("contains");
    com();

    pushSource("subroutine ");
    pushEsetRoutineName(solveNo,solveElementNo,quadNo);

    // argument variable list

    flushSource();

    com();

    comment();
    
    F90useAlways();
    fortImplicit();

    com();

    comment();

    // parameter for NPG?
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
    com();

    // argument variable definitions..
    COMMENTlong("auto variables");
    writeInteger4sc("itp");
    com();
    

    // common argument variable declaration...
    COMMENTlong("common variables");
    DiscretizedComponent *dcPtr = sePtr->GetIthDiscretizedComponentPtr(i);

    EcalQuadArgumentVariableDeclaration(sePtr,dcPtr,solveNo,solveElementNo,
					quadNo);

    comment();
    // common argument
    
    EcalQuadCommon(sePtr,dcPtr,solveNo,solveElementNo,quadNo);

    comment();

    // set quadrature point and weight
    int points; 
    int dim;

    points = qPtr->GetQuadraturePoints();
    dim    = qPtr->GetDimension();

    for(int ip=0;ip<points;ip++) {
      
      // gx
      pushSource("gx_");
      pushSourceInt(quadNo);
      pushSource("(");
      pushSourceInt( ip+1 );
      pushSource(") =");
      pushSourceDbl( qPtr->GetIthXi( ip ) );
      flushSource();

      // gy
      if(dim > 1) {
	pushSource("gy_");
	pushSourceInt(quadNo);
	pushSource("(");
	pushSourceInt( ip+1 );
	pushSource(") =");
	pushSourceDbl( qPtr->GetIthEta( ip ) );
	flushSource();
      }

      // gz
      if(dim > 2) {
	pushSource("gz_");
	pushSourceInt(quadNo);
	pushSource("(");
	pushSourceInt( ip+1 );
	pushSource(") =");
	pushSourceDbl( qPtr->GetIthZeta( ip ) );
	flushSource();
      }
      
      pushSource(" w_");
      pushSourceInt(quadNo);
      pushSource("(");
      pushSourceInt( ip+1 );
      pushSource(") =");
      pushSourceDbl( qPtr->GetIthWeight( ip ) );
      flushSource();
      
      com();
    }
   
    comment();

    
    // loop for Quadrature
    pushSource("do itp=1,NPG");
    pushSourceInt(quadNo);
    flushSource();
    com();

    // evaluation of interpolation funcs at each quadPoints
    doEsetCalcInterpolation(sePtr,dcPtr,solveNo,solveElementNo,quadNo);
    
    com();
    com();
    writeSource("end do");

    comment();
    com();

    writeSource("return");
    com();

    pushSource("end subroutine ");
    pushEsetRoutineName(solveNo,solveElementNo,quadNo);
    flushSource();

    pushSource("end module mod_");
    pushEsetRoutineName(solveNo,solveElementNo,quadNo);
    flushSource();

    CloseSource();
  }

  return;
}

void PM_feelfem90smpi::doEsetCalcInterpolation(SolveElement *sePtr,
					   DiscretizedComponent *dcPtr,
					   int solveNo,
					   int solveElementNo,
					   int quadNo)
{
  EcalInfo *eiPtr = sePtr->GetIthEcalInfoPtr( quadNo -1);

  listIterator <EcalEvalPair *>itrEEP( eiPtr->GetEcalEvalPairPtrLst() );

  for(itrEEP.init(); !itrEEP ; ++itrEEP) {
    Element *ePtr = itrEEP()->GetElementPtr();
    int      type = itrEEP()->GetType();

    doEsetCalcInterpolationSub( quadNo,
				sePtr,
				ePtr,
				type   );
  }

  return;
}

void PM_feelfem90smpi::doEsetCalcInterpolationSub( int quadNo,
					       SolveElement *sePtr,
					       Element *ePtr,
					       int type             )
{
  int freedom = ePtr->GetElementFreedom();
  
  // Make TermConvert

  TermConvert tc;

  char buf[38];

  // for r  ===> _m1
  sprintf(buf,"gx_%d(itp)",quadNo);
  tc.StoreMetaPair( "r" , buf);

  // for s  ===> _m2
  sprintf(buf,"gy_%d(itp)",quadNo);
  tc.StoreMetaPair( "s" , buf);

  // for t  ===> _m3
  sprintf(buf,"gz_%d(itp)",quadNo);
  tc.StoreMetaPair( "t" , buf);


  for(int i=0;i<freedom;i++) {
    Interpolation *iPtr = ePtr->GetIthInterpolationPtr(i);

    pushSource("  ");
    pushSource("r");
    pushSource(ePtr->GetName());
    pushSource("_");
    pushSourceInt(i+1);

    switch(type) {

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

    pushSource("_");
    pushSourceInt(quadNo);

    pushSource("(itp)=");


    string exprStrForGinac = tc.convertExpressionString(iPtr->GetExprString());

    void esetDerivative(char *,int,char *,int);
    char exprBuf[MAX_FORMULA_BUF];

    switch(type) {
    case TYPE_DIFF_ZERO:
      exprStrForGinac = tc.ReverseConvertExpressionString(exprStrForGinac);
      break;

    case TYPE_DIFF_X:
    case TYPE_DIFF_Y:
    case TYPE_DIFF_Z:
      esetDerivative( exprStrForGinac, type, exprBuf,MAX_FORMULA_BUF );
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
