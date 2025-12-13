/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999,2000
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SL_feelfem90DRAMA.hpp
 *  Date     : 2000/11/20
 *  Modified : 2000/11/20
 *  
 *  Purpose  : Source Library generator for feelfem90DRAMA model
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

  void SL_PAMGCRS(int);        // AMGCRS.f90
  void SL_preport90(int);      // preport90.f90
  void SL_numeric(int);        // numeric.f90
  void SL_femDataType(int);    // femDataType.f90
  void SL_abortmodule(int);    // abortmodule.f90
  void SL_fileread(int);       // fileread.f90
  void SL_datatrans(int);      // datatrans.f90
  void SL_dramaDataModel(int); // dramaDataModel.f90
  void SL_subSolveDrama(int);  // subSolveDrama.f90
  void SL_feelfem90mp(int);    // feelfem90mp.f90

  void generateLibrary(void) {

    SL_numeric(1);         // fundamental
    SL_preport90(1);       // fundamental
    SL_femDataType(1);     // fundamental
    SL_abortmodule(1);     // fundamental,MPI
    SL_feelfem90mp(3);     // use abortmodule,MPI
    SL_fileread(5);        // use femDataType,numeric
    SL_datatrans(5);       // use numeric,femDataType, MPI
    SL_dramaDataModel(5);  // use numeric,femDataType,abortmodule
    SL_subSolveDrama(5);   // use numeric,abortmodule,feelfem90mp
    SL_PAMGCRS(10);        // use numeric,subSolveDrama,amg_update,amg_penv
    

    return;
  }


};


#endif
