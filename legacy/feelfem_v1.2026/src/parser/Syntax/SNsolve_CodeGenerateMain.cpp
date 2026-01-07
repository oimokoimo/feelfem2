/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNsolve_CodeGenerateMain.cpp
 *  Date     : 2001/08/24
 *  Modified : 
 *  
 *  Purpose  : Main generator
 *  
 */

#include "../../class/feeldef.hpp"
#include "../../class/feelfuncs.hpp"

#include "SNsolve.hpp"

#include "../../class/PM_feelfem90.hpp"
#include "../../class/PM_feelfem90smpi.hpp"

#include "../../class/Main.hpp"
#include "../../class/PM_feelP2DRAMA.hpp"
#include "../../class/PM_feelfem90DRAMA.hpp"
#include "../../class/PM_aistpcp90.hpp"
#include "../../class/MainGeneratorTemplate.hpp"



void SNsolve::CodeGenerateMain(void *mgtPtr,Main *mPtr)  // MainGeneratorTemplate
{

  // AVS,GID are not supported now.  (Maybe easy to extend)
  switch(mPtr->getProgramModelType()) {
    
  case TYPE_FEELP2:
    {
      //      MainGeneratorTemplate <PM_feelP2> *ptr = 
      //	(MainGeneratorTemplate <PM_feelfem90> *)mgtPtr;
      //      ptr->DoMainScheme_solve(mPtr,solvePtr);
    }
    break;
    

  case TYPE_FEELP2DRAMA:
    {
      MainGeneratorTemplate <PM_feelP2DRAMA> *ptr = 
      	(MainGeneratorTemplate <PM_feelP2DRAMA> *)mgtPtr;
      ptr->DoMainScheme_solve(mPtr,solvePtr);
    }
    break;

  case TYPE_FEELFEM90:
    {
      MainGeneratorTemplate <PM_feelfem90> *ptr = 
	(MainGeneratorTemplate <PM_feelfem90> *)mgtPtr;
      ptr->DoMainScheme_solve(mPtr,solvePtr);
    }
    break;

  case TYPE_FEELFEM90DRAMA:
    {
      MainGeneratorTemplate <PM_feelfem90DRAMA> *ptr = 
      	(MainGeneratorTemplate <PM_feelfem90DRAMA> *)mgtPtr;
      ptr->DoMainScheme_solve(mPtr,solvePtr);
    }
    break;

  case TYPE_FEELFEM90SMPI:
    {
      MainGeneratorTemplate <PM_feelfem90smpi> *ptr = 
	(MainGeneratorTemplate <PM_feelfem90smpi> *)mgtPtr;
      ptr->DoMainScheme_solve(mPtr,solvePtr);
    }
    break;


  case TYPE_AISTPCP90:
    {
      MainGeneratorTemplate <PM_aistpcp90> *ptr = 
	(MainGeneratorTemplate <PM_aistpcp90> *)mgtPtr;
      ptr->DoMainScheme_solve(mPtr,solvePtr);
    }
    break;

  default:
    cerr << "##################################################\n";
    cerr << "This is default in void SNsolve::CodeGenerateMain\n";
    cerr << "###  code = " << mPtr->getProgramModelType() << endl;
    cerr << "##################################################\n";

  }
}
