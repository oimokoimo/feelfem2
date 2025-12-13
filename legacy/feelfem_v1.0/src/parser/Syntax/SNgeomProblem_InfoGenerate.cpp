/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNGeomProblem_InfoGenerate.cpp
 *  Date     : 2002/03/19
 *  Modified : 
 *  
 *  Purpose  :
 *  
 */

#include "feelfuncs.hpp"
#include "GeometryObject.hpp"
#include "SNgeomProblem.hpp"

int SNgeomProblem::InfoGenerate()
{
  feelfemgeomobj.SetProblemName( problemName );
  return(0);
}
