/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : Procedure.hpp
 *  Date     : 2001/04/23
 *  Modified : 
 *  
 *  Purpose  : Correspondance of scheme block
 *  
 */

#ifndef FEM_CLASS_PROCEDURE
#define FEM_CLASS_PROCEDURE

class Procedure {
public:
  Procedure();
  ~Procedure();

  void SetProgramModel(int code) {                // from scheme_pm_check.cpp
    programModel = code;
    return;
  }
  int GetProgramModel(void) { return programModel; }  // used in Main const,
                                                      // cg_Assignment*.cpp
private:
  int programModel;

};

#endif

