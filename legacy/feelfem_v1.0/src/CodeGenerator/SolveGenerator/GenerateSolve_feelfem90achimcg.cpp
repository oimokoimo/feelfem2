/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : GenerateSolve_feelfem90achimcg.cpp
 *  Date     : 2001/08/22
 *  Modified : 
 *  
 *  Purpose  :
 *  
 */

#include "../../class/Source.hpp"
#include "../../class/Solve.hpp"
#include "../../class/Dirichlet.hpp"
#include "../../class/Neumann.hpp"

#include "../../class/SolveGeneratorTemplate.hpp"
#include "../../class/ElemGeneratorTemplate.hpp"
#include "../../class/DirichletGeneratorTemplate.hpp"
#include "../../class/NeumannGeneratorTemplate.hpp"

#include "../../class/PM_feelfem90.hpp"
#include "../../class/MT_ff90AMGCRS.hpp"
#include "../../class/LIB_feelfem90AchimCG.hpp"

void GenerateSolve_feelfem90achimcg( Solve *solvePtr )
{
  LIB_feelfem90AchimCG<MT_ff90AMGCRS>  *ptr = 
    new LIB_feelfem90AchimCG<MT_ff90AMGCRS> ();
  ptr ->NormalLinearProblem(solvePtr);

  int dconds;
  dconds = solvePtr->GetDconds();
  for(int i=0;i<dconds;i++) {
    Dirichlet *dPtr = solvePtr->GetIthDirichletDataPtr( i );
    DirichletGeneratorTemplate<MT_ff90AMGCRS> *ptrDG =
      new DirichletGeneratorTemplate<MT_ff90AMGCRS>();
    ptrDG->DirichletNormalLinear(solvePtr,dPtr);
  }

  int nconds;
  nconds = solvePtr->GetNconds();
  for(int i=0;i<nconds;i++) {
    Neumann *nPtr = solvePtr->GetIthNeumannDataPtr( i );
    NeumannGeneratorTemplate<MT_ff90AMGCRS> *ptrNG =
      new NeumannGeneratorTemplate<MT_ff90AMGCRS>();
    ptrNG->NeumannNormalLinear(solvePtr,nPtr);
  }

  return;
}
