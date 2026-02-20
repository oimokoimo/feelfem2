/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNwrite_CodeGenerateMain.cpp
 *  Date     : 2002/11/22 (copy of SNif_CodeGenerateMain.cpp)
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

#include "SNwrite.hpp"
#include "Main.hpp"

// Generator template class
#include "MainGeneratorTemplate.hpp"

// Program models
#include "PM_feelfem90.hpp"
#include "PM_feelfem90smpi.hpp"
#include "PM_aistpcp90.hpp"
#include "Write.hpp"

void SNwrite::CodeGenerateMain(void *mgtPtr,Main *mainPtr)
{
  switch(mainPtr->getProgramModelType()) {
  case TYPE_FEELFEM90:
    {
      MainGeneratorTemplate <PM_feelfem90> *ptr = 
      	(MainGeneratorTemplate <PM_feelfem90> *)mgtPtr;
      ptr->DoMainScheme_write(mainPtr,writePtr);
    }
    break;


  case TYPE_FEELFEM90SMPI:
    {
      MainGeneratorTemplate <PM_feelfem90smpi> *ptr = 
      	(MainGeneratorTemplate <PM_feelfem90smpi> *)mgtPtr;
      ptr->DoMainScheme_write(mainPtr,writePtr);
    }
    break;

  case TYPE_AISTPCP90:
    {
      MainGeneratorTemplate <PM_aistpcp90> *ptr = 
      	(MainGeneratorTemplate <PM_aistpcp90> *)mgtPtr;
      ptr->DoMainScheme_write(mainPtr,writePtr);
    }
    break;

  default:
    std::cerr << "##################################################" << std::endl;
    std::cerr << "# NOT IMPLEMENTED OUTPUT.                        #" << std::endl;
    std::cerr << "# SNoutput_CodeGeneratorMain.cpp                 #" << std::endl;
    std::cerr << "##################################################" << std::endl;
  }
  return;
}
