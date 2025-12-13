/*
 *  feelfem v1.0 NEC Corporation (C) 1999,2000,2001
 *                   Programmed  by  Hidehiro FUJIO
 *
 *  Filename : SL_LIB_feelP2Achim.hpp
 *  Date     : 2002/04/19 01:54
 *  Purpose  : LIB_feelP2Achim library generate class
 *
 */


#ifndef FEM_CLASS_SL_LIB_FEELP2ACHIM
#define FEM_CLASS_SL_LIB_FEELP2ACHIM

#include "PM_feelP2.hpp"

class SL_LIB_feelP2Achim
  :  public PM_feelP2 {

public:
  SL_LIB_feelP2Achim() { return; } // do nothing
  ~SL_LIB_feelP2Achim(){ return; } // do nothing

  void SL_binio(int);
  void SL_wrtcrsfil(int);

  void generateLibrary(void) {

    SL_binio(80);
    SL_wrtcrsfil(90);

    return;
  }


};

#endif
