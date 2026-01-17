/*
 *  feelfem v1.0 NEC Corporation (C) 1999,2000,2001
 *                   Programmed  by  Hidehiro FUJIO
 *
 *  Filename : SL_LIB_feelP2Skyline.hpp
 *  Date     : 2002/04/19 01:54
 *  Purpose  : LIB_feelP2Skyline library generate class
 *
 */


#ifndef FEM_CLASS_SL_LIB_FEELP2SKYLINE
#define FEM_CLASS_SL_LIB_FEELP2SKYLINE

#include "PM_feelP2.hpp"

class SL_LIB_feelP2Skyline
  :  public PM_feelP2 {

public:
  SL_LIB_feelP2Skyline() { return; } // do nothing
  ~SL_LIB_feelP2Skyline(){ return; } // do nothing

  void SL_sol(int);
  void SL_scal(int);

  void generateLibrary(void) {

    SL_sol(90);
    SL_scal(80);

    return;
  }


};

#endif
