/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : Source.cpp
 *  Date     : 1999/10/26
 *  Modified : 1999/10/26
 *  
 *  Purpose  : Source test
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

#include <cstdio>
#include <cassert>
#include "feelfuncs.hpp"
#include "feeldef.hpp"
#include "Source.hpp"

#include "MakefileObject.hpp"


// Source.cpp (どこか1か所だけ！)

FILE* Source::fpSource = nullptr;
int   Source::divideFlag = 0;
int   Source::numberOfSourceFiles = 0;

// orderedPtrList の static も全部ここで定義が必要
orderedPtrList<MakefileObject*> Source::f90_basic_list;
orderedPtrList<MakefileObject*> Source::f90_library_list;
orderedPtrList<MakefileObject*> Source::f90_model_list;
orderedPtrList<MakefileObject*> Source::f90_problem_list;
orderedPtrList<MakefileObject*> Source::f90_main_list;

orderedPtrList<MakefileObject*> Source::f77_basic_list;
orderedPtrList<MakefileObject*> Source::f77_library_list;
orderedPtrList<MakefileObject*> Source::f77_model_list;
orderedPtrList<MakefileObject*> Source::f77_problem_list;
orderedPtrList<MakefileObject*> Source::f77_main_list;

orderedPtrList<MakefileObject*> Source::c_basic_list;
orderedPtrList<MakefileObject*> Source::c_library_list;
orderedPtrList<MakefileObject*> Source::c_model_list;
orderedPtrList<MakefileObject*> Source::c_problem_list;
orderedPtrList<MakefileObject*> Source::c_main_list;

orderedPtrList<MakefileObject*> Source::cpp_basic_list;
orderedPtrList<MakefileObject*> Source::cpp_library_list;
orderedPtrList<MakefileObject*> Source::cpp_model_list;
orderedPtrList<MakefileObject*> Source::cpp_problem_list;
orderedPtrList<MakefileObject*> Source::cpp_main_list;


//Constructor
Source::Source( const char *name)
{
  assert(fpSource == nullptr);
  
    fpSource = fopen(name,"w");
    if(fpSource == nullptr) {
      std::cerr << "Cannot open " << FEELFEM_SRC_FNAME << " to create.\n";
      abortExit(1);
    }
    //std::cerr <"DEBUG IN SOURCE(CHAR *)\n";  for debug
    //fpSource = stderr;                  for debug
  return;
}



Source::Source()
{
  divideFlag = 1;  

  dbgGeneratorReport( "Source constructor ",
		      "divide flag set to 1 in Source constructor");

  return;
}

Source::~Source() =default;


FILE * Source::GetSourceFP(void)
{
  if(fpSource == nullptr) {
    std::cerr << "File pointer is  in Source::GetSourceFP() \n";
    abortExit(1);
  }
  return(fpSource);
}


void Source::startSource(const char *str)       // this is called OpenSource 
{
  if(divideFlag == 1 && fpSource != nullptr) {
    std::cerr << "fpSource is not nullptr while calling startSource()\n";
    abortExit(1);
  }

  fpSource = fileOpenToWrite(str);
  if(fpSource == nullptr) {
    std::cerr << "Cannot open " <<str << " to write.\n";
    abortExit(1);
  }

  StoreSource(str , 999);    // 999 means individual level(maybe ERROR)
 
  return;
}


void Source::startSource(const char *str , int makeFlag)
{
  if(divideFlag == 1 && fpSource !=nullptr) {
    std::cerr << "fpSource is not NULL while calling startSource()\n";
    abortExit(1);
  }

  fpSource = fileOpenToWrite(str);
  if(fpSource == nullptr) {
    std::cerr << "Cannot open " <<str << " to write.\n";
    abortExit(1);
  }

  StoreSource(str , makeFlag);  
  return;
}



void Source::endSource(void)
{
  if(fpSource == nullptr) {
    std::cerr <<"Try to close nullptr pointer in endSource()\n";
    abortExit(1);
  }
  fclose(fpSource);
  fpSource = nullptr;

  return;
}

//void Source::StoreSource(char *sourceName, int makeFlag)
// above function is in MakeMakefile.cpp
