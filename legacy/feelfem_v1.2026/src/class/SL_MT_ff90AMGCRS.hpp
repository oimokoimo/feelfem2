/*
 *  feelfem v1.0 NEC Corporation (C) 1999,2000,2001
 *                   Programmed  by  Hidehiro FUJIO
 *
 *  Filename : SL_MT_ff90AMGCRS.hpp
 *  Date     : 2003/01/05 01:06
 *  Purpose  : MT_ff90AMGCRS library generate class
 *
 */


#ifndef FEM_CLASS_SL_MT_FF90AMGCRS
#define FEM_CLASS_SL_MT_FF90AMGCRS

#include "PM_feelfem90.hpp"

class SL_MT_ff90AMGCRS
  :  public PM_feelfem90 {

public:
  SL_MT_ff90AMGCRS() { return; } // do nothing
  ~SL_MT_ff90AMGCRS(){ return; } // do nothing

  void SL_AMGCRS(int);

  void generateLibrary(void) {

    SL_AMGCRS(40);

    return;
  }


};

#endif
