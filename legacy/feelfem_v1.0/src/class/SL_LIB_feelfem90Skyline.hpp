/*
 *  feelfem v1.0 NEC Corporation (C) 1999,2000,2001
 *                   Programmed  by  Hidehiro FUJIO
 *
 *  Filename : SL_LIB_feelfem90Skyline.hpp
 *  Date     : 2002/04/19 01:54
 *  Purpose  : LIB_feelfem90Skyline library generate class
 *
 */


#ifndef FEM_CLASS_SL_LIB_FEELFEM90SKYLINE
#define FEM_CLASS_SL_LIB_FEELFEM90SKYLINE

#include "PM_feelfem90.hpp"

class SL_LIB_feelfem90Skyline
  :  public PM_feelfem90 {

public:
  SL_LIB_feelfem90Skyline() { return; } // do nothing
  ~SL_LIB_feelfem90Skyline(){ return; } // do nothing

  void SL_skyline_solver(int);
  void SL_skyline_scal(int);

  void generateLibrary(void) {

    SL_skyline_solver(90);
    SL_skyline_scal(90);

    return;
  }


};

#endif
