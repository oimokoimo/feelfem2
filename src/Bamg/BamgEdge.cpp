/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : BamgEdge.cpp
 *  Date     : 2001/04/05
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

#include "Bamg.hpp"

BamgEdge::BamgEdge(int f,int t,int r)
{
  assert(f!=t);

  bamgEdgeRefNo = r;
  from          = f;
  to            = t;
  return;
}

int BamgEdge::isSameEdge( int f, int t )
{
  if(from == f && to == t) return(1 == 1);
  if(from == t && to == f) return(1 == 1);
  return(1 == 0);
}

