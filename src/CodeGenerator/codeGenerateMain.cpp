/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : codeGenerateMain.cpp
 *  Date     : 2001/05/09
 *  Modified : 
 *  
 *  Purpose  :
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

#include <iostream>
#include "Main.hpp"
#include "feeldef.hpp"
#include "Configure.hpp"   // for F90 compiler set for aistpcp90(02/12/08)
#include "feelfuncs.hpp"


#include "MainGeneratorTemplate.hpp"
//#include "PM_feelP2.hpp"                  // (underconstruction)
#include "PM_feelP2DRAMA.hpp"
#include "PM_feelfem90DRAMA.hpp"
#include "PM_feelfem90.hpp"
#include "PM_aistpcp90.hpp"
#include "PM_feelfem90smpi.hpp"  // 2003/01/04


// SourceLibrary for ProgramModel
#include "SL_feelfem90.hpp"
#include "SL_aistpcp90.hpp"
#include "SL_feelfem90DRAMA.hpp"

void codeGenerateMain(Main *mainPtr)
{

  // Program Model type
  switch( mainPtr->getProgramModelType() ) {
  
    // NormalMainProgram    (not Subroutine as found in AVS co-routine)  


  case TYPE_FEELP2:
    std::cerr << "TYPE_FEELP2 MainGeneratorTemplate does not exist.(codeGenerateMain.cpp)\n";
    break;

  case TYPE_FEELP2DRAMA:
    {
      MainGeneratorTemplate<PM_feelP2DRAMA> *mPtr =
	new MainGeneratorTemplate<PM_feelP2DRAMA>();
      mPtr->NormalMainProgram(mainPtr);

    }
    break;

  case TYPE_FEELFEM90:
    {
      MainGeneratorTemplate<PM_feelfem90> *mPtr =
	new MainGeneratorTemplate<PM_feelfem90>();
      
      mPtr->NormalMainProgram(mainPtr);


      // ProgramModel related
      SL_feelfem90 *slpmPtr  = new SL_feelfem90();
      slpmPtr ->generateLibrary();


    }
    break;

  case TYPE_FEELFEM90DRAMA:
    {
      MainGeneratorTemplate<PM_feelfem90DRAMA> *mPtr =
	new MainGeneratorTemplate<PM_feelfem90DRAMA>();
      
      mPtr->NormalMainProgram(mainPtr);

      // ProgramModel related
      SL_feelfem90DRAMA *slpmPtr  = new SL_feelfem90DRAMA();
      slpmPtr ->generateLibrary();

      // mpif90
      feelfemconf.SetF90(DEFAULT_MPIF90_COMPILER);

    }
    break;

  case TYPE_AISTPCP90:
    {
      MainGeneratorTemplate<PM_aistpcp90> *mPtr =
	new MainGeneratorTemplate<PM_aistpcp90>();
      
      mPtr->NormalMainProgram(mainPtr);

      // ProgramModel related modules
      SL_aistpcp90         *slpmPtr  = new SL_aistpcp90();
      slpmPtr  ->generateLibrary();

      // mpif90
      feelfemconf.SetF90(DEFAULT_MPIF90_COMPILER);

    }
    break;


  case TYPE_FEELFEM90SMPI:
    {
      MainGeneratorTemplate<PM_feelfem90smpi> *mPtr =
	new MainGeneratorTemplate<PM_feelfem90smpi>();
      
      mPtr->NormalMainProgram(mainPtr);

      // ProgramModel related modules
      //      SL_aistpcp90         *slpmPtr  = new SL_aistpcp90();
      //      slpmPtr  ->generateLibrary();

      // mpif90
      feelfemconf.SetF90(DEFAULT_MPIF90_COMPILER);


      // almost same as feelfem90
      SL_feelfem90 *slpmPtr  = new SL_feelfem90();
      slpmPtr ->generateLibrary();


    }
    break;


  default:
    std::cerr << "mainPtr->getProgramModelType() = " 
	 << mainPtr->getProgramModelType() 
         << " (In codeGenerateMain.cpp)\n";
    abortExit(1);

  }

  return;
}
  
