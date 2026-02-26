/*
 *  feelfem v1.0 NEC Corporation (C) 1999,2000,2001
 *                   Programmed  by  Hidehiro FUJIO
 *
 *  Filename : SL_MT_ff90PAMGCRS.hpp
 *  Date     : 2002/04/19 01:54
 *  Purpose  : MT_ff90PAMGCRS library generate class
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


#ifndef FEM_CLASS_SL_MT_FF90PAMGCRS
#define FEM_CLASS_SL_MT_FF90PAMGCRS

#include "PM_feelfem90DRAMA.hpp"

class SL_MT_ff90PAMGCRS
  :  public PM_feelfem90DRAMA {

public:
  SL_MT_ff90PAMGCRS() { return; } // do nothing
  ~SL_MT_ff90PAMGCRS(){ return; } // do nothing

  void SL_PAMGCRS(int);

  void generateLibrary(void) {

    SL_PAMGCRS(40);

    return;
  }


};

#endif
