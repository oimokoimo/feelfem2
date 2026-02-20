/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNunit.cpp
 *  Date     : 2001/12/21
 *  Modified : 
 *  
 *  Purpose  : for virtual print function,  why = 0; ???
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
#include "SNunit.hpp"

void SNunit::print(std::ostream &ost)
{
  ost << "VIRTUAL FUNCTION SNunit::print is called.\n";
}
