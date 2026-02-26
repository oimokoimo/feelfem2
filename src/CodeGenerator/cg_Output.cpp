/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : cg_Output.cpp
 *  Date     : 2002/07/17
 *  Modified : 
 *  
 *  Purpose  : Output routine
 *
 *
 *  feelfem2 (modernized/ported)
 *  Copyright (C) 2025-2026 Hidehiro Fujio and contributors
 *  SPDX-License-Identifier: BSD-3-Clause
 *  Repository: https://github.com/oimokoimo/feelfem2
 *
 *
 *  Notes:
 *  
 */

#include "feeldef.hpp"
#include "feelfuncs.hpp"
#include "Procedure.hpp"

#include "OutputGeneratorTemplate.hpp"
#include "Output.hpp"


// ProgramModels
#include "PM_feelfem90.hpp"
#include "PM_feelfem90smpi.hpp"
#include "PM_feelfem90DRAMA.hpp"

#include "PM_aistpcp90.hpp"


void cg_Output(Output *outputPtr )
{
  switch(feelfemproc.GetProgramModel()) {

  case TYPE_FEELFEM90:
    {
      OutputGeneratorTemplate <PM_feelfem90> *ptrOutput =
	new OutputGeneratorTemplate<PM_feelfem90>();

      ptrOutput->GiDOutput(outputPtr);  // currently, only gid.
    }
    break;

  case TYPE_FEELFEM90SMPI:
    {
      OutputGeneratorTemplate <PM_feelfem90smpi> *ptrOutput =
	new OutputGeneratorTemplate<PM_feelfem90smpi>();

      ptrOutput->GiDOutput(outputPtr);  // currently, only gid.
    }
    break;

  case TYPE_AISTPCP90:
    {
      OutputGeneratorTemplate <PM_aistpcp90> *ptrOutput =
	new OutputGeneratorTemplate<PM_aistpcp90>();

    
      ptrOutput->GiDOutput(outputPtr);  // currently, only gid.
    }
    break;

  case TYPE_FEELFEM90DRAMA:
    {
      OutputGeneratorTemplate <PM_feelfem90DRAMA> *ptrOutput =
	new OutputGeneratorTemplate<PM_feelfem90DRAMA>();

      ptrOutput->GiDOutput(outputPtr);  // currently, only gid.
    }
    break;



  case TYPE_FEELP2:
  case TYPE_FEELP2DRAMA:
  case TYPE_FEELFEM90VEC:

    std::cerr << "UC output scalar for feelp2, feelp2Drama, etc."
	 << std::endl;
    break;

  default:
    std::cerr << "This is default: section in cg_Output.cpp" 
	 << std::endl;
    break;    
  }

  return;
}
