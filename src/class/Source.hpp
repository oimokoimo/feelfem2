/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : Source.hpp
 *  Date     : 1999/10/26
 *  Modified : 2001/02/02  orderedPtrList
 *  
 *  Purpose  : Source code output control base class
 *  
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
#include "orderedPtrList.hpp"

#ifndef FEM_SOURCE_CLASS
#define FEM_SOURCE_CLASS

class MakefileObject;
class string;

class Source {
  
public:
  Source();         // Normal Constructor for nested class
  Source(const char *);   // Initializer 
  ~Source();
  

  void startSource( const char *);          // Normal open with no hierarchy
  void startSource( const char * , int );   // Open file with dependency level number

  void endSource  ( void  );

  FILE *GetSourceFP(void);

  void StoreSource( const char *, int );     // file name and flag(dependctrl)
  void StoreSourceUniq( const char *, int ); // for user function, library,etc.

  // Making Makefile related functions
  void makeMakefile( int );
  void writeObjList( FILE *,orderedPtrList <MakefileObject *> &);
  

private:
  static  FILE *fpSource;
  static  int   divideFlag;

  static  int   numberOfSourceFiles;

  static orderedPtrList <MakefileObject *>  f90_basic_list;
  static orderedPtrList <MakefileObject *>  f90_library_list;
  static orderedPtrList <MakefileObject *>  f90_model_list;
  static orderedPtrList <MakefileObject *>  f90_problem_list;
  static orderedPtrList <MakefileObject *>  f90_main_list;

  static orderedPtrList <MakefileObject *>  f77_basic_list;
  static orderedPtrList <MakefileObject *>  f77_library_list;
  static orderedPtrList <MakefileObject *>  f77_model_list;
  static orderedPtrList <MakefileObject *>  f77_problem_list;
  static orderedPtrList <MakefileObject *>  f77_main_list;

  static orderedPtrList <MakefileObject *>  c_basic_list;
  static orderedPtrList <MakefileObject *>  c_library_list;
  static orderedPtrList <MakefileObject *>  c_model_list;
  static orderedPtrList <MakefileObject *>  c_problem_list;
  static orderedPtrList <MakefileObject *>  c_main_list;

  static orderedPtrList <MakefileObject *>  cpp_basic_list;
  static orderedPtrList <MakefileObject *>  cpp_library_list;
  static orderedPtrList <MakefileObject *>  cpp_model_list;
  static orderedPtrList <MakefileObject *>  cpp_problem_list;
  static orderedPtrList <MakefileObject *>  cpp_main_list;

  list <string>outerSourceFile;

};


#endif
