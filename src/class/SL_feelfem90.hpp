/*
 *  feelfem v1.0 NEC Corporation (C) 1999,2000,2001
 *                   Programmed  by  Hidehiro FUJIO
 *
 *  Filename : SL_feelfem90.hpp
 *  Date     : 2002/09/12 17:25
 *  Purpose  : feelfem90 library generate class
 *
 *
 *  feelfem2 (modernized/ported)
 *  Copyright (C) 2025-2026 Hidehiro Fujio and contributors
 *  SPDX-License-Identifier: BSD-3-Clause
 *  Repository: https://github.com/oimokoimo/feelfem2
 *
 *
 *  Notes:
 *
 */


#ifndef FEM_CLASS_SL_FEELFEM90
#define FEM_CLASS_SL_FEELFEM90

#include "PM_feelfem90.hpp"

class SL_feelfem90
  :  public PM_feelfem90 {

public:
  SL_feelfem90() { return; } // do nothing
  ~SL_feelfem90() = default;

  void SL_numeric(int);
  void SL_zero(int);
  void SL_femDataType(int);
  void SL_abortmodule(int);
  void SL_fileread(int);
  void SL_report90(int);
  void SL_feelP2data(int);
  void SL_subsolveff90p2(int);

  void generateLibrary(void) {

    SL_numeric(1);
    SL_zero(1);
    SL_femDataType(2);
    SL_abortmodule(1);
    SL_fileread(5);
    SL_report90(5);
    SL_feelP2data(5);
    SL_subsolveff90p2(10);

    return;
  }


};

#endif
