/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNquadrature_CHECK.cpp
 *  Date     : 2001/12/12
 *  Modified : 
 *  
 *  Purpose  : Evaluate x,y,z and weight, convert numerical value
 *             This is a copy of 'mesh_check_eval.cpp'
 *  
 */

#include <stream.h>

#include "list.hpp"
#include "string.hpp"
#include "feelfuncs.hpp"

#include "../../check/check_funcs.hpp"

// ginac
#include "quadratureEvalGinac.hpp"

#include "SNquadrature.hpp"
#include "SNquadratureDoubleVar.hpp"
#include "SNquadratureAssignment.hpp"
#include "SNquadratureGaussP.hpp"

// Set etype code from specified string 'elementShape'
int SNquadrature::SetEtype(void)
{

  // triangle
  if(elementShape ==  ETYPE_TRI_NAME) {
    etype     = ELEMENT_TYPE_TRI;
    dimension = 2;
    return(0);
  }

  // rectangle
  if(elementShape ==  ETYPE_RECT_NAME) {
    etype     = ELEMENT_TYPE_RECT;
    dimension = 2;

    return(0);
  }

  // line
  if(elementShape ==  ETYPE_LINE_NAME) {
    etype     = ELEMENT_TYPE_LINE;
    dimension = 1;
    return(0);
  }

  // point
  if(elementShape ==  ETYPE_POINT_NAME) {
    etype     = ELEMENT_TYPE_POINT;
    dimension = 0;
    return(0);
  }

  // tetrahedra
  if(elementShape ==  ETYPE_TETRA_NAME) {
    etype     = ELEMENT_TYPE_TETRA;
    dimension = 3;
    return(0);
  }

  // hexahedra
  if(elementShape ==  ETYPE_CUBE_NAME) {
    etype     = ELEMENT_TYPE_CUBE;
    dimension = 3;
    return(0);
  }

  // error
  return(1);  
}


int SNquadrature::CheckGaussPDimension(void)
{
  int errors;
  
  errors = 0;


  listIterator <SNquadratureGaussP *>itr(gaussPPtrLst);

  for(itr.init();  !itr   ;++itr ) {
    if( dimension != itr()->getSpaceDimension() ) {
      SystemErrorA((SNunit *)itr() , "Wrong dimension for coordinates.");
      errors++;
    }
  }
  
  if( errors  != 0) {
    return(YA);           // error
  }
  else {
    return(NICHT);
  }

}

int SNquadrature::EvalExpressions( void )
{
  quadratureEvalGinac evaluator;

  listIterator <SNunit *>itr(dblAndAssignPtrLst);

  int errorFlag,ret;
  errorFlag = 0;
  
  for(itr.init(); !itr; ++itr) {

    switch(itr()->GetType()) {

    case SN_QUADRATUREDOUBLEVAR:
      ret = evaluator.quadratureDoubleVar( (SNquadratureDoubleVar *)itr());
      if(ret) {
	SystemErrorA( (SNunit *) itr()," returned non zero.");
      }
      errorFlag += ret;
      break;

    case SN_QUADRATUREASSIGNMENT:
      ret = evaluator.quadratureAssignment( (SNquadratureAssignment *)itr());
      if(ret) {
	SystemErrorANameA(itr(),"Assignment of ",
			  " cannot be evaluated.");
      }
      errorFlag += ret;
      break;

    default:
      assert(1==0);
      break;
    }
  }


  // Evaluate gauss point information

  listIterator <SNquadratureGaussP *>itrG(gaussPPtrLst);
    
  int count_for_quad_point;
  count_for_quad_point = 0;

  for(itrG.init(); !itrG ;  ++itrG) {

    count_for_quad_point++;  // used in error report

    ret = evaluator.quadratureGaussP( (SNquadratureGaussP *)itrG());
    if(ret != 0) {
      SystemErrorAIA((SNunit *)itrG(),
		     "Quadrature point No.",
		     count_for_quad_point,
		     " cannot be evaluated."  );
    }
    errorFlag += ret;
    
  }

  return(errorFlag);
}

// check Gauss point range
int SNquadrature::CheckGaussPRange()
{
  int errors;

  errors = 0;

  if(etype == 0)  return(1);        // etype == 0 means error

  listIterator <SNquadratureGaussP *> itr(gaussPPtrLst);

  int no = 0;
  for(itr.init(); !itr ; ++itr ) {
    double xi,eta,zeta;

    switch(etype) {

    case ELEMENT_TYPE_POINT:
    case ELEMENT_TYPE_LINE:
      itr()->getCoordinate(xi);
      break;

    case ELEMENT_TYPE_TRI:
    case ELEMENT_TYPE_RECT:
      itr()->getCoordinate(xi,eta);
      break;

    case ELEMENT_TYPE_TETRA:
    case ELEMENT_TYPE_CUBE:
      itr()->getCoordinate(xi,eta,zeta);
      break;

    default:
      assert(1==0);
      break;
    }



    int checkRegionFlag;

    checkRegionFlag = NICHT;
    switch(etype) {

    case ELEMENT_TYPE_POINT:
    case ELEMENT_TYPE_LINE:
      if(xi < -1.0 || xi > 1.0) {
	checkRegionFlag = YA;
      }
      break;

    case ELEMENT_TYPE_TRI:
      if(xi < 0.0 || eta < 0.0 || xi+eta > 1.0) {
	checkRegionFlag = YA;
      }
      break;
	

    case ELEMENT_TYPE_RECT:
      if(xi < -1.0 || eta < -1.0 || xi > 1.0 || eta > 1.0) {
	checkRegionFlag = YA;
      }
      break;

    case ELEMENT_TYPE_TETRA:
      if(xi < 0.0 || eta < 0.0 || zeta < 0.0 ||  xi+eta+zeta> 1.0) {
	checkRegionFlag = YA;
      }
      break;
      
    case ELEMENT_TYPE_CUBE:
      if(xi < -1.0 || eta < -1.0 || zeta < -1.0 ||
	 xi >  1.0 || eta >  1.0 || zeta >  1.0    ) {
	checkRegionFlag = YA;
      }
      break;

    default:
      assert(1==0);
      break;
    }

    if(checkRegionFlag == YA) {
      SystemErrorA((SNunit *)itr(),"Specified quad-point is out of reference element.");
      errors++;
    }

  }  // iter for GaussP iterator

  return(errors);
}

// check consistency function should be called after evaluation.
int SNquadrature::CheckConsistency()
{
  double weightSum,idealSum;
  
  weightSum = 0.0;

  listIterator <SNquadratureGaussP *> itr(gaussPPtrLst);

  for(itr.init(); !itr ; ++itr ) {
    weightSum += itr()->getWeight();
  }

  switch(etype) {

  case ELEMENT_TYPE_POINT:
    idealSum = 1.0;
    break;
    
  case ELEMENT_TYPE_LINE:
    idealSum = 2.0;
    break;

  case ELEMENT_TYPE_TRI:
    idealSum = 0.5;
    break;

  case ELEMENT_TYPE_RECT:
    idealSum = 4.0;
    break;

  case ELEMENT_TYPE_TETRA:
    idealSum = 0.5 * 1.0 / 3.0;
    break;
      
  case ELEMENT_TYPE_CUBE:
    idealSum = 8.0;
    break;

  default:
    assert(1==0);
    break;
  }

  //  cerr << "name =" << name << "  weightSum=" << weightSum << " ratio=" 
  //       << weightSum/idealSum << endl;
  
  if(weightSum / idealSum < 0.9999 || weightSum / idealSum > 1.0001) {
    return(YA);
  }
  else {
    return(NICHT);
  }
}

