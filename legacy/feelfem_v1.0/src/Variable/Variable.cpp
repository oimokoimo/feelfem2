/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : Variable.cpp
 *  Date     : 1999/11/17
 *  Modified : 1999/11/18
 *  
 *  Purpose  : Variable instance
 *  
 */

#include <iostream.h>     // for ostream
#include <assert.h>

#include "feelfem.hpp"    // for debugging
#include "feelfuncs.hpp" 
#include "Variable.hpp"

#include "Element.hpp"
#include "Quadrature.hpp"

#include "GeometryObject.hpp"    // for GetMATERIALFreedom();

// static variables
int Variable::numerateInitialNo    = 0;
int Variable::numerateDblInitialNo = 0;
int Variable::numerateIntInitialNo = 0;

int operator <(const Variable &val1, const Variable &val2)
{
  if( val1.varType != val2.varType) {
    return ( val1.varType < val2.varType);
  }
  return( val1.varName < val2.varName);
}

int operator ==(const Variable &val1, const Variable &val2)
{

  // TEMPORARY CODING       streq is not good
  
  if( val1.varType == val2.varType && streq(val1.varName,val2.varName)) {
    return ( val1.varType == val2.varType);
  }
  return( 1 == 0);
}





Variable::Variable()
{
  cerr << "Default Variable constructor was called...(It may be error)\n";
  assert(1==0);
  return;  // do nothing now
}

Variable::Variable(char *name, int type)
{
  varName = name;
  varType = type;

  ePtr    = NULL;
  qPtr    = NULL;

  elementFreedom = 0;
  ewiseType      = 0;

  sblNo_termConvert       = 0;
  elementNo_termConvert   = 0;
  elementStno_termConvert = 0;
  functionNo_termConvert  = 0;   // ewiseQuad 020724

  initialFlag = 0;

  // material variable
  pairs          = 0;
  materialValues = 0;


  return;  
}

Variable::~Variable()
{
  return;  // do nothing now
}

const char *Variable::GetName()
{
  return (const char *)varName;
}

int Variable::GetType()
{
  return varType;
}

int Variable::GetEwiseType(void)
{
  return(ewiseType);
}

void Variable::SetFunctionName(const char *nm)
{
  functionName = nm;
  return;
}

int Variable::IsElementPtrReady(void)
{
  if(ePtr == NULL) {
    return(NO);
  }

  return(YES);
}

int Variable::GetEtype(void)
{
  
  if(feelfem_debug) {
    cerr << "CHECK GetEtype " << varName << endl;
  }

  switch(varType) {
  case VAR_FEM:
    return(ePtr->GetEtype());
    break;

  case VAR_EWISE_A:
    if(ewiseType == EWISE_TYPE_INTERPOLATION) {
      return(ePtr->GetEtype());
    }
    else {
      if(ewiseType == EWISE_TYPE_GAUSSPOINT) {
	return(qPtr->GetEtype());
      }
      assert (1 == 0);
    }
   
  default:
    assert(1==0);
  }
  assert(1==0);
  return(-999);
}


int Variable::GetFreedom(void)
{
  assert(varType == VAR_EWISE   || 
	 varType == VAR_EWISE_A ||
	 varType == VAR_FEM     || 
	 varType == VAR_VFEM           );
  return(elementFreedom);
}

int Variable::GetEWISEFreedom(void)
{
  assert(varType == VAR_EWISE || varType == VAR_EWISE_A);

  return(elementFreedom);
}

int Variable::GetFEMFreedom(void)
{
  assert(varType == VAR_FEM || varType == VAR_VFEM);
  
  return(elementFreedom);
}
 
int Variable::IsConsistentEtypeWith(int refEtype)
{
  switch(varType) {

  case VAR_DOUBLE:
  case VAR_INT:
  case VAR_CONST:
  case VAR_EWISE:
  case VAR_MATERIAL:
    return(YES);
    
  case VAR_FEM:
  case VAR_EWISE_A:
    if(GetEtype() == refEtype) {
      return(YES);
    }
    else {
      return(NO);
    }

  default:
    assert(1==0);
  }
  return(NO);
}


Quadrature *Variable::GetQuadraturePtr(void)
{
  switch(varType) {


  case VAR_EWISE_A:
    if(ewiseType == EWISE_TYPE_GAUSSPOINT) {
      return(qPtr);
    }
    else {
      cerr << "Try to get quadPtr from ewise-interpolation variable.\n";
      assert(1==0);
    }
    break;
    
  case VAR_EWISE:
  case VAR_MATERIAL:
  case VAR_DOUBLE:
  case VAR_INT:
  case VAR_CONST:
  case VAR_FEM:
    cerr << "Variable::GetQuadraturePtr not quadrature variable\n";
    assert(1==0);

  default:
    assert(1==0);
  }
  return(0);
}

Element *Variable::GetElementPtr(void)
{
  switch(varType) {

  case VAR_FEM:
  case VAR_VFEM:
    return(ePtr);

  case VAR_EWISE_A:
    if(ewiseType == EWISE_TYPE_INTERPOLATION) {
      return(ePtr);
    }
    else {
      cerr << "Try to get elemPtr from ewise-gausspoint variable.\n";
      assert(1==0);
    }
    break;
    
  case VAR_EWISE:
  case VAR_DOUBLE:
  case VAR_INT:
  case VAR_CONST:
    cerr << "Variable::GetQuadraturePtr not element variable\n";
    assert(1==0);

  default:
    assert(1==0);
  }
  return(0);
}


void Variable::operator = (const Variable &val)
{
  varType = val.varType;   
  varName = val.varName;   // it takes new memory!!!!!

  cerr << "======================================================\n";
  cerr << "Variable operator= called.(FOR ONLY ReadCtrl77dat.cpp)\n";
  cerr << "======================================================\n";

  functionName   = val.functionName;
  elementFreedom = val.elementFreedom;
  ePtr           = val.ePtr;
  qPtr           = val.qPtr;
  elementFreedom = val.elementFreedom;
  ewiseType      = val.ewiseType;

  return;
}

ostream & operator << (ostream &cout, Variable &var )
{
  cout << "(dbg:Variable=[" << var.GetName() << "]";
  return cout;
}

void Variable::SetSblNo(int no)
{
  assert(sblNo_termConvert == 0);
  sblNo_termConvert = no; 
  //  cerr << "Variable::SetSblNo  "<<varName << " = "<<no << endl; // oimo
  return;
}

int Variable::GetSblNo(void)
{
  //  cerr << "Variable::GetSblNo "<<varName<<"="<<sblNo_termConvert << endl;

  assert(sblNo_termConvert > 0);
  return sblNo_termConvert;
}

void Variable::SetElementTCNo( int no) 
{
  assert(elementNo_termConvert == 0);
  elementNo_termConvert = no;
  return; 
}

int Variable::GetElementTCNo(void) 
{ 
  assert(elementNo_termConvert > 0);
  return elementNo_termConvert; 
}

void Variable::SetElementStno( int no) 
{
  assert(elementStno_termConvert == 0);
  elementStno_termConvert = no;
  return;
} 

int Variable::GetElementStno(void) 
{ 
  assert(elementStno_termConvert >0);
  return elementStno_termConvert; 
}

void Variable::initWorkTC(void)
{
  sblNo_termConvert       = 0;
  elementNo_termConvert   = 0;
  elementStno_termConvert = 0;
  functionNo_termConvert  = 0;

  return;
}

void Variable::SetFunctionTCNo(int no)
{
  assert(functionNo_termConvert == 0);
  functionNo_termConvert = no;
  return;
} 

int Variable::GetFunctionTCNo(void) 
{ 
  assert(functionNo_termConvert >0);
  return functionNo_termConvert; 
}

int Variable::GetMATERIALFreedom(void)
{
  //  All region has its correspondance of material No.

  int mat_regions = feelfemgeomobj.GetNumberOfRegionObjects();

  return( mat_regions );
}

