/*
 *  feelfem v1.0 NEC Corporation (C) 1999,2000,2001
 *                   Programmed  by  Hidehiro FUJIO
 *
 *  Filename : SL_MT_ff90smpiMUMPSCA.hpp
 *  Date     : 2003/01/10 13:03
 *  Purpose  : MT_ff90smpiMUMPSCA library generate class
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


#ifndef FEM_CLASS_SL_MT_FF90SMPIMUMPSCA
#define FEM_CLASS_SL_MT_FF90SMPIMUMPSCA

#include "PM_feelfem90smpi.hpp"

class SL_MT_ff90smpiMUMPSCA
  :  public PM_feelfem90smpi {

public:
  SL_MT_ff90smpiMUMPSCA() { return; } // do nothing
  ~SL_MT_ff90smpiMUMPSCA(){ return; } // do nothing

  void SL_MUMPSCA(int);

  void generateLibrary(void) {

    SL_MUMPSCA(40);

    return;
  }


};

#endif
