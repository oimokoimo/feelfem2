/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : GenerateSolve_feelp2achimloc.cpp
 *  Date     : 2001/08/22
 *  Modified : 
 *  
 *  Purpose  :
 *  
 */

#include "../../class/feeldef.hpp"

#include "../../class/Source.hpp"
#include "../../class/Solve.hpp"
#include "../../class/SolveElement.hpp"
#include "../../class/Dirichlet.hpp"
#include "../../class/Neumann.hpp"

#include "../../class/ElemGeneratorTemplate.hpp"
#include "../../class/DirichletGeneratorTemplate.hpp"
#include "../../class/NeumannGeneratorTemplate.hpp"

#include "../../class/PM_feelP2DRAMA.hpp"
#include "../../class/MT_P2CRSLOC.hpp"
#include "../../class/LIB_feelP2AchimLoc.hpp"


void GenerateSolve_feelp2achimloc( Solve *solvePtr )
{
  LIB_feelP2AchimLoc<MT_P2CRSLOC>  *ptr = 
    new LIB_feelP2AchimLoc<MT_P2CRSLOC> ();
  ptr ->NormalLinearProblem(solvePtr);

  int dconds;
  dconds = solvePtr->GetDconds();
  for(int i=0;i<dconds;i++) {
    Dirichlet *dPtr = solvePtr->GetIthDirichletDataPtr( i );
    DirichletGeneratorTemplate<MT_P2CRSLOC> *ptrDG =
      new DirichletGeneratorTemplate<MT_P2CRSLOC>();
    ptrDG->DirichletNormalLinear(solvePtr,dPtr);
  }

  int nconds;
  nconds = solvePtr->GetNconds();
  for(int i=0;i<nconds;i++) {
    Neumann *nPtr = solvePtr->GetIthNeumannDataPtr( i );
    NeumannGeneratorTemplate<MT_P2CRSLOC> *ptrNG =
      new NeumannGeneratorTemplate<MT_P2CRSLOC>();
    ptrNG->NeumannNormalLinear(solvePtr,nPtr);
  }

  return;
}
