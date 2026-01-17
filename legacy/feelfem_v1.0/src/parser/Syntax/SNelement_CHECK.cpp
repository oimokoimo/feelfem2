/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNelement_CHECK.cpp
 *  Date     : 2001/12/21             (file divided into _CHECK.cpp)
 *  Modified : 2001/12/31
 *  
 *  Purpose  : int setEtype(void);
 *             int CheckSystemVariables(void)
 *             int EvalExpressions(void)
 *             int ParseInterpolates(void)
 *  
 *  
 */
#include <iostream.h>

#include "../../check/check_funcs.hpp"

#include "SNunit.hpp"
#include "SNelement.hpp"
#include "SNelementDoubleVar.hpp"
#include "SNelementAssignment.hpp"

#include "Node.hpp"

#include "elementEvalGinac.hpp"

//      check routines  (called from element_check()  )

int SNelement::setEtype(void)    // also set inside SNelementIntp::etype
{

  // point
  if(elementShape ==  ETYPE_POINT_NAME) {
    etype = ELEMENT_TYPE_POINT;
    dimension = 0;
    setIntpEtype();
    return(0);
  }

  // line
  if(elementShape ==  ETYPE_LINE_NAME) {
    etype = ELEMENT_TYPE_LINE;
    dimension = 1;
    setIntpEtype();
    return(0);
  }

  // triangle
  if(elementShape ==  ETYPE_TRI_NAME) {
    etype = ELEMENT_TYPE_TRI;
    dimension = 2;
    setIntpEtype();
    return(0);
  }

  // rectangle
  if(elementShape ==  ETYPE_RECT_NAME) {
    etype = ELEMENT_TYPE_RECT;
    dimension = 2;
    setIntpEtype();
    return(0);
  }

  // tetrahedra
  if(elementShape ==  ETYPE_TETRA_NAME) {
    etype = ELEMENT_TYPE_TETRA;
    dimension = 3;
    setIntpEtype();
    return(0);
  }

  // hexahedra
  if(elementShape ==  ETYPE_CUBE_NAME) {
    etype = ELEMENT_TYPE_CUBE;
    dimension = 3;
    setIntpEtype();
    return(0);
  }


  return(1);
}                  // end of setEtype()

// check node coordinate consistency
int SNelement::CheckNodeDimension()
{
  int errors;

  errors = 0;
  
  listIterator <SNelementIntp *> itr(intpPtrLst);

  for(itr.init(); !itr ; ++itr) {

    if(dimension != itr()->getSpaceDimension()) {
      SystemErrorA((SNunit *)itr(),"Node coordinate has a wrong dimension.");
      errors++;
    }
  }

  return(errors);

}   // end of CheckNodeDimension()



// system variables are, x_1,x_2,,,, y_1,y_2, ...
int SNelement::CheckSystemVariables(void)
{
  int ret,errors;
  
  errors = 0;
  

  if(etype == 0) {
    cerr << "Cannot check when etype==0 [SNelement::CheckSystemVairalbes]\n";
    return(1);
  }

  listIterator <SNunit *>itr(dblAndAssignPtrLst);

  SNelementDoubleVar  *snedvPtr;
  //  SNelementAssignment *sneasPtr;

  for(itr.init(); !itr ; ++itr ) {
    
    switch( itr()->GetType()) {

    case SN_ELEMENTDOUBLEVAR:
      snedvPtr = (SNelementDoubleVar *)itr();
      ret      = snedvPtr->CheckSystemVariables(etype);
      if(ret != 0) {
	SystemErrorNameA(itr(), " is reserved vertex variable.");
	errors++;
      }
      break;
      

    default:
      break;
    }
  }

  return(errors);
}


// EvalExpression (for node coordinates and doubleVars, etc.)
// 
int SNelement::EvalExpressions(void)
{
  int errFlag,ret;
  
  errFlag = 0;
  
  elementEvalGinac evaluator;

  // node coordinates evaluation
  listIterator <SNelementIntp *> itr(intpPtrLst);

  for(itr.init(); !itr ; ++itr) {

    ret = evaluator.evalInterpolationNode(itr());
    if(ret != 0) {
      SystemErrorA((SNunit *)itr(),"Node coordinate is not numeric.");
      errFlag++;
    }
  }
  
    
  evaluator.vertexDefaults( etype );  // add evalPair("x1",-1.0) etc.


  // feelfemTEMP   here should be evaluation (numeric or not)
  // for defined variables, etc.

  return(0);   // feelfemTEMP
}


// 
int SNelement::ParseInterpolates(void)
{
  nodes = 0;   // this is private member of SNelement.

  // Node analyse
  Node *nPtr;
  listIterator <SNelementIntp *>itr(intpPtrLst);
  

  // count number of nodes
  for(itr.init(); !itr ; ++itr ) {

    nPtr = itr()->generateNodeClass();   // it is copied to Element class
    
    if(nodeOrderedPtrLst.includes( nPtr ) ) {
      nPtr->~Node();
      continue;
    }
    nodeOrderedPtrLst.add( nPtr );
    nodes++;
  }

  return(0);
}


int SNelement::CheckInterpType(void)
{
  int errors;
  
  errors = 0;
  
  listIterator <SNelementIntp *>itr(intpPtrLst);

  // count number of nodes
  for(itr.init(); !itr ; ++itr ) {

    int ret;

    ret = itr()->checkTypeAttribute();

    if(ret != 0) {
      SystemErrorANameA((SNunit*)itr(),"Interpolation type '","' is invalid.");
      errors++;
    }
  }
  return(errors);
}
