/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : GenerateSolve_feelfem90pamg.cpp
 *  Date     : 2001/08/22
 *  Modified : 
 *  
 *  Purpose  :
 *  
 */

#include "../../class/feeldef.hpp"

#include "../../class/Source.hpp"
#include "../../class/Solve.hpp"
#include "../../class/Dirichlet.hpp"
#include "../../class/Neumann.hpp"

#include "../../class/ElemGeneratorTemplate.hpp"
#include "../../class/DirichletGeneratorTemplate.hpp"
#include "../../class/NeumannGeneratorTemplate.hpp"

#include "../../class/PM_feelfem90DRAMA.hpp"
#include "../../class/MT_ff90PAMGCRS.hpp"
#include "../../class/LIB_feelfem90PAMG81.hpp"

void GenerateSolve_feelfem90pamg81( Solve *solvePtr )
{
  LIB_feelfem90PAMG81<MT_ff90PAMGCRS>  *ptr = 
    new LIB_feelfem90PAMG81<MT_ff90PAMGCRS> ();
  ptr ->NormalLinearProblem(solvePtr);

  int dconds;
  dconds = solvePtr->GetDconds();
  for(int i=0;i<dconds;i++) {
    Dirichlet *dPtr = solvePtr->GetIthDirichletDataPtr( i );
    DirichletGeneratorTemplate<MT_ff90PAMGCRS> *ptrDG =
      new DirichletGeneratorTemplate<MT_ff90PAMGCRS>();
    ptrDG->DirichletNormalLinear(solvePtr,dPtr);
  }

  int nconds;
  nconds = solvePtr->GetNconds();
  for(int i=0;i<nconds;i++) {
    Neumann *nPtr = solvePtr->GetIthNeumannDataPtr( i );
    NeumannGeneratorTemplate<MT_ff90PAMGCRS> *ptrNG =
      new NeumannGeneratorTemplate<MT_ff90PAMGCRS>();
    ptrNG->NeumannNormalLinear(solvePtr,nPtr);
  }
  return;
}
