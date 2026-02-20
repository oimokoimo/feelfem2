/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNprogramModel.hpp
 *  Date     : 2001/02/14
 *  Modified : 
 *  
 *  Purpose  : programmodel class for parser  (reference aumc)
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

#ifndef FEM_SYNTAX_PROGRAMMODEL
#define FEM_SYNTAX_PROGRAMMODEL

#include "SNunit.hpp"
#include "SNname.hpp"

class Main;

class SNprogramModel : public SNunit {
public:
  SNprogramModel( const char *nm) : SNunit("programModel",SN_PROGRAMMODEL) 
  { modelName = nm; }


  // print
  void print(std::ostream & ost) { ost << "programModel=" 
				  <<  modelName
				  << "\n";            }

  // check functions
  int IsDefinedProgramModelName(void);    // in SNprogramModel_CHECK.cpp
  void set_feelfemproc(void);             // in SNprogramModel_CHECK.cpp
                                          // set feelfemproc

  // Code generate functions  (ProgramModel has no instance.)
  void CodeGenerate(void);
  void CodeGenerateMain(void *p,Main *m);

  // for SystemError functions
  void errWrtName(std::ostream &ost ) {
    ost << modelName;
    return;
  }


private:
  string modelName;

};


#endif
