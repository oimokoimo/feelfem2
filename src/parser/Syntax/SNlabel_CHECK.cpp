/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNlabel_CHECK.cpp
 *  Date     : 2002/07/18
 *  Modified : 
 *  
 *  Purpose  : duplicate check
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

#include "list.hpp"
#include "string.hpp"

#include "SNlabel.hpp"

#include "../../check/check_funcs.hpp"

int SNlabel::duplicate_check(list <string>&strLst)
{
  if(strLst.includes(val)) {
    SystemErrorAStrA(this,"Label ",val," is multiply defined.");
    return(1);
  }
  
  strLst.add(val);

  return(0);
}
