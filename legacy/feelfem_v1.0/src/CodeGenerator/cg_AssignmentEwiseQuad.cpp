/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : cg_AssignmentEwiseQuad.cpp
 *  Date     : 2002/07/11
 *  Modified : 
 *  
 *  Purpose  :
 *  
 */

#include "feeldef.hpp"
#include "feelfuncs.hpp"
#include "Procedure.hpp"

#include "Assign.hpp"
#include "AssignScheme.hpp"
#include "AssignGeneratorTemplate.hpp"

// ProgramModels
#include "PM_feelfem90.hpp"
#include "PM_feelfem90smpi.hpp"

#ifdef USE_PM_AISTPCP90
#include "PM_aistpcp90.hpp"
#endif


void cg_AssignmentEwiseQuad( Assign *asPtr )
{
  switch(feelfemproc.GetProgramModel()) {

  case TYPE_FEELFEM90:
    {
      AssignGeneratorTemplate <PM_feelfem90> *ptrAS = 
	new AssignGeneratorTemplate<PM_feelfem90>();

      ptrAS->NormalAssignmentEwiseQuad(asPtr);
      ptrAS->NormalAssignmentEwiseQuadCoroutine(asPtr);   // coroutine
    }
    break;


  case TYPE_FEELFEM90SMPI:
    {
      AssignGeneratorTemplate <PM_feelfem90smpi> *ptrAS = 
	new AssignGeneratorTemplate<PM_feelfem90smpi>();

      ptrAS->NormalAssignmentEwiseQuad(asPtr);
      ptrAS->NormalAssignmentEwiseQuadCoroutine(asPtr);   // coroutine
    }
    break;

#ifdef USE_PM_AISTPCP90
  case TYPE_AISTPCP90:
    {
      AssignGeneratorTemplate <PM_aistpcp90> *ptrAS = 
	new AssignGeneratorTemplate<PM_aistpcp90>();
    
      ptrAS->NormalAssignmentEwiseQuad(asPtr);
      ptrAS->NormalAssignmentEwiseQuadCoroutine(asPtr);   // coroutine
    }
    break;

#endif


  case TYPE_FEELP2:
  case TYPE_FEELP2DRAMA:
  case TYPE_FEELFEM90DRAMA:
  case TYPE_FEELFEM90VEC:

    cerr << "UC assignment ewise quad for feelp2, feelp2Drama,feemfem90drama, etc."
	 << endl;
    break;

  default:
    cerr << "This is default: section in cg_AssignmentEwiseQuad.cpp" 
	 << endl;
    break;    
  }

  return;
}
