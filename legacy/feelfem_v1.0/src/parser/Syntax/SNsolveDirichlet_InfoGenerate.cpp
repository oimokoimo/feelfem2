/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNsolveDirichlet_InfoGenerate.cpp
 *  Date     : 2002/02/05
 *  Modified : 
 *  
 *  Purpose  :
 *  
 */

#include "SNsolveDirichlet.hpp"

#include "feeldef.hpp"      // for EXPR_LENGTH
#include "feelfuncs.hpp"
#include "Object.hpp"

#include "Variable.hpp"
#include "Dirichlet.hpp"

#include "GeometryObject.hpp"
#include "DirichletGeom.hpp"


Variable *SNsolveDirichlet::GetDirichletVariablePtr(void)
{
  Variable *ptr;
  ptr = feelfemobj.GetVariablePtrWithName( varName );
  return(ptr);
}

void SNsolveDirichlet::AddVariablePtr_Dirichlet(Dirichlet *dPtr)
{
  dirichletPtr = dPtr;

  dExprPtr->AddVariablePtr_Dirichlet(dPtr);
  return;
}

void SNsolveDirichlet::SetDataExprStr(Dirichlet *dPtr)
{
  char buf[MAX_EXPRPRINT_BUF];
 
  buf[0] = '\0';
  dExprPtr->exprPrint(buf,EXPRPRINT_NORMAL,0,0);
  dPtr->SetDataExprStr( buf );

  return;
}

void SNsolveDirichlet::SetDataSimpleExprStr(Dirichlet *dPtr)
{
  char buf[MAX_EXPRPRINT_BUF];
 
  buf[0] = '\0';
  dExprPtr->exprPrint(buf,EXPRPRINT_SIMPLE,0,0);
  dPtr->SetDataSimpleExprStr( buf );

  return;
}

int SNsolveDirichlet::GeometryCreate()
{
  int errors = 0;
  
  for(int i=0;i<dBoundaryLst->GetNumberOfElements();i++) {
    string nm = (*dBoundaryLst)[i]->GetName();

    GeomObj *goPtr       = feelfemgeomobj.GetGeomObjByName(nm);
    DirichletGeom *dgPtr = feelfemgeomobj.AcquireDirichletGeomByName(goPtr);

    assert(dirichletPtr != 0);

    // DirichletGeom data in Dirichlet,
    dirichletPtr->AddDirichletGeomPtr( dgPtr );

    // Dirichlet data in DirichletGeom
    dgPtr->StoreDirichletData(dirichletPtr);

  }
  
  return(errors);
}
  
