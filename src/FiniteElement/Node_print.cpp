/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : Node_print.cpp
 *  Date     : 2002/02/01
 *  Modified : 
 *  
 *  Purpose  : debug routine
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
#include "Node.hpp"

void Node::print(std::ostream &ost)
{
  ost << "(" << xi ;
  if(dimension >1) {
    ost << "," << eta;
  }
  if(dimension >2) {
    ost << "," << zeta;
  }
  ost << ") [eval=";

  ost << eval() << "]";
  
  return;
}
