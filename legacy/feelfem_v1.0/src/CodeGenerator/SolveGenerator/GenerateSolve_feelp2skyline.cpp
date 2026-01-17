/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : 
 *  Date     : 2001/08/21
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

#include "../../class/SolveGeneratorTemplate.hpp"
#include "../../class/ElemGeneratorTemplate.hpp"
#include "../../class/DirichletGeneratorTemplate.hpp"
#include "../../class/NeumannGeneratorTemplate.hpp"

#include "../../class/PM_feelP2.hpp"
#include "../../class/MT_P2Skyline.hpp"
#include "../../class/LIB_feelP2Skyline.hpp"

void GenerateSolve_feelp2skyline( Solve *solvePtr )
{
  LIB_feelP2Skyline      <MT_P2Skyline>  *ptr = 
    new LIB_feelP2Skyline<MT_P2Skyline> ();

  ptr ->NormalLinearProblem(solvePtr);
  
  return;
}
