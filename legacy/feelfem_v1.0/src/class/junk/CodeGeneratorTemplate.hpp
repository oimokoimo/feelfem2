/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : CodeGeneratorTemplate.hpp
 *  Date     : 2002/02/06
 *  Modified : 
 *  
 *  Purpose  :
 *  
 */

#include "Solve.hpp"

#include "SolveGeneratorTemplate.hpp"
#include "ElemGeneratorTemplate.hpp"
#include "DirichletGeneratorTemplate.hpp"
#include "NeumannGeneratorTemplate.hpp"


template <class template LIB_Class,  class MT_Class> 
void cg_NormalLinearProblem( Solve *solvePtr )
{
  LIB_Class<MT_Class>  *ptr =
    new LIB_Class<MT_Class> ();
  ptr ->NormalLinearProblem(solvePtr);
 
  ElemGeneratorTemplate<MT_Class> *ptrEG =
    new ElemGeneratorTemplate<MT_Class>();
  ptrEG->NormalAssembly(solvePtr,solvePtr->GetIthSolveElementPtr(0));
 
  int dconds;
  dconds = solvePtr->GetDconds();
  for(int i=0;i<dconds;i++) {
    Dirichlet *dPtr = solvePtr->GetIthDirichletDataPtr( i );
    DirichletGeneratorTemplate<MT_Class> *ptrDG =
      new DirichletGeneratorTemplate<MT_Class>();
    ptrDG->DirichletNormalLinear(solvePtr,dPtr);
  }
 
  int nconds;
  nconds = solvePtr->GetNconds();
  for(int i=0;i<nconds;i++) {
    Neumann *nPtr = solvePtr->GetIthNeumannDataPtr( i );
    NeumannGeneratorTemplate<MT_Class> *ptrNG =
      new NeumannGeneratorTemplate<MT_Class>();
    ptrNG->NeumannNormalLinear(solvePtr,nPtr);
  }
  return;
}
