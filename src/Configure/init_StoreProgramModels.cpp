/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : init_StoreProgramModels.cpp
 *  Date     : 2002/03/07
 *  Modified : 
 *  
 *  Purpose  :
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

#include "Configure.hpp"
#include "feeldef.hpp"

void Configure::init_StoreProgramModels()
{
  // Store Program Model Names
  StoreProgramModelNames(NAME_PM_FEELP2        ,TYPE_FEELP2         );
  StoreProgramModelNames(NAME_PM_FEELP2DRAMA   ,TYPE_FEELP2DRAMA    );
  StoreProgramModelNames(NAME_PM_FEELFEM90     ,TYPE_FEELFEM90      );
  StoreProgramModelNames(NAME_PM_FEELFEM90DRAMA,TYPE_FEELFEM90DRAMA );
  StoreProgramModelNames(NAME_PM_AISTPCP90     ,TYPE_AISTPCP90      );
  StoreProgramModelNames(NAME_PM_FEELFEM90SMPI ,TYPE_FEELFEM90SMPI  );
  return;
}
