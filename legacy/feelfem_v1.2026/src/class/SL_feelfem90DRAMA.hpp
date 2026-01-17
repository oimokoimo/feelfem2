/*
 *  feelfem v1.0 NEC Corporation (C) 1999,2000,2001
 *                   Programmed  by  Hidehiro FUJIO
 *
 *  Filename : SL_feelfem90DRAMA.hpp
 *  Date     : 2003/03/02 20:50
 *  Purpose  : feelfem90DRAMA library generate class
 *
 */


#ifndef FEM_CLASS_SL_FEELFEM90DRAMA
#define FEM_CLASS_SL_FEELFEM90DRAMA

#include "PM_feelfem90DRAMA.hpp"

class SL_feelfem90DRAMA
  :  public PM_feelfem90DRAMA {

public:
  SL_feelfem90DRAMA() { return; } // do nothing
  ~SL_feelfem90DRAMA(){ return; } // do nothing

  void SL_numeric(int);
  void SL_abortmodule(int);
  void SL_preport90(int);
  void SL_feelfem90mp(int);
  void SL_datatrans(int);
  void SL_probInfoDistribute(int);
  void SL_subSolveDrama(int);
  void SL_femDataType(int);
  void SL_dramaDataModel(int);
  void SL_fileread(int);

  void generateLibrary(void) {

    SL_numeric(1);
    SL_abortmodule(1);
    SL_preport90(2);
    SL_feelfem90mp(3);
    SL_datatrans(5);
    SL_probInfoDistribute(5);
    SL_subSolveDrama(10);
    SL_femDataType(2);
    SL_dramaDataModel(5);
    SL_fileread(5);

    return;
  }


};

#endif
