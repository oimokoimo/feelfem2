/*
 *  feelfem v1.0 NEC Corporation (C) 1999,2000,2001
 *                   Programmed  by  Hidehiro FUJIO
 *
 *  Filename : SL_MT_ff90SKYLINE.hpp
 *  Date     : 2002/04/19 01:54
 *  Purpose  : MT_ff90SKYLINE library generate class
 *
 */


#ifndef FEM_CLASS_SL_MT_FF90SKYLINE
#define FEM_CLASS_SL_MT_FF90SKYLINE

#include "PM_feelfem90.hpp"

class SL_MT_ff90SKYLINE
  :  public PM_feelfem90 {

public:
  SL_MT_ff90SKYLINE() { return; } // do nothing
  ~SL_MT_ff90SKYLINE(){ return; } // do nothing

  void SL_mat_skyline(int);

  void generateLibrary(void) {

    SL_mat_skyline(30);

    return;
  }


};

#endif
