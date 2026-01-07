/*
 *  feelfem v1.0 NEC Corporation (C) 1999,2000,2001
 *                   Programmed  by  Hidehiro FUJIO
 *
 *  Filename : SL_MT_P2CRS.hpp
 *  Date     : 2002/04/19 01:54
 *  Purpose  : MT_P2CRS library generate class
 *
 */


#ifndef FEM_CLASS_SL_MT_P2CRS
#define FEM_CLASS_SL_MT_P2CRS

#include "PM_feelP2.hpp"

class SL_MT_P2CRS
  :  public PM_feelP2 {

public:
  SL_MT_P2CRS() { return; } // do nothing
  ~SL_MT_P2CRS(){ return; } // do nothing

  void SL_mkcrsindex(int);
  void SL_nc_connect(int);

  void generateLibrary(void) {

    SL_mkcrsindex(40);
    SL_nc_connect(40);

    return;
  }


};

#endif
