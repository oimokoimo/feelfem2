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
 */

#include <iostream.h>

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
    cerr << "##################################################" << endl;
    cerr << "# NOT IMPLEMENTED OUTPUT.                        #" << endl;
    cerr << "# SNoutput_CodeGeneratorMain.cpp                 #" << endl;
    cerr << "##################################################" << endl;
  }
  return;
}
