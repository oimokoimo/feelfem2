/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : cg_AssignmentScalar.cpp
 *  Date     : 2002/04/16 (BCN)
 *  Modified : 
 *  
 *  Purpose  : scalar variable assignment code generator
 *             Called from 
 *  
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
#include "PM_feelfem90DRAMA.hpp"

#ifdef USE_PM_AISTPCP90
#include "PM_aistpcp90.hpp"
#endif


void cg_AssignmentScalar( Assign *asPtr )
{
  switch(feelfemproc.GetProgramModel()) {

  case TYPE_FEELFEM90:
    {
      AssignGeneratorTemplate <PM_feelfem90> *ptrAS = 
	new AssignGeneratorTemplate<PM_feelfem90>();
      ptrAS->NormalAssignment(asPtr);
    }
    break;

  case TYPE_FEELFEM90SMPI:
    {
      AssignGeneratorTemplate <PM_feelfem90smpi> *ptrAS = 
	new AssignGeneratorTemplate<PM_feelfem90smpi>();
      ptrAS->NormalAssignment(asPtr);
    }
    break;

  case TYPE_FEELFEM90DRAMA:
    {
      AssignGeneratorTemplate <PM_feelfem90DRAMA> *ptrAS = 
	new AssignGeneratorTemplate<PM_feelfem90DRAMA>();
      ptrAS->NormalAssignment(asPtr);
    }
    break;


#ifdef USE_PM_AISTPCP90

  case TYPE_AISTPCP90:
    {
      AssignGeneratorTemplate <PM_aistpcp90> *ptrAS = 
    	new AssignGeneratorTemplate<PM_aistpcp90>();

      ptrAS->NormalAssignment(asPtr);
    }
    break;
#else

  case TYPE_AISTPCP90:
#endif


  case TYPE_FEELP2:
  case TYPE_FEELP2DRAMA:
  case TYPE_FEELFEM90VEC:

    cerr << "UC assignment scalar for feelp2, feelp2Drama, etc in cg_AssignementScalar.cpp."
	 << endl;
    break;

  default:
    cerr << "This is default: section in cg_AssignmentScalar.cpp" 
	 << endl;
    break;    
  }

  return;
}
