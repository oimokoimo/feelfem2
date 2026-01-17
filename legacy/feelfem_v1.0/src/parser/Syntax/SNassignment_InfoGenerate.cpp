/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNassignment_InfoGenerate.cpp
 *  Date     : 2002/04/15 (BCN)
 *  Modified : 
 *  
 *  Purpose  :
 *  
 */

#include <assert.h>

#include "feeldef.hpp"
#include "feelfuncs.hpp"

#include "SNassignment.hpp"
#include "Assign.hpp"
#include "Variable.hpp"
#include "orderedPtrList.hpp"

#include "Object.hpp"
#include "GeometryObject.hpp"
#include "Configure.hpp"       // for default integral integration method


int SNassignment::InfoGenerate(void)
{
  // asPtr is in SNassignment class
  asPtr = new Assign;
  assert(asPtr != 0);

  // add feelfemobj
  feelfemobj.StoreAssign( asPtr );  // counts how many assigns in the mean time

  // SNassignment is a friend class of Assign

  // left hand side variable pointer
  Variable *vPtr = feelfemobj.GetVariablePtrWithName(leftVarName);
  asPtr->AddLeftVarPtr(vPtr);
  

  // Make Variable list on right hand side
  exprPtr->MakeVariablePtr(asPtr->varPtrLst);

  // Make user function list
  list <string>userFuncUsedLst;
  exprPtr->MakeUserFuncLst( userFuncUsedLst );
  listIterator <string>itruf(userFuncUsedLst);
  for(itruf.init();!itruf;++itruf) {
    string s=itruf();
    asPtr->AddUsedUserFuncSymbol( s );
  }

  // set expression of assignment
  char exprbuf[MAX_EXPRPRINT_BUF];
  exprbuf[0] = '\0';
  exprPtr->exprPrint(exprbuf,EXPRPRINT_NORMAL,0,0);
  asPtr->expr = exprbuf;   // SetExpression is added after ewise quad

  // set original expression in simple form
  exprbuf[0] = '\0';
  exprPtr->exprPrint(exprbuf,EXPRPRINT_SIMPLE,0,0);
  asPtr->SetOriginalExpression( exprbuf );

  // set x,y,z,nx,ny,nz usage flag
  exprPtr->CheckXYZNXNYNZ_Assign( asPtr );

  // set geometry type
  switch(vPtr->GetType()) {
  case VAR_FEM:
    asPtr->SetGeometryType( ASSIGN_TYPE_NORMAL ); // selective fem value
    // assign is not implemented
    // UC
    break;

  case VAR_EWISE:
  case VAR_EWISE_A:
    asPtr->SetGeometryType( ASSIGN_TYPE_ELEM );  //means just to use ielem data
    break;

  case VAR_VFEM:
    assert(1==0);
    break;

  case VAR_INT:
  case VAR_DOUBLE:
    {
      if( integralType == ASSIGNMENT_TYPE_ORIGINAL) {
	switch(placeFlag) {
	case SN_ASSIGNMENT_NORMAL:
	  asPtr->SetGeometryType( ASSIGN_TYPE_NORMAL ); 
	  break;

	case SN_ASSIGNMENT_AT:
	  asPtr->SetGeometryType( ASSIGN_TYPE_NODE   );  // ip data
	  break;

	case SN_ASSIGNMENT_IN:
	case SN_ASSIGNMENT_ON:
	case SN_ASSIGNMENT_WHERE:
	  assert(1==0);  // never happen?
	  break;
	}
	break;
      }
      else {
	if(integralType == ASSIGNMENT_TYPE_INTEGRAL) {
	  asPtr->SetGeometryType( ASSIGN_TYPE_INTEGRAL );  //integration
	  break;
	}
	else {
	  assert(1==0);  // ASSIGNMENT_TYPE_BINTEGRAL
	}
      }
    }
  default:
    assert(1==0);

  }

  // left var type ( with geometry into consideration)
  switch(vPtr->GetType()) {
  case VAR_FEM:
    asPtr->SetLeftVarAssignType( AS_VAR_TYPE_FEM_NODE);
    break;

  case VAR_EWISE:
    asPtr->SetLeftVarAssignType( AS_VAR_TYPE_EWISE_M);
    break;

  case VAR_EWISE_A:

    if(vPtr->GetEwiseType() == EWISE_TYPE_INTERPOLATION ) {
      asPtr->SetLeftVarAssignType(AS_VAR_TYPE_EWISE_I);
    }
    else {
      assert(vPtr->GetEwiseType() == EWISE_TYPE_GAUSSPOINT);
      asPtr->SetLeftVarAssignType(AS_VAR_TYPE_EWISE_G);

      // set Quadrature Pointer to Assign class
      asPtr->SetQuadraturePtr( vPtr->GetQuadraturePtr());

      // use coroutine
      asPtr->UseCoroutine();
    }
    break;

  case VAR_VFEM:
    assert(1==0);
    break;

  case VAR_INT:
    asPtr->SetLeftVarAssignType( AS_VAR_TYPE_SCALAR );
    break;

  case VAR_DOUBLE:
    if(integralType == ASSIGNMENT_TYPE_ORIGINAL) {
      asPtr->SetLeftVarAssignType( AS_VAR_TYPE_SCALAR );
    }
    else if(integralType == ASSIGNMENT_TYPE_INTEGRAL) {
      asPtr->SetLeftVarAssignType( AS_VAR_TYPE_DOUBLE_INTEGRAL );
      asPtr->UseDiff1st();         // integration needs determinant(02/11/19)

      // Quadrature pointer will be set
      if(integrationMethod == DEFAULT_STRING) {

	int etype        = feelfemgeomobj.GetRegionalEtype();
	Quadrature *qPtr = feelfemconf.GetDefaultQuadraturePtrByEtype(etype);
	asPtr->SetQuadraturePtr(qPtr);
      }
      else {
	Quadrature *qPtr;
	qPtr = feelfemobj.GetQuadraturePtrByName(integrationMethod);
	asPtr->SetQuadraturePtr(qPtr);
      }

      // use coroutine
      asPtr->UseCoroutine();
    }
    else {
      assert(1==0);  // for bintegral, max, min etc.
    }

    break;

  default:
    assert(1==0);
  }

  // make GeomObj pointer list
  int numberOfPlaces = 0;
  if(placeLst != 0) {
    numberOfPlaces = placeLst->GetNumberOfElements();
  }
  asPtr->SetNumberOfPlaces( numberOfPlaces );

  for(int i=0;i<numberOfPlaces; i++) {
    string nm = (*placeLst)[i]->GetName();

    GeomObj *goPtr = feelfemgeomobj.GetGeomObjByName(nm);
    
    asPtr->AddGeomObjPtr( goPtr );
  }


  // Differential operator 
  if(exprPtr->HasDifferential1st()) {

    asPtr->UseDiff1st();               // exists 1st order diff op. dx,dy,dz

    switch(feelfemobj.GetSpaceDimension()) {
    case 1:
      asPtr->UseX();
      break;

    case 2:
      asPtr->UseX();
      asPtr->UseY();
      break;

    case 3:
      asPtr->UseX();
      asPtr->UseY();
      asPtr->UseZ();
      break;

    default:
      assert(1==0);
    }

  }

  return(0);
}

