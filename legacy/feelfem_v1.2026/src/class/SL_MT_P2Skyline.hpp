/*
 *  feelfem v1.0 NEC Corporation (C) 1999,2000,2001
 *                   Programmed  by  Hidehiro FUJIO
 *
 *  Filename : SL_MT_P2Skyline.hpp
 *  Date     : 2002/04/19 01:54
 *  Purpose  : MT_P2Skyline library generate class
 *
 */


#ifndef FEM_CLASS_SL_MT_P2SKYLINE
#define FEM_CLASS_SL_MT_P2SKYLINE

#include "PM_feelP2.hpp"

class SL_MT_P2Skyline
  :  public PM_feelP2 {

public:
  SL_MT_P2Skyline() { return; } // do nothing
  ~SL_MT_P2Skyline(){ return; } // do nothing

  void SL_cal_ht(int);
  void SL_make_KLD(int);

  void generateLibrary(void) {

    SL_cal_ht(30);
    SL_make_KLD(40);

    return;
  }


};

#endif
