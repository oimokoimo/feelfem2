/*
 *  feelfem v1.0 NEC Corporation (C) 1999,2000,2001
 *                   Programmed  by  Hidehiro FUJIO
 *
 *  Filename : SL_LIB_feelfem90SAMG20c.hpp
 *  Date     : 2001/02/06 14:22
 *  Purpose  : LIB_feelfem90SAMG20c library generate class
 *
 */


#ifndef FEM_CLASS_SL_LIB_FEELFEM90SAMG20C
#define FEM_CLASS_SL_LIB_FEELFEM90SAMG20C

#include "PM_feelfem90DRAMA.hpp"

class SL_LIB_feelfem90SAMG20c
  :  public PM_feelfem90DRAMA {

public:
  SL_LIB_feelfem90SAMG20c() { return; } // do nothing
  ~SL_LIB_feelfem90SAMG20c(){ return; } // do nothing

  void SL_user_coo(int);

  void generateLibrary(void) {

    SL_user_coo(1000);

    return;
  }


};

#endif
