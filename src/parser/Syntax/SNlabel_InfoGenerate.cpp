/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNlabel_InfoGenerate.cpp
 *  Date     : 2002/07/18
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

#include "SNlabel.hpp"
#include "Label.hpp"

#include "Object.hpp"
#include "feelfuncs.hpp"

int SNlabel::InfoGenerate(void)
{
  labelPtr = new Label(val);
  feelfemobj.StoreLabelPtr(labelPtr);     

  return(0);
}
