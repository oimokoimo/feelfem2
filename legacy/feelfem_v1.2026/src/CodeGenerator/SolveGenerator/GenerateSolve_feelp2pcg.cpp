/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : GenerateSolve_feelp2pcg.cpp
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

#include "../../class/PM_feelP2.hpp"
#include "../../class/MT_P2PCG.hpp"
#include "../../class/LIB_feelP2PCG.hpp"

void GenerateSolve_feelp2pcg( Solve *solvePtr )
{
  LIB_feelP2PCG<MT_P2PCG>  *ptr = 
    new LIB_feelP2PCG<MT_P2PCG> ();
  ptr ->NormalLinearProblem(solvePtr);

  return;
}
