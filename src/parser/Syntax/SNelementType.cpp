/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNelementType.cpp
 *  Date     : 2002/11/02
 *  Modified : 
 *  
 *  Purpose  : element type parser
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

#include "feeldef.hpp"
#include "SNelementType.hpp"

SNelementType::SNelementType( SNidentifierlist *ptr) 
  :            SNunit("elementType",SN_ELEMENTTYPE) 
{ 
  etypeIdentifierLst = ptr;
  return;
}

