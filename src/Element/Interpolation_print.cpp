/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : Interpolation_print.cpp
 *  Date     : 2002/04/09
 *  Modified : 
 *  
 *  Purpose  : check write function
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

#include <iostream>

#include "Interpolation.hpp"

void Interpolation::print(std::ostream &ost)
{
  nodePtr->print(ost);
  ost << " [" << type << "] ";
  ost << " : " << exprStr;

  return;
}
