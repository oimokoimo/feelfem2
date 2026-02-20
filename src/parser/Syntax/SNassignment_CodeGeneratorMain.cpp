/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNassignment_CodeGeneratorMain.cpp
 *  Date     : 2002/04/17 (BCN)
 *  Modified : 
 *  
 *  Purpose  :
 *  
 */

#include "SNassignment.hpp"
#include "Main.hpp"

// Generator template class
#include "MainGeneratorTemplate.hpp"

// Program models
#include "PM_feelfem90.hpp"
#include "PM_feelfem90smpi.hpp"
#include "PM_aistpcp90.hpp"
#include "PM_feelfem90DRAMA.hpp"

void SNassignment::CodeGenerateMain(void *mgtPtr,Main *mainPtr)
{
  switch(mainPtr->getProgramModelType()) {

  case TYPE_FEELFEM90:
    {
      MainGeneratorTemplate <PM_feelfem90> *ptr = 
	(MainGeneratorTemplate <PM_feelfem90> *)mgtPtr;
      ptr->DoMainScheme_assign(mainPtr,asPtr);
    }
    break;

  case TYPE_FEELFEM90SMPI:
    {
      MainGeneratorTemplate <PM_feelfem90smpi> *ptr = 
	(MainGeneratorTemplate <PM_feelfem90smpi> *)mgtPtr;
      ptr->DoMainScheme_assign(mainPtr,asPtr);
    }
    break;

  case TYPE_AISTPCP90:
    {
      MainGeneratorTemplate <PM_aistpcp90> *ptr = 
	(MainGeneratorTemplate <PM_aistpcp90> *)mgtPtr;
      ptr->DoMainScheme_assign(mainPtr,asPtr);
    }
    break;

  case TYPE_FEELFEM90DRAMA:
    {
      MainGeneratorTemplate <PM_feelfem90DRAMA> *ptr = 
	(MainGeneratorTemplate <PM_feelfem90DRAMA> *)mgtPtr;
      ptr->DoMainScheme_assign(mainPtr,asPtr);
    }
    break;

  default:
    cerr << "##################################################" << endl;
    cerr << "# NOT IMPLEMENTED ASSIGN.                        #" << endl;
    cerr << "# SNassignment_CodeGeneratorMain.cpp             #" << endl;
    cerr << "##################################################" << endl;
  }
  return;
}
